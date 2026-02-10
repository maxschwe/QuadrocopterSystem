using DifferentialEquations, LinearAlgebra, Plots, CSV, DataFrames, Optim
using Optimization, OptimizationOptimJL, ForwardDiff, SciMLSensitivity

data = CSV.read("data/log_20260210_141438_Sine.csv", DataFrame)

recorded_t = [i*0.005 for i in 0:nrow(data)-1]
recorded_roll = data.roll_actual
modeled_roll = data.roll_modeled

function reference_roll(t)
    idx = searchsortedfirst(recorded_t, t)
    idx = clamp(idx, 1, nrow(data))
    target = deg2rad(data.roll_cmd[idx]) 
    return target
end

# --- 1. Parameters & Configuration ---
const P = (
    J = Diagonal([0.0258, 0.0268, 0.0680]),
    a = 13.0, b = 0.085908, c = 0.0351, 
    l = 0.20,
    E = [1.0  1.0  1.0  1.0;
           0.0 -0.2  0.0  0.2;
           0.2  0.0 -0.2  0.0;
           0.0351 -0.0351 0.0351 -0.0351],
    k_roll_drag = 0.1,
    m = 1.014,
    g = 9.81,
    d = 0.02,
    dt_ctrl = 0.005
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
    0.8, 0.8, 0.35, 
    0.0, 0.0, 
    zeros(4), 
    reference_roll
)

function control_alloc(tau)
    # Solve mixing: Torques -> Squared Thrusts -> RPM
    f_sq = P.E \ tau
    rpm = sqrt.(max.(f_sq, 0.0) ./ P.a) .+ P.b
    return clamp.(rpm, 0.15, 0.90)
end

function pid_callback!(integrator)
    state = integrator.u
    t = integrator.t
    
    # 1. Sense: Roll error
    target = ctrl.target_func(t)
    error = target - state[1]

    # 2. PID Logic
    ctrl.integral += error * integrator.p.dt_ctrl
    deriv = (error - ctrl.prev_error) / integrator.p.dt_ctrl
    roll_moment = ctrl.kp * error + ctrl.ki * ctrl.integral + ctrl.kd * deriv
    
    # 3. Control Allocation
    # [Thrust, Roll Moment, Pitch, Yaw]
    tau_vec = [2.0, roll_moment, 0.0, 0.0]
    ctrl.throttles = control_alloc(tau_vec)
    
    # 4. Update internal state
    ctrl.prev_error = error
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
    du[1:3] = W * ω
    du[4:6] = p.J \ (torques - damping_torques - cross(ω, p.J * ω))
end

# --- 4. Simulation Execution ---
tspan = (recorded_t[1], recorded_t[end])
trange = tspan[1]:0.005:tspan[2]

prob = ODEProblem(quadrotor_dynamics!, u0, tspan, P; callback=cb)
sol = solve(prob, Tsit5(), reltol=1e-8, abstol=1e-8)

# --- 5. Visualization ---
# Main state plot
plot(
    recorded_t,
    [data.roll_cmd data.roll_actual [u[1] |> rad2deg for u in sol(recorded_t)]],
    xlabel="Time (s)", ylabel="Roll Angle (deg)", title="Roll Angle Comparison",
    legend=:bottomright,
    label=["Roll reference" "Roll measured" "Roll old model"]
)
