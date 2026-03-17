using JSON3

const DEFAULT_B_EFF = [
    1.0     1.0    1.0     1.0;
    0.2     0.0   -0.2     0.0;
    0.0     0.2    0.0    -0.2;
    0.0351 -0.0351  0.0351 -0.0351
]

Base.@kwdef struct OptimParam
    lb_factor = 0.80
    ub_factor = 1.20
end

Base.@kwdef struct Params
    kp= 1.0
    ki = 0.1
    kd = 0.05

    N_filter = 100.0

    m = 1.210
    g = 9.81
    a = 13.06
    b = 0.0859
    thrust = 3.0

    B_eff = DEFAULT_B_EFF
    B_eff_inv = inv(DEFAULT_B_EFF)

    J_xx = 0.0258
    J_yy = 0.0268
    J_zz = 0.0680

    p_x = 0.0
    p_y = 0.0
    p_z = 0.0

    h = 0.05
end

function update_params(base::Params, overrides::Dict{Symbol})
    fields = fieldnames(Params)
    values = [get(overrides, f, getfield(base, f)) for f in fields]
    return Params(; zip(fields, values)...)
end

function load_config(json_path::String; base::Params = Params())
    data = JSON3.read(read(json_path, String))

    return update_params(base, Dict{Symbol, Any}(
        :kp => data.kp,
        :ki => data.ki,
        :kd => data.kd,
    ))
end
