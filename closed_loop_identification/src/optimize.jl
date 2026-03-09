using DifferentialEquations, LinearAlgebra, Plots, CSV, DataFrames, Optim
using Optimization, OptimizationOptimJL, ForwardDiff, SciMLSensitivity

data = CSV.read("./data/kp-1.2-ki-0.3-kd-0.1/trajectory_30s Benchmark_Roll_1772900591.csv", DataFrame)

recorded_t = [i * 0.02 for i in 0:nrow(data)-1]
recorded_roll = data.roll
recorded_pitch = data.pitch
recorded_yaw = data.yaw

function references(t)
    idx = searchsortedfirst(recorded_t, t)
    idx = clamp(idx, 1, nrow(data))
    targets = [data.reference_roll[idx], data.reference_pitch[idx], data.reference_yaw[idx]]
    return targets
end

function quadrotor_dynamics!(du, u, p, t)
    η = u[1:3]
    ω = u[4:6]
    int_states = u[7:9]
    deriv_states = u[10:12]

    # PID Controllers
    targets = references(t)
    error = targets - η
    
    control_moments = p.kp .* error + p.ki .* int_states - p.kd .* deriv_states
    
    # Control allocation: Moments -> Throttles
    tau = [3.0; control_moments]
    f_sq = p.B_eff \ tau
    rpm = sqrt.(max.(f_sq, 0.0) ./ p.a) .+ p.b
    throttles = clamp.(rpm, 0.15, 0.90)

    # Thrusters model
    thrusts = @. p.a * (throttles - p.b)^2
    torques = (p.B_eff * thrusts)[2:4]

    # Angular velocity to Euler rate mapping
    sφ, cφ = sin(η[1]), cos(η[1])
    sθ, tθ, cθ = sin(η[2]), tan(η[2]), cos(η[2])
    T = [1.0  sφ*tθ  cφ*tθ;
         0.0  cφ     -sφ;
         0.0  sφ/cθ  cφ/cθ]

    # Rotation dynamics
    torques[1] += p.m * p.g * p.h * sφ * cθ
    torques[2] += p.m * p.g * p.h * sθ 

    # Add damping torques
    torques += -p.d .* ω
    
    du[1:3] = T * ω
    du[4:6] = p.J \ (torques - cross(ω, p.J * ω))
    du[7:9] = error
    du[10:12] = p.N_filter .* (ω - deriv_states)
end

function construct_parameters(params)
    d_x = params[1]
    d_y = params[2]
    d_z = params[3]
    return (
        m=1.014, g=9.81, h=0.05, 
        J=Diagonal([0.0308, 0.0268, 0.0680]), 
        B_eff=[
            1.0 1.0 1.0 1.0;
            0.2 0.0 -0.2 0.0;
            0.0 0.2 0.0 -0.2;
            0.0351 -0.0351 0.0351 -0.0351
        ],
        a=13.06, b=0.0859, 
        d = [d_x, d_y, d_z],
        kp=[1.2, 1.2, 1.2], ki=[0.3, 0.3, 0.3], kd=[0.1, 0.1, 0.1], N_filter = [100.0, 100.0, 100.0])
end

function loss_function(params)
    sim_roll, sim_pitch, sim_yaw = sim_system(params)
    return (sum(abs2, sim_roll .- recorded_roll) + sum(abs2, sim_pitch .- recorded_pitch) + sum(abs2, sim_yaw .- recorded_yaw)) / length(recorded_roll)
end

function sim_system(params)
    u0 = zeros(12)
    u0[1] = recorded_roll[1]
    u0[2] = recorded_pitch[1]
    u0[3] = recorded_yaw[1]
    u0[4] = data.value4[1]
    u0[5] = data.value5[1]
    u0[6] = data.value6[1]
    tspan = (recorded_t[1], recorded_t[end])

    p_local = construct_parameters(params)
    prob = ODEProblem(quadrotor_dynamics!, u0, tspan, p_local)
    sol = solve(prob, Tsit5(), saveat=recorded_t, reltol=1e-6, abstol=1e-6)

    return [u[1] for u in sol.u], [u[2] for u in sol.u], [u[3] for u in sol.u]
end

d_x_init = 0.0
d_y_init = 0.0
d_z_init = 0.0

params_init = [d_x_init, d_y_init, d_z_init]
simulated_roll, simulated_pitch, simulated_yaw = sim_system(params_init)

plot(
    recorded_t,
    [data.roll data.roll_predicted simulated_roll],
    xlabel="Time (s)", ylabel="Roll Angle (deg)", title="Roll Angle Comparison",
    legend=:bottomright,
    label=["Roll measured" "Roll predicted" "Roll simulated"],
    size=(1200, 800)
)

lb = 0.0 * params_init
ub = 2.0 * params_init

opt_f = OptimizationFunction(loss_function, Optimization.AutoForwardDiff())
opt_prob = OptimizationProblem(opt_f, params_init, lb=lb, ub=ub)

println("Starting Optimization...")
res = solve(opt_prob, BFGS(), maxiters=5, maxtime=30.0)

println("--- Results ---")
println("Identified k_roll_drag: ", res.minimizer[1])

# Loss custom fitted system
loss_function((0.2))

# Loss for optimizer fitted system
loss_function(res.minimizer)

optimizer_fitted_sim_data = sim_system([0.18])
self_fitted_sim_data = sim_system([0.18]) # Simulate a self-fitted model

plot(
    recorded_t,
    [data.reference_roll data.roll data_sim_old_model optimizer_fitted_sim_data self_fitted_sim_data],
    xlabel="Time (s)", ylabel="Roll Angle (deg)", title="Roll Angle Comparison",
    legend=:bottomright,
    label=["Roll reference" "Roll measured" "Roll old model" "Roll optimizer fitted model" "Roll self fitted model"]
)

# Generate Loss Landscape Plot
drag_range = 0.0:0.02:0.5      # Slightly coarser step to save time
inertia_range = 0.02:0.001:0.04

p1 = plot(drag_range, inertia_range, (d, j) -> loss_function((d, j)), 
    st = :surface, 
    xlabel = "k_roll_drag", 
    ylabel = "J_xx", 
    zlabel = "MSE Loss",
    title = "Quadrotor Loss Landscape",
    color = :viridis)

display(p1)
