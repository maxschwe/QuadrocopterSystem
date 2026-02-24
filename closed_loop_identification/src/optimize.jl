using DifferentialEquations, LinearAlgebra, Plots, CSV, DataFrames, Optim
using Optimization, OptimizationOptimJL, ForwardDiff, SciMLSensitivity

data = CSV.read("../recordings/trajectory_30s Benchmark_1771925754.csv", DataFrame)

recorded_t = [i * 0.005 for i in 0:nrow(data)-1]
recorded_roll = data.roll

function reference_roll(t)
    idx = searchsortedfirst(recorded_t, t)
    idx = clamp(idx, 1, nrow(data))
    target = data.reference_roll[idx]
    return target
end

function quadrotor_dynamics!(du, u, p, t)
    ϕ, θ = u[1], u[2]
    ω = u[4:6]
    int_err = u[7]
    deriv_state = u[8] # The "memory" for the filtered derivative

    # 1. Calculate Error
    target = reference_roll(t)
    error = target - ϕ
    
    # 2. Filtered Derivative Logic
    # This acts like a low-pass filter on the D-term
    # D_out = N * (kd * error - deriv_state)
    d_term = p.N_filter * p.kd * ω[1]
    
    # 3. Control Allocation
    roll_moment = p.kp * error + p.ki * int_err + d_term
    tau_vec = [3.0, roll_moment, 0.0, 0.0]
    
    f_sq = p.E \ tau_vec
    rpm = sqrt.(max.(f_sq, 0.0) ./ p.a) .+ p.b
    throttles = clamp.(rpm, 0.15, 0.90)
    thrusts = @. p.a * (throttles - p.b)^2

    # Kinematics
    sφ, cφ = sin(ϕ), cos(ϕ)
    sθ, tθ, cθ = sin(θ), tan(θ), cos(θ)
    W = [1 sφ*tθ cφ*tθ;
        0 cφ -sφ;
        0 sφ/cθ cφ/cθ]

    # Forces/Torques
    torques = (p.E*thrusts)[2:4]
    torques[1] += p.m * p.g * p.d * sφ * cθ

    damping_torques = [p.k_roll_drag * ω[1], 0.0, 0.0]

    # Derivatives
    du[1:3] = W * ω
    du[4:6] = p.J \ (torques - damping_torques - cross(ω, p.J * ω))
    du[7] = error # Derivative of integral is the error
    du[8] = d_term # Update the filtered derivative state
end

function construct_parameters(params)
    k_roll_drag = params[1]
    return (
        m=1.014, g=9.81, d=0.03, 
        J=Diagonal([0.0258, 0.0268, 0.0680]), 
        E=[
            1.0 1.0 1.0 1.0;
            0.0 -0.2 0.0 0.2;
            0.2 0.0 -0.2 0.0;
            0.0351 -0.0351 0.0351 -0.0351
        ],
        a=13.0, b=0.085908, 
        k_roll_drag=k_roll_drag,
        kp=0.8, ki=0.3, kd=1.5, N_filter = 100.0,)
end

function sim_system(params)
    u0 = [recorded_roll[1], 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0] # Include filtered derivative state
    tspan = (recorded_t[1], recorded_t[end])

    p_local = construct_parameters(params)
    prob = ODEProblem(quadrotor_dynamics!, u0, tspan, p_local)
    sol = solve(prob, Tsit5(), saveat=recorded_t, reltol=1e-6, abstol=1e-6)
    print(params, " final error: ", sum(abs2, data.roll .- [u[1] for u in sol.u]) / length(sol.u), "\n")

    return [u[1] for u in sol.u]
end

p_init = [0.1]
data_sim_old_model = sim_system(p_init)

function loss_function(params, recorded_roll)
    sim_roll = sim_system(params)
    return sum(abs2, sim_roll .- recorded_roll) / length(recorded_roll)
end

lb = 0.8 * p_init
ub = 1.2 * p_init

opt_f = OptimizationFunction(loss_function, Optimization.AutoForwardDiff())
opt_prob = OptimizationProblem(opt_f, p_init, recorded_roll, lb=lb, ub=ub)

println("Starting Optimization...")
res = solve(opt_prob, BFGS(), maxiters=5, maxtime=30.0)

println("--- Results ---")
println("Identified k_roll_drag: ", res.minimizer[1])

# Loss custom fitted system
loss_function((0.2), recorded_roll)

# Loss for optimizer fitted system
loss_function(res.minimizer, recorded_roll)

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
