import numpy as np
from scipy.integrate import odeint
from scipy.optimize import minimize

a = 0.0013
b = 8.5908

I = np.array([
    [0.0258, 0.0, 0.0], 
    [0.0, 0.0268, 0.0], 
    [0.0, 0.0, 0.068]
])

E = np.array([[1.0, 0.0, 0.2, 0.0351], [1.0, -0.2, 0.0, -0.0351], [1.0, 0.0, -0.2, 0.0351], [1.0,
    0.2, 0.0, -0.0351]])

# 1. Der Regler aus deinem Bild (Diskretisiert für die Simulation)
class PID_Filtered:
    def __init__(self, P, I, D, N, dt):
        self.P, self.I, self.D, self.N = P, I, D, N
        self.dt = dt
        self.integral = 0
        self.last_filter_out = 0
        self.last_error = 0

    def compute(self, error):
        # I-Anteil (Rechteck-Regel)
        self.integral += error * self.dt
        
        # D-Anteil mit Filter (N)
        # Diskretisierung des Filters: (D*N*s)/(s+N)
        # Entspricht einer Tiefpass-gefilterten Ableitung
        filter_out = (self.D * self.N * (error - self.last_error) + 
                      self.last_filter_out) / (1 + self.N * self.dt)
        
        u = (self.P * error) + (self.I * self.integral) + filter_out
        
        # Updates für den nächsten Schritt
        self.last_error = error
        self.last_filter_out = filter_out
        return u

# 2. Nichtlineares Anlagenmodell (z.B. Drohne oder Roboterarm)
def plant_dynamics(x, t, u, p):
    u = E * a * (u - b) ** 2

    phi = x[0]
    theta = x[1]

    body_to_euler_rates = [
        [1, np.sin(phi) * np.tan(theta), np.cos(phi)*np.tan(theta)],
        [0, np.cos(phi), -np.sin(phi)],
        [0, np.sin(phi) / np.cos(theta), np.cos(phi)/np.cos(theta)]
    ]

    dx = np.zeros(6)
    dx[0:3] = np.dot(body_to_euler_rates, x[3:6])
    dx[3:6] = np.linalg.solve(I, (u - np.cross(x[3:6], np.dot(I, x[3:6]))))
    return dx


# 3. Simulations-Funktion für den geschlossenen Regelkreis
def simulate(p, t_data, r_data, controller_params):
    y_sim = np.zeros_like(t_data)
    x0 = 0
    dt = t_data[1] - t_data[0]
    
    # Regler initialisieren mit Werten aus deinem Bild
    regler = PID_Filtered(*controller_params, dt)
    
    for i in range(1, len(t_data)):
        error = r_data[i] - current_y
        u = regler.compute(error)
        
        # Physik-Update
        sol = odeint(plant_dynamics, x0, [0, dt], args=(u, p))

        y = sol[-1][:3]
        x0 = sol[-1]
        y_sim[i] = x0[0]
    return y_sim

# 4. Zielfunktion für Nelder-Mead
def objective(p_guess):
    # p_guess sind hier z.B. [masse, reibung]
    # controller_params sind bekannt: [P, I, D, N]
    known_controller = [4.70813243049012, 0.35599180792732, 0.5, 100.0] 
    y_sim = simulate(p_guess, t_data, r_data, known_controller)
    return np.mean((y_measured - y_sim)**2)

# Optimierung starten
res = minimize(objective, x0=[1.0, 0.1], method='Nelder-Mead')
print(f"Gefundene Anlagenparameter: {res.x}")
