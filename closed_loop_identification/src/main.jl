using Statistics
using Plots

include("params.jl")
include("training_data.jl")
include("identification.jl")

const DATA_PATH = "./data"

dirs = filter(d -> isdir(joinpath(DATA_PATH, d)), readdir(DATA_PATH))

J_identified_values = [Float64[] for _ in 1:3]
p_identified_values = [Float64[] for _ in 1:3]
h_identified_values = Float64[]

loss_total = 0.0

for d in dirs
    params = load_config(joinpath(DATA_PATH, d, "params.json"))
    println("Loaded parameters for directory: $d  kp=$(params.kp)  ki=$(params.ki)  kd=$(params.kd)")

    for (i, axis) in enumerate(instances(Axis))
        J_key = Dict(Roll => :J_xx, Pitch => :J_yy, Yaw => :J_zz)[axis]
        P_key = Dict(Roll => :p_x, Pitch => :p_y, Yaw => :p_z)[axis]

        to_opt = Dict(J_key => OptimParam(), P_key => OptimParam(0.001, 100.0), :h => OptimParam())
        if axis != Yaw
            to_opt[:h] = OptimParam()
        end

        for num in 1:3
            file_path = joinpath(DATA_PATH, d, "$(lowercase(string(axis)))$num.csv")

            identified_params, loss = opt_params(TrainingData(file_path, axis), params, to_opt)

            push!(J_identified_values[i], identified_params[J_key])
            push!(p_identified_values[i], identified_params[P_key])
            axis != Yaw && push!(h_identified_values, identified_params[:h])
            loss_total += loss
        end
    end
end

J_identified = mean.(J_identified_values)
p_identified = mean.(p_identified_values)
h_identified = mean(h_identified_values)

println("J identified: $J_identified")
println("p identified: $p_identified")
println("h identified: $h_identified")
println("Total loss: $loss_total")

function compare_plot(dir, filename, axis::Axis)
    data = TrainingData(joinpath(dir, filename), axis)

    # Initial Param Sim
    initial_params = load_config(joinpath(dir, "params.json"))
    before_params = update_params(initial_params, Dict(:p_x => 0.0, :p_y => 0.0, :p_z => 0.0))

    sim_before, loss_before = eval_sim(data, before_params)

    # Optimized Param Sim
    optimized_overrides = Dict(
        :J_xx => J_identified[1], :J_yy => J_identified[2], :J_zz => J_identified[3],
        :p_x => p_identified[1], :p_y => p_identified[2], :p_z => p_identified[3],
        :h => h_identified
    )
    final_params = update_params(initial_params, optimized_overrides)
    sim_after, loss_after = eval_sim(data, final_params)

    plt = plot(data.timesteps, data.measured, 
        label="Measured (Ground Truth)", lw=2, color=:red, ls=:dot,
        title="Parameter Identification Results: $(axis) Axis",
        xlabel="Time (s)", ylabel="Angle (rad)", legend=:outertopright, size=(800, 800))

    # plot!(plt, data.timesteps, [ref[1] for ref in data.reference.ref_η.(data.timesteps)], 
    #     label="Reference Trajectory", lw=2, color=:black)

    # plot!(plt, data.timesteps, data.onboard_predicted, 
    #     label="Onboard Model Prediction", lw=1.5, color=:orange)

    plot!(plt, data.timesteps, sim_before, 
        label="Sim (Initial)", lw=1.5, color=:blue, alpha=0.6)

    plot!(plt, data.timesteps, sim_after, 
        label="Sim (Optimized)", lw=2, color=:green, alpha=0.8)

    println("Loss Before Optimization: $loss_before")
    println("Loss After Optimization: $loss_after")

    display(plt)

    df = DataFrame(
        time = data.timesteps,
        measured = rad2deg.(data.measured),
        sim_initial = rad2deg.(sim_before),
        sim_optimized = rad2deg.(sim_after)
    )

    output_path = joinpath("plot_data_$(filename).csv")
    CSV.write(output_path, df)
end

compare_plot(joinpath("data", "Test3"), "roll3.csv", Roll)
