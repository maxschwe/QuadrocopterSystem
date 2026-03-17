using OrdinaryDiffEq
using LinearAlgebra

function sim(timesteps, reference::ReferenceData, u0, params::Params)
    relevant_fields = [:kp, :ki, :kd, :m, :g, :a, :b, :J_xx, :J_yy, :J_zz, :h, :thrust]
    T = mapreduce(f -> typeof(getfield(params, f)), promote_type, relevant_fields, init=eltype(u0))
    u0 = T.(u0)

    J = [
        params.J_xx 0.0 0.0;
        0.0 params.J_yy 0.0;
        0.0 0.0 params.J_zz
    ]

    function quadrotor_dynamics!(du, u, p, t)
        η          = u[1:3]
        ω          = u[4:6]
        int_states = u[7:9]
        filt_e_dot = u[10:12]

        error     = reference.ref_η(t) .- η
        error_dot = reference.ref_ω(t) .- ω

        control_moments = p.kp .* error .+ p.ki .* int_states .+ p.kd .* filt_e_dot

        u_generalized       = [p.thrust; control_moments]
        f_sq                = p.B_eff_inv * u_generalized
        throttles_unclamped = sqrt.(max.(f_sq, 0.0) ./ p.a) .+ p.b
        throttles           = clamp.(throttles_unclamped, 0.15, 0.90)

        thrusts        = @. p.a * (throttles - p.b)^2
        generated_torques = (p.B_eff * thrusts)[2:4]

        sφ, cφ = sin(η[1]), cos(η[1])
        sθ, cθ = sin(η[2]), cos(η[2])
        tθ     = tan(η[2])

        W = [1.0  sφ*tθ  cφ*tθ;
             0.0  cφ     -sφ;
             0.0  sφ/cθ  cφ/cθ]

        applied_torques = [
            generated_torques[1] + p.m * p.g * p.h * sφ * cθ - p.p_x * ω[1],
            generated_torques[2] + p.m * p.g * p.h * sθ - p.p_y * ω[2],
            generated_torques[3] - p.p_z * ω[3]
        ]

        du[1:3]   .= W * ω
        du[4:6]   .= J \ (applied_torques.- cross(ω, J * ω))
        du[7:9]   .= error
        du[10:12] .= p.N_filter .* (error_dot .- filt_e_dot)
    end

    tspan = (timesteps[1], timesteps[end])
    prob  = ODEProblem(quadrotor_dynamics!, u0, tspan, params)
    sol   = solve(prob, Tsit5(), saveat=timesteps)
    return sol
end
