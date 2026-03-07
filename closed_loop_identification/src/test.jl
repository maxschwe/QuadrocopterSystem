using DifferentialEquations, LinearAlgebra, Plots, CSV, DataFrames, Optim
using Optimization, OptimizationOptimJL, ForwardDiff, SciMLSensitivity

data = CSV.read("../recordings/trajectory_30s Benchmark_Roll_1772900591.csv", DataFrame)

recorded_t = [i * 0.02 for i in 0:nrow(data)-1]
recorded_roll = data.roll

function reference_roll(t)
    idx = searchsortedfirst(recorded_t, t)
    idx = clamp(idx, 1, nrow(data))
    target = data.reference_roll[idx]
    return target
end

function quadrotor_dynamics!(du, u, p, t)
    # u[1:3] = [phi, theta, psi], u[4:6] = omega
    # u[7] = Integrator_CSTATE_c (Roll Integral)
    # u[8] = Filter_CSTATE (Roll Filter)
    
    phi = u[1]
    omega_x = u[4]
    
    # 1. Error Signal
    target = reference_roll(t)
    error = target - phi
    
    # 2. PID Terms matching Simulink 'step()' logic
    # Derivative on measurement: -Kd * velocity
    # Note: In your code: rtDW.SumD = p.kd * -u[4] - p.N * u[8]
    rtb_Sum2 = p.N * u[8] # Filtered state output
    
    # Control output (Roll Moment)
    roll_moment = (p.kp * error + u[7]) + rtb_Sum2
    
    # 3. Mixer and Actuator Dynamics
    tau_vec = [3.0, roll_moment, 0.0, 0.0]
    f_sq = p.B_eff \ tau_vec
    
    # Motor RPM and Saturation
    rpm_raw = sqrt.(max.(f_sq, 0.0) ./ p.a) .+ p.b
    throttles = clamp.(rpm_raw, p.LowerSat, p.UpperSat)
    thrusts = @. p.a * (throttles - p.b)^2

    # 4. Physical Derivatives (Rigid Body)
    sφ, cφ = sin(phi), cos(phi)
    sθ, tθ, cθ = sin(u[2]), tan(u[2]), cos(u[2])
    W = [1 sφ*tθ cφ*tθ; 0 cφ -sφ; 0 sφ/cθ cφ/cθ]

    torques = (p.B_eff * thrusts)[2:4]
    torques[1] += p.m * p.g * p.d * sφ * cθ 
    damping = [p.k_roll_drag * u[4], 0.0, 0.0]

    du[1:3] = W * u[4:6]
    du[4:6] = p.J \ (torques - damping - cross(u[4:6], p.J * u[4:6]))

    # 5. Controller State Derivatives (The "Fix")
    # Matches: _rtXdot->Integrator_CSTATE_c = rtDW.IntegralGain_j;
    du[7] = p.ki * error 
    
    # Matches: _rtXdot->Filter_CSTATE = rtDW.SumD;
    # SumD = (p.kd * -velocity) - (p.N * filter_state)
    du[8] = (p.kd * -u[4]) - (p.N * u[8])
end

function construct_parameters(params)
    k_roll_drag = params[1]
    return (
        m=1.014, g=9.81, d=0.05, 
        J=Diagonal([0.0258, 0.0268, 0.0680]), 
        B_eff=[
            1.0 1.0 1.0 1.0;
            0.2 0.0 -0.2 0.0;
            0.0 0.2 0.0 -0.2;
            0.0351 -0.0351 0.0351 -0.0351
        ],
        a=13.06, b=0.0859,
        k_roll_drag=k_roll_drag,
        kp=2.1, ki=0.9, kd=10.5, N = 100.0,
            LowerSat=0.15, UpperSat=0.90,   
     )
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

plot(
    recorded_t,
    [data.reference_roll data.roll data_sim_old_model],
    xlabel="Time (s)", ylabel="Roll Angle (rad)", title="Roll Angle Comparison",
    legend=:bottomright,
    label=["Roll reference" "Roll measured" "Roll old model"]
)
