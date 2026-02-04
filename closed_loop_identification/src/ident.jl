using DifferentialEquations
using Plots

J_xx = 0.0258
J_yy = 0.0268
J_zz = 0.0680

J = diag([J_xx, J_yy, J_zz])

m = 1.014
g = 9.81

a = 0.0013
b = 8.5908
c = 0.0351

l = 0.20
d = 0.05


E = [
    1 1 1 1;
    0 -l 0 l;
    l 0 -l 0;
    c -c c -c;
]

# 1. Define the system of equations
function quadrotor_dynamics(dx, x, p, t)
    throttles = p.(t)
    thrusts = a * (throttles - b).^2

    generalized_forces = E * thrusts
    torques = generalized_forces[2:4]

    phi = x(1)
    theta = x(2)
    omega = x(4:6)

    body_to_euler_rates = [
        1, sin(phi) * tan(theta), cos(phi)*tan(theta);
        0, cos(phi), -sin(phi);
        0, sin(phi) / cos(theta), cos(phi)/cos(theta);
    ]

    angles_dot = body_to_euler_rates * omega
    omega_dot = J \ (torques - damping_moments - cross(omega, J * omega))

    dx = [angles_dot; omega_dot]
end

# 2. Set Initial Conditions and Parameters
u0 = [0.0; 0.0; 0.0]        # Initial state [x, y, z]
p = (10.0, 28.0, 8/3)       # Parameters (σ, ρ, β)
tspan = (0.0, 100.0)        # Time interval

# 3. Define and Solve the Problem
prob = ODEProblem(lorenz!, u0, tspan, p)
sol = solve(prob, Tsit5(), reltol=1e-8, abstol=1e-8)

# 4. Plot the results
plot(sol, vars=(1, 2, 3), title="Lorenz Attractor", lw=0.5)

ODEProblem()
