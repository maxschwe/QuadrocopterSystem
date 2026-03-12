using DifferentialEquations, LinearAlgebra, DataInterpolations
using CSV, DataFrames

using Optimization, OptimizationOptimJL, ForwardDiff

using Plots

data = CSV.read("data/kp-0.8-ki-0.6-kd-0.3/trajectory_30s Benchmark_Roll_1772900959.csv", DataFrame)
recorded_t = [i * 0.02 for i in 0:nrow(data)-1]
recorded_roll = data.roll
recorded_pitch = data.pitch
recorded_yaw = data.yaw

ref_roll_itp = LinearInterpolation(data.reference_roll, recorded_t)
ref_pitch_itp = LinearInterpolation(data.reference_pitch, recorded_t)
ref_yaw_itp = LinearInterpolation(data.reference_yaw, recorded_t)

plot(recorded_t, ref_roll_itp.(recorded_t), label="Reference Roll", title="Reference Trajectory")

function quadrotor_dynamics!(du, u, p, t)
    # Use the eltype of u to ensure compatibility with Dual numbers
    T = eltype(u)
    
    η = u[1:3]
    ω = u[4:6]
    int_states = u[7:9]
    deriv_states = u[10:12]

    targets = [ref_roll_itp(t), ref_pitch_itp(t), ref_yaw_itp(t)]
    error = targets .- η
    
    control_moments = p.kp .* error .+ p.ki .* int_states .- p.kd .* deriv_states
    
    tau_ideal = [T(3.0); control_moments]
    
    f_sq = p.B_eff_inv * tau_ideal
    rpm = sqrt.(max.(f_sq, T(0.0)) ./ p.a) .+ p.b
    throttles = clamp.(rpm, T(0.15), T(0.90))

    thrusts = @. p.a * (throttles - p.b)^2
    applied_torques = (p.B_eff * thrusts)[2:4]

    sφ, cφ = sin(η[1]), cos(η[1])
    sθ, cθ = sin(η[2]), cos(η[2])
    tθ = tan(η[2])
    T_mat = [1.0  sφ*tθ  cφ*tθ;
             0.0  cφ     -sφ;
             0.0  sφ/cθ  cφ/cθ]

    # applied_torques[1] += p.m * p.g * p.h * sφ * cθ
    # applied_torques[2] += p.m * p.g * p.h * sθ 

    du[1:3] .= T_mat * ω
    du[4:6] .= p.J \ (applied_torques .- cross(ω, p.J * ω))
    du[7:9] .= error
    du[10:12] .= p.N_filter .* (ω .- deriv_states)
end

function construct_parameters(params)
    J_val = params[1]
    h_val = params[2]

    println("Testing with J_val = ", J_val, " and h_val = ", h_val)

    B_eff = [1.0 1.0 1.0 1.0; 
         0.2 0.0 -0.2 0.0; 
         0.0 0.2 0.0 -0.2; 
         0.0351 -0.0351 0.0351 -0.0351]
    B_eff_inv = inv(B_eff)

    return (
        m=1.014, g=9.81, h=h_val, 
        J=Diagonal([J_val, 0.0268, 0.0680]), 
        B_eff=B_eff,
        B_eff_inv=B_eff_inv,
        a=13.06, b=0.0859, 
        kp=[0.8, 0.8, 0.8], ki=[0.6, 0.6, 0.6], kd=[0.3, 0.3, 0.3], 
        N_filter = [100.0, 100.0, 100.0]
    )
end

# 2. Update the loss function to be more robust
function loss_function(params, _)
    T = eltype(params) 
    p_local = construct_parameters(params)
    
    # Ensure u0 starts as the correct type
    u0 = zeros(T, 12) 
    u0[1] = T(recorded_roll[1])
    u0[2] = T(recorded_pitch[1])
    u0[3] = T(recorded_yaw[1])

    prob = ODEProblem(quadrotor_dynamics!, u0, (T(recorded_t[1]), T(recorded_t[end])), p_local)
    
    # Use Sensealg for ForwardDiff to be explicit
    sol = solve(prob, Tsit5(), saveat=recorded_t, reltol=1e-6, abstol=1e-6)

    if sol.retcode != ReturnCode.Success
        return T(1e9) 
    end

    res_roll = [u[1] for u in sol.u]
    # res_pitch = [u[2] for u in sol.u]
    # res_yaw = [u[3] for u in sol.u]
    
    mse = sum((res_roll .- recorded_roll).^2 ./ length(recorded_t))
    
    return mse
end

# --- Running the Identification ---
d_init = [0.0258, 0.05]

initial_loss = loss_function(d_init, nothing)
println("Initial Loss: ", initial_loss)
sol_initial = solve(ODEProblem(quadrotor_dynamics!, zeros(12), (recorded_t[1], recorded_t[end]), construct_parameters(d_init)), Tsit5(), saveat=recorded_t)

plot(recorded_t, [recorded_roll, data.roll_predicted, [u[1] for u in sol_initial.u]], label=["Measured Roll" "Internal Predicted" "Initial Model Roll"], title="Initial Model Performance")

lb = 0.8 * d_init
ub = 1.2 * d_init

opt_f = OptimizationFunction(loss_function, Optimization.AutoForwardDiff())
opt_prob = OptimizationProblem(opt_f, d_init, lb=lb, ub=ub)

println("Starting Optimization...")
res = solve(opt_prob, BFGS(), maxiters=100, maxtime=60.0)

println("Identified Coefficients: ", res.minimizer)

loss = loss_function(res.minimizer, nothing)
println("Final Loss: ", loss)

# --- Plotting Results ---
p_final = construct_parameters(res.minimizer)
prob_final = ODEProblem(quadrotor_dynamics!, zeros(12), (recorded_t[1], recorded_t[end]), p_final)
sol_final = solve(prob_final, Tsit5(), saveat=recorded_t)

plot(recorded_t, [ref_roll_itp.(recorded_t) * 180 / π, recorded_roll * 180 / π, [u[1] * 180 / π for u in sol_initial.u], [u[1] * 180 / π for u in sol_final.u]], 
     label=["Reference" "Measured Roll" "Initial Model Roll" "Identified Model Roll"], title="Identification Results")

# identified: h = 0.03369, J = 0.0235
# identified: h = 0.036, J = 0.02738
