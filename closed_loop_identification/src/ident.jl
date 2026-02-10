using DifferentialEquations, LinearAlgebra, Plots, CSV, DataFrames, Optim
using Optimization, OptimizationOptimJL, ForwardDiff, SciMLSensitivity

# --- 1. Parameters & Configuration ---
const P = (
    J = Diagonal([0.0258, 0.0268, 0.0680]),
    a = 13.0, b = 0.085908, c = 0.0351, 
    l = 0.20,
    E = [1.0  1.0  1.0  1.0;
           0.0 -0.2  0.0  0.2;
           0.2  0.0 -0.2  0.0;
           0.0351 -0.0351 0.0351 -0.0351],
    k_roll_drag = 0.05,
    m = 1.014,
    g = 9.81,
    d = 0.05,
    dt_ctrl = 0.05
)

# --- 2. Controller & Allocation ---
mutable struct Controller
    kp::Float64; ki::Float64; kd::Float64
    integral::Float64; prev_error::Float64
    throttles::Vector{Float64}
    target_func::Function
end

# Initialize PID for Roll (Angle setpoint = 0)
ctrl = Controller(
    0.8, 0.8, 0.45, 
    0.0, 0.0, 
    zeros(4), 
    t -> deg2rad(10.0) * sin(0.5 * t)
)

function control_alloc(tau)
    # Solve mixing: Torques -> Squared Thrusts -> RPM
    f_sq = P.E \ tau
    rpm = sqrt.(max.(f_sq, 0.0) ./ P.a) .+ P.b
    return clamp.(rpm, 0.15, 0.90)
end

function pid_callback!(integrator)
    c = ctrl
    state = integrator.u
    t = integrator.t
    
    # 1. Sense: Roll error
    target = c.target_func(t)
    error = target - state[1]

    # 2. PID Logic
    c.integral += error * P.dt_ctrl
    deriv = (error - c.prev_error) / P.dt_ctrl
    roll_moment = c.kp * error + c.ki * c.integral + c.kd * deriv
    
    # 3. Control Allocation
    # [Total Thrust (to maintain hover), Roll Moment, Pitch, Yaw]
    tau_vec = [2.0, roll_moment, 0.0, 0.0]
    c.throttles = control_alloc(tau_vec)
    
    # 4. Update internal state
    c.prev_error = error
end

cb = PeriodicCallback(pid_callback!, P.dt_ctrl)

# --- 3. Dynamics ---
u0 = zeros(6)
# u0[1] = deg2rad(15.0)  # Initial roll angle
function quadrotor_dynamics!(du, u, p, t)
    ϕ, θ = u[1], u[2]
    ω = u[4:6]

    throttles = ctrl.throttles
    thrusts = @. p.a * (throttles - p.b)^2

     # Kinematics: Body rates to Euler rates
    # s=sin, c=cos, t=tan
    sφ, cφ = sin(ϕ), cos(ϕ)
    sθ, tθ, cθ = sin(θ), tan(θ), cos(θ)
    W = [1  sφ*tθ  cφ*tθ;
           0  cφ     -sφ;
           0  sφ/cθ  cφ/cθ]
    
    # Forces/Torques
    torques = (p.E * thrusts)[2:4]
    torques[1] += p.m * p.g * p.d * sφ * cθ
    torques[2] += p.m * p.g * p.d * sθ

    torques[2] = 0.0
    torques[3] = 0.0

    damping_torques = p.k_roll_drag * ω[1] * [1.0, 0.0, 0.0]

    # Derivatives
    du[1:3] = W * omega
    du[4:6] = p.J \ (torques - damping_torques - cross(omega, p.J * omega))
end

# --- 4. Simulation Execution ---
tspan = (0.0, 40.0)
trange = tspan[1]:0.01:tspan[2]

prob = ODEProblem(quadrotor_dynamics!, u0, tspan, P; callback=cb)
sol = solve(prob, Tsit5(), reltol=1e-8, abstol=1e-8)

# --- 5. Visualization ---
# Main state plot
y = [rad2deg.(u[1]) for u in sol.u], 
    [rad2deg.(u[4]) for u in sol.u]

# Convert to a Matrix for easy plottin
plot(sol.t, hcat(y[:, 1], y[:, 2], [rad2deg(ctrl.target_func(t)) for t in sol.t]),
     layout=(2,1),
     labels=["Roll" "wx" "Reference Roll"])

# Animation
function rotation_matrix(phi, theta, psi)
    Rx = [1 0 0; 0 cos(phi) -sin(phi); 0 sin(phi) cos(phi)]
    Ry = [cos(theta) 0 sin(theta); 0 1 0; -sin(theta) 0 cos(theta)]
    Rz = [cos(psi) -sin(psi) 0; sin(psi) cos(psi) 0; 0 0 1]
    return Rz * Ry * Rx
end

println("Generating animation...")
anim = @animate for t in range(tspan[1], tspan[2], length=200)
    phi, theta, psi = sol(t)[1:3]
    R = rotation_matrix(phi, theta, psi)
    
    # Rotate arms
    p1, p3 = R * [P.l, 0, 0], R * [-P.l, 0, 0]
    p2, p4 = R * [0, P.l, 0], R * [0, -P.l, 0]
    pz = R * [0, 0, P.d]  # Z-axis endpoint
    
    p = plot(xlim=(-0.3, 0.3), ylim=(-0.3, 0.3), zlim=(-0.3, 0.3),
             title="Drone t=$(round(t, digits=1))", camera=(45, 30), aspect_ratio=:equal)
             
    # Draw Arms
    plot!(p, [p1[1], p3[1]], [p1[2], p3[2]], [p1[3], p3[3]], lw=3, color=:red, label="Roll-Axis")
    plot!(p, [p2[1], p4[1]], [p2[2], p4[2]], [p2[3], p4[3]], lw=3, color=:blue, label="Pitch-Axis")
    # Draw Z-axis
    plot!(p, [0, pz[1]], [0, pz[2]], [0, pz[3]], lw=2, color=:green, label="Yaw-Axis")
    
    scatter!(p, [p1[1], p2[1], p3[1], p4[1], pz[1]], [p1[2], p2[2], p3[2], p4[2], pz[2]], 
             [p1[3], p2[3], p3[3], p4[3], pz[3]], markersize=4, color=:black, label=nothing)
end

gif(anim, "drone_sim.gif", fps=20)

data = CSV.read("data/log_20260204_101613_Sine.csv", DataFrame)

recorded_t = [i*0.05 for i in 0:nrow(data)-1]
recorded_roll = data.roll_actual

function pid_callback_optim!(integrator)
    c = ctrl
    state = integrator.u
    t = integrator.t
    
    # 1. Pull the reference from the recorded CSV data at this specific time
    # We use the reference column from your headerless CSV (Column2)
    # Finding the closest time row in your data:
    idx = searchsortedfirst(recorded_t, t)
    idx = clamp(idx, 1, nrow(data))
    target = deg2rad(data.roll_cmd[idx]) 
    error = target - state[1]
    
    # 2. PID Logic (Must match the real drone's logic exactly!)
    c.integral += error * P.dt_ctrl
    deriv = (error - c.prev_error) / P.dt_ctrl
    roll_moment = c.kp * error + c.ki * c.integral + c.kd * deriv
    
    # 3. Allocation
    tau_vec = [2.0, roll_moment, 0.0, 0.0]
    c.throttles = control_alloc(tau_vec)
    
    c.prev_error = error
end

# --- 2. Define the Identification Objective ---
function sys_id_objective(params)
    # Unpack parameters the optimizer is testing
    # We apply the ±10% search space here
    J_val, a_val, b_val, m_val, k_roll_drag_val = params
    
    # Create a local version of P with these guesses
    local_P = (
        J = Diagonal([J_val, 0.0268, 0.0680]), # Simplified: identifying Jxx
        a = a_val, b = b_val, m = m_val,
        k_roll_drag = k_roll_drag_val,
        g = 9.81, d = 0.05, l = 0.20,
        E = P.E, dt_ctrl = P.dt_ctrl
    )

    # Setup the problem with u0 from your recorded data
    u0_id = [deg2rad(recorded_roll[1]), 0.0, 0.0, 0.0, 0.0, 0.0]
    tspan = (recorded_t[1], recorded_t[end])
    
    # Define dynamics using the optimizer's parameters
    # Note: You should pass recorded throttles to the dynamics 
    # if you want to see how the physical model responds to real inputs
    cb = PeriodicCallback(pid_callback_optim!, P.dt_ctrl)

    prob = ODEProblem(quadrotor_dynamics!, u0_id, tspan, local_P)
    sol = solve(prob, Tsit5(), saveat=recorded_t, callback=cb, reltol=1e-8, abstol=1e-8)

    results = sol(recorded_t)
    sim_roll = [u[1] for u in results]

    # Calculate Mean Squared Error (MSE) between Sim and Real
    mse = sum((sim_roll .- deg2rad.(recorded_roll)).^2) / length(recorded_roll)
    println("Params: ", params, " MSE: ", mse)
    return mse
end

function loss_function(params, data_payload)
    # params: [Jxx, a, b, m, k_roll_drag]
    t_steps, target_roll = data_payload

    println("Testing params: ", params)
    
    # Construct parameter set for this iteration
    p_local = (
        J = Diagonal([params[1], P.J[2], P.J[3]]),
        a = params[2], 
        b = params[3], 
        m = params[4],
        k_roll_drag = params[5],
        E = P.E, g = P.g, d = P.d, l = P.l
    )

    u0 = [target_roll[1], 0.0, 0.0, 0.0, 0.0, 0.0]
    tspan = (t_steps[1], t_steps[end])

    prob = ODEProblem(quadrotor_dynamics!, u0, tspan, p_local)
    
    # solve with ForwardDiff sensitivity
    sol = solve(prob, Tsit5(), p=p_local, saveat=t_steps, 
                sensealg=ForwardDiffSensitivity(), reltol=1e-6, abstol=1e-6)

    # Calculate MSE
    sim_roll = [u[1] for u in sol.u]
    return sum(abs2, sim_roll .- target_roll) / length(target_roll)
end

p_init = [P.J[1], P.a, P.b, P.m, P.k_roll_drag]
lb = p_init .* 0.90
ub = p_init .* 1.10

# Define the problem for Optimization.jl
# AutoForwardDiff() automatically calculates the gradient for LBFGS
opt_f = OptimizationFunction(loss_function, Optimization.AutoForwardDiff())
opt_prob = OptimizationProblem(opt_f, p_init, (recorded_t, recorded_roll), lb=lb, ub=ub)

loss_function(p_init, (recorded_t, recorded_roll))

println("Starting Gradient-Based Optimization (L-BFGS)...")
res = solve(opt_prob, LBFGS(), maxiters=100)

println("--- Results ---")
println("Identified Jxx: ", res.minimizer[1])
println("Identified a:   ", res.minimizer[2])
println("Final Loss:     ", res.objective)
