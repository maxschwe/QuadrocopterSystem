using DifferentialEquations, LinearAlgebra, DataInterpolations
using CSV, DataFrames, JSON3, Statistics

using Optimization, OptimizationOptimJL, ForwardDiff

using Plots

function optimize_params_with_data(path, axis, kp, ki, kd)
    data = CSV.read(path, DataFrame)
    recorded_t = [i * 0.02 for i in 0:nrow(data)-1]

    ref_roll = LinearInterpolation(data.reference_roll, recorded_t)
    ref_pitch = LinearInterpolation(data.reference_pitch, recorded_t)
    ref_yaw = LinearInterpolation(data.reference_yaw, recorded_t)

    ref_roll_dot = t -> DataInterpolations.derivative(ref_roll, t)
    ref_pitch_dot = t -> DataInterpolations.derivative(ref_pitch, t)
    ref_yaw_dot = t -> DataInterpolations.derivative(ref_yaw, t)

    plot(recorded_t, [ref_roll.(recorded_t), ref_roll_dot.(recorded_t)], label=["Reference Roll" "Reference Roll Dot"], title="Reference Trajectory")

    function construct_parameters(params)
        J_val = params[1]
        h_val = params[2]

        # println("Testing with J_val = ", J_val, " and h_val = ", h_val)

        B_eff = [1.0 1.0 1.0 1.0; 
            0.2 0.0 -0.2 0.0; 
            0.0 0.2 0.0 -0.2; 
            0.0351 -0.0351 0.0351 -0.0351]
        B_eff_inv = inv(B_eff)

        if axis == "roll"
            J=Diagonal([J_val, 0.0268, 0.0680])
        elseif axis == "pitch"
            J=Diagonal([0.0258, J_val, 0.0680])
        else
            J=Diagonal([0.0258, 0.0268, J_val])
        end 

        return (
            m=1.210, g=9.81, h=h_val, 
            J=J,
            B_eff=B_eff,
            B_eff_inv=B_eff_inv,
            a=13.06, b=0.0859,
            kp=kp * ones(3), ki=ki * ones(3), kd=kd * ones(3),
            N_filter = [100.0, 100.0, 100.0],
            thrust = 3.0,
        )
    end

    function quadrotor_dynamics!(du, u, p, t)
        # Use the eltype of u to ensure compatibility with Dual numbers
        T = eltype(u)
        
        η = u[1:3]
        ω = u[4:6]
        int_states = u[7:9]
        filt_e_dot = u[10:12]

        targets = [ref_roll(t), ref_pitch(t), ref_yaw(t)]
        targets_dot = [ref_roll_dot(t), ref_pitch_dot(t), ref_yaw_dot(t)]

        # 3-DOF PID control
        error = targets .- η
        error_dot = targets_dot .- ω
        
        control_moments = p.kp .* error .+ p.ki .* int_states .+ p.kd .* filt_e_dot
        
        # control alloc
        u_generalized = [T(p.thrust); control_moments]
        f_sq = p.B_eff_inv * u_generalized
        throttles_unclamped = sqrt.(max.(f_sq, T(0.0)) ./ p.a) .+ p.b
        throttles = clamp.(throttles_unclamped, T(0.15), T(0.90))

        # propulsion model
        thrusts = @. p.a * (throttles - p.b)^2
        applied_torques = (p.B_eff * thrusts)[2:4]

        # angular velocity to Euler rate mapping
        sφ, cφ = sin(η[1]), cos(η[1])
        sθ, cθ = sin(η[2]), cos(η[2])
        tθ = tan(η[2])
        T = [1.0  sφ*tθ  cφ*tθ;
                0.0  cφ     -sφ;
                0.0  sφ/cθ  cφ/cθ]

        # dynamics model
        applied_torques[1] += p.m * p.g * p.h * sφ * cθ
        applied_torques[2] += p.m * p.g * p.h * sθ 

        du[1:3] .= T * ω
        du[4:6] .= p.J \ (applied_torques .- cross(ω, p.J * ω))
        du[7:9] .= error
        du[10:12] .= p.N_filter .* (error_dot .- filt_e_dot)
    end

    function get_sol(params)
        T = eltype(params) 
        p_local = construct_parameters(params)
        
        # Ensure u0 starts as the correct type
        u0 = zeros(T, 12) 
        u0[1] = T(data.roll[1])
        u0[2] = T(data.pitch[1])
        u0[3] = T(data.yaw[1])

        prob = ODEProblem(quadrotor_dynamics!, u0, (T(recorded_t[1]), T(recorded_t[end])), p_local)
        
        sol = solve(prob, Tsit5(), saveat=recorded_t, reltol=1e-6, abstol=1e-6)
        return sol
    end

    function loss(sol)
        if axis == "roll"
            recorded = data.roll
            sim_data = [u[1] for u in sol.u]
        elseif axis == "pitch"
            recorded = data.pitch
            sim_data = [u[2] for u in sol.u]
        else
            recorded = data.yaw
            sim_data = [u[3] for u in sol.u]
        end

        mse = sum((sim_data .- recorded).^2) / length(recorded)
        return mse
    end

    function optimization_function(params, _)
        sol = get_sol(params)

        loss_value = loss(sol)
        
        return loss_value
    end

    function eval_sim(params)
        sol = get_sol(params)
        loss_value = loss(sol)
        
        return [u[1] for u in sol.u], loss_value
    end

    # --- Running the Identification ---
    if axis == "roll"
        println("Optimizing for Roll axis...")
        d_init = [0.0258, 0.05]
        onboard_predicted = data.roll_predicted
        measured = data.roll
    elseif axis == "pitch"
        println("Optimizing for Pitch axis...")
        d_init = [0.0268, 0.05]
        onboard_predicted = data.pitch_predicted
        measured = data.pitch
    else
        println("Optimizing for Yaw axis...")
        d_init = [0.0680, 0.05]
        onboard_predicted = data.yaw_predicted
        measured = data.yaw
    end

    initial_sim_data, loss_initial = eval_sim(d_init)
    println("Initial Loss: ", loss_initial)
    plot(recorded_t, [measured, onboard_predicted, initial_sim_data], label=["Measured" "Onboard Modeled" "Julia Modeled"], title="Initial Model Performance")

    lb = 0.70 * d_init
    ub = 1.30 * d_init

    opt_f = OptimizationFunction(optimization_function, Optimization.AutoForwardDiff())
    opt_prob = OptimizationProblem(opt_f, d_init, lb=lb, ub=ub)

    println("Starting Optimization...")
    res = solve(opt_prob, BFGS(), maxiters=100, maxtime=30.0)
    println("Termination Reason: ", res.retcode)

    optimized_sim_data, optimized_loss = eval_sim(res.minimizer)
    println("Final Loss: ", optimized_loss)

    plot(recorded_t, [ref_roll.(recorded_t) * 180 / π, measured * 180 / π, initial_sim_data * 180 / π, optimized_sim_data * 180 / π], 
        label=["Reference" "Measured Roll" "Initial Model Roll" "Optimized Model Roll"], title="Identification Results")
    
    return res.minimizer, optimized_loss
end

# identified: h = 0.03369, J = 0.0235
# identified: h = 0.036, J = 0.02738

path = "./data"

dirs = [d for d in readdir(path) if isdir(joinpath(path, d))]

J_identified_values = [[] for _ in 1:3]
h_identified_values = []

for d in dirs
    json_file = joinpath(path, d, "params.json")
    json_string = read(json_file, String)
    data = JSON3.read(json_string)
    println("Loaded parameters for directory: ", d, " with kp: ", data.kp, ", ki: ", data.ki, ", kd: ", data.kd)

    for (i, axis) in enumerate(["roll", "pitch", "yaw"])
        for num in 1:3
            file_path = joinpath(path, d, "$axis$num.csv")
            println("Processing file: ", file_path)
            params, loss = optimize_params_with_data(file_path, axis, data.kp, data.ki, data.kd)
            println("Optimized parameters for ", axis, ": ", params, " with loss: ", loss)

            push!(J_identified_values[i], params[1])
            push!(h_identified_values, params[2])
        end
    end
end

J_identified = [mean(J_identified_values[i]) for i in 1:3]
h_identified = mean(h_identified_values)

# 3-element Vector{Float64}:
# J_xx  0.030468012288083865
# J_yy  0.031451597116136175
# J_zz  0.047614690524708826

# h = 0.04423048673551669
