using CSV
using DataFrames
using DataInterpolations

@enum Axis Roll=1 Pitch=2 Yaw=3

struct ReferenceData
    ref_η::Function
    ref_ω::Function

    function ReferenceData(data::DataFrame, timesteps::Vector{Float64})
        roll  = LinearInterpolation(data.reference_roll,  timesteps)
        pitch = LinearInterpolation(data.reference_pitch, timesteps)
        yaw   = LinearInterpolation(data.reference_yaw,   timesteps)

        ref_η = t -> [roll(t), pitch(t), yaw(t)]
        ref_ω = t -> [DataInterpolations.derivative(roll, t), DataInterpolations.derivative(pitch, t), DataInterpolations.derivative(yaw, t)]

        new(ref_η, ref_ω)
    end
end

struct TrainingData
    csv_path::String
    axis::Axis
    timesteps::Vector{Float64}
    measured::Vector{Float64}
    onboard_predicted::Vector{Float64}
    reference::ReferenceData
    u0::Vector{Float64}

    function TrainingData(csv_path::String, axis::Axis)
        data = CSV.read(csv_path, DataFrame)

        start_time_ms = data.time_ms[1]
        timesteps = (data.time_ms .- start_time_ms) ./ 1000.0

        if axis == Roll
            measured = data.roll
            onboard_predicted = data.roll_predicted
        elseif axis == Pitch
            measured = data.pitch
            onboard_predicted = data.pitch_predicted
        else
            measured = data.yaw
            onboard_predicted = data.yaw_predicted
        end

        reference = ReferenceData(data, timesteps)

        u0 = zeros(12)
        u0[1] = data.roll[1]
        u0[2] = data.pitch[1]
        u0[3] = data.yaw[1]

        new(csv_path, axis, timesteps, measured, onboard_predicted, reference, u0)
    end
end
