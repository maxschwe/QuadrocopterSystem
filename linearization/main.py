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

omega_dot = J.inv() * (sp.Matrix([Mx, My, Mz]) + tau_g - sp.diag([dx, dy, dz], unpack=True) * omega - omega.cross(J * omega))

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
