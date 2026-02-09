using DifferentialEquations, LinearAlgebra, Plots

# --- 1. Parameters & Configuration ---
const P = (
    J = Diagonal([0.0258, 0.0268, 0.0680]),
    a = 13.0, b = 0.085908, c = 0.0351, 
    l = 0.20,
    E = [1.0  1.0  1.0  1.0;
           0.0 -0.2  0.0  0.2;
           0.2  0.0 -0.2  0.0;
           0.0351 -0.0351 0.0351 -0.0351],
    m = 1.014,
    g = 9.81,
    d = 0.05
)

# --- 2. Controller & Allocation ---
function control_alloc(tau)
    # Solve mixing: Torques -> Squared Thrusts -> RPM
    f_sq = P.E \ tau
    rpm = sqrt.(max.(f_sq, 0.0) ./ P.a) .+ P.b
    return clamp.(rpm, 0.15, 0.80)
end

# --- 3. Dynamics ---
u0 = zeros(6)
function quadrotor_dynamics!(du, u, p, t)
    phi, theta = u[1], u[2]
    omega = u[4:6]

    throttles = p.(t)
    thrusts = @. P.a * (throttles - P.b)^2

     # Kinematics: Body rates to Euler rates
    # s=sin, c=cos, t=tan
    sφ, cφ = sin(phi), cos(phi)
    sθ, tθ, cθ = sin(theta), tan(theta), cos(theta)
    W = [1  sφ*tθ  cφ*tθ;
           0  cφ     -sφ;
           0  sφ/cθ  cφ/cθ]
    
    # Forces/Torques (skip the first element as it's total lift, we use 2:4)
    torques = (P.E * thrusts)[2:4]
    torques[1] += P.m * P.g * P.d * sφ * cθ
    torques[2] += P.m * P.g * P.d * sθ

    torques[2] = 0.0
    torques[3] = 0.0

    # Derivatives
    du[1:3] = W * omega
    du[4:6] = P.J \ (torques - cross(omega, P.J * omega))
end

# --- 4. Simulation Execution ---
tspan = (0.0, 1000.0)

generalized_forces(t) = [
    2.0,
    0.1 * sin(t), 
    0.0, 
    0.0
]

throttles(t) = control_alloc(generalized_forces(t))

trange = tspan[1]:0.01:tspan[2]
plot(trange, stack(throttles.(trange))', title="Throttles over Time", xlabel="Time (s)", ylabel="Throttles", labels=["Motor 1" "Motor 2" "Motor 3" "Motor 4"], lw=2)

prob = ODEProblem(quadrotor_dynamics!, u0, tspan, throttles)
sol = solve(prob, Tsit5(), reltol=1e-8, abstol=1e-8)

# --- 5. Visualization ---
# Main state plot
y = stack(map(u -> ([u[1], u[4]]), sol.u))'

motor2 = stack(throttles.(sol.t))'[:, 2]
motor4 = stack(throttles.(sol.t))'[:, 4]

# Convert to a Matrix for easy plottin
plot(sol.t, hcat(y[:, 1], y[:, 2], motor2, motor4),
     layout=(4,1),
     labels=["Roll" "wx" "Throttle"])

# # Animation

# Helpers for rotation logicdas
# function rotation_matrix(phi, theta, psi)
#     Rx = [1 0 0; 0 cos(phi) -sin(phi); 0 sin(phi) cos(phi)]
#     Ry = [cos(theta) 0 sin(theta); 0 1 0; -sin(theta) 0 cos(theta)]
#     Rz = [cos(psi) -sin(psi) 0; sin(psi) cos(psi) 0; 0 0 1]
#     return Rz * Ry * Rx
# end

# println("Generating animation...")
# anim = @animate for t in range(tspan[1], tspan[2], length=200)
#     phi, theta, psi = sol(t)[1:3]
#     R = rotation_matrix(phi, theta, psi)
    
#     # Rotate arms
#     p1, p3 = R * [P.l, 0, 0], R * [-P.l, 0, 0]
#     p2, p4 = R * [0, P.l, 0], R * [0, -P.l, 0]
    
#     p = plot(xlim=(-0.3, 0.3), ylim=(-0.3, 0.3), zlim=(-0.3, 0.3),
#              title="Drone t=$(round(t, digits=1))", camera=(45, 30), aspect_ratio=:equal)
             
#     # Draw Arms
#     plot!(p, [p1[1], p3[1]], [p1[2], p3[2]], [p1[3], p3[3]], lw=3, color=:red)
#     plot!(p, [p2[1], p4[1]], [p2[2], p4[2]], [p2[3], p4[3]], lw=3, color=:blue)
#     scatter!(p, [p1[1], p2[1], p3[1], p4[1]], [p1[2], p2[2], p3[2], p4[2]], 
#              [p1[3], p2[3], p3[3], p4[3]], markersize=4, color=:black)
# end

# gif(anim, "drone_sim.gif", fps=20)
