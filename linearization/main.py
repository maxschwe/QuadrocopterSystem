import sympy as sp

phi, theta, psi = sp.symbols('phi theta psi')
wx, wy, wz = sp.symbols('omega_x omega_y omega_z')
dx, dy, dz = sp.symbols('d_x d_y d_z')

X = sp.Matrix([phi, theta, psi, wx, wy, wz])

T = sp.Matrix([
    [1, sp.sin(phi)*sp.tan(theta), sp.cos(phi)*sp.tan(theta)],
    [0, sp.cos(phi),              -sp.sin(phi)],
    [0, sp.sin(phi)/sp.cos(theta), sp.cos(phi)/sp.cos(theta)]
])
omega = sp.Matrix([wx, wy, wz])
phi_dot = T * omega

Ixx, Iyy, Izz = sp.symbols('J_xx J_yy J_zz')
Mx, My, Mz = sp.symbols('tau_x tau_y tau_z')

g, m, h = sp.symbols('g m h')

J = sp.diag(Ixx, Iyy, Izz)

tau_g = sp.Matrix([m * g * h * sp.sin(phi) * sp.cos(theta), m * g * h * sp.sin(theta), 0])
tau_g = sp.Matrix([0, 0, 0])

omega_dot = J.inv() * (sp.Matrix([Mx, My, Mz]) - omega.cross(J * omega)) #  + tau_g - sp.diag([dx, dy, dz], unpack=True) * omega

f = sp.Matrix.vstack(phi_dot, omega_dot)

A = f.jacobian(X)
A_simplified = sp.simplify(A)
latex_code = sp.latex(A_simplified)

B = f.jacobian(sp.Matrix([Mx, My, Mz]))
B_simplified = sp.simplify(B)
b_latex = sp.latex(B_simplified)

print("State-space A matrix:")
print(latex_code)
sp.pprint(A_simplified)
print("State-space B matrix:")
print(b_latex)
sp.pprint(B)

# Symbols
x, y, z = sp.symbols('x y z')
vx, vy, vz = sp.symbols('v_x v_y v_z')
phi, theta, psi = sp.symbols('phi theta psi')
m, g, F_thrust = sp.symbols('m g F_thrust')
dx, dy, dz = sp.symbols('d_x d_y d_z') # Drag coefficients

X_trans = sp.Matrix([x, y, z, vx, vy, vz])

Rx = sp.Matrix([[1, 0, 0], [0, sp.cos(phi), -sp.sin(phi)], [0, sp.sin(phi), sp.cos(phi)]])
Ry = sp.Matrix([[sp.cos(theta), 0, sp.sin(theta)], [0, 1, 0], [-sp.sin(theta), 0, sp.cos(theta)]])
Rz = sp.Matrix([[sp.cos(psi), -sp.sin(psi), 0], [sp.sin(psi), sp.cos(psi), 0], [0, 0, 1]])

R_bw = Rz * Ry * Rx

pos_dot = sp.Matrix([vx, vy, vz])

gravity = sp.Matrix([0, 0, -m * g])
thrust_body = sp.Matrix([0, 0, F_thrust])
thrust_world = R_bw * thrust_body

vel_dot = (gravity + thrust_world) / m

f_trans = sp.Matrix.vstack(pos_dot, vel_dot)

A_trans = f_trans.jacobian(X_trans)

B_trans = f_trans.jacobian(sp.Matrix([F_thrust, phi, theta, psi]))

print("Translational State-space A matrix:")

sp.pprint(sp.simplify(A_trans))
a_latex = sp.latex(sp.simplify(A_trans))
print(a_latex)

print("\nTranslational State-space B matrix (Thrust input):")
sp.pprint(sp.simplify(B_trans))
b_latex = sp.latex(sp.simplify(B_trans))
print(b_latex)
