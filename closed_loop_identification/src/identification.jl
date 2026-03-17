using Optim
using ADTypes

include("sim.jl")

function eval_sim(training_data::TrainingData, params::Params)
    sol = sim(training_data.timesteps, training_data.reference, training_data.u0, params)
    sim_data = [u[Int(training_data.axis)] for u in sol.u]

    loss = sum((training_data.measured .- sim_data) .^ 2) / length(training_data.timesteps)
    return sim_data, loss
end

function opt_params(training_data::TrainingData, params::Params, to_opt_params::Dict{Symbol,OptimParam})
    to_opt_keys = collect(keys(to_opt_params))
    to_opt_values = [getfield(params, k) for k in to_opt_keys]
    to_opt_lb = [getfield(params, k) * to_opt_params[k].lb_factor for k in to_opt_keys]
    to_opt_ub = [getfield(params, k) * to_opt_params[k].ub_factor for k in to_opt_keys]

    function objective(opt_vars)
        overrides = Dict{Symbol,Any}(k => opt_vars[i] for (i, k) in enumerate(to_opt_keys))
        new_params = update_params(params, overrides)
        _, loss = eval_sim(training_data, new_params)
        return loss
    end

    println("Optimizing $to_opt_params with $(training_data.csv_path); initial loss: $(objective(to_opt_values))")

    result = optimize(objective, to_opt_lb, to_opt_ub, to_opt_values, Fminbox(BFGS()), Optim.Options(
            time_limit=30.0,
            show_trace=false,
            f_reltol = 0.5e-2,
        ), autodiff=AutoForwardDiff())

    optimized_params = Dict(k => result.minimizer[i] for (i, k) in enumerate(to_opt_keys))

    display(result)

    return optimized_params, result.minimum
end
