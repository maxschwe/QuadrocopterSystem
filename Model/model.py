import numpy as np
import matplotlib.pyplot as plt
from numpy.polynomial.polynomial import Polynomial

M_MOTOR = 0.068
L = 0.2 # m


throttles = np.arange(0, 105, 5)
throttles_to_weight = np.array([0, 0, 0, np.nan, np.nan, np.nan, np.nan, 0.025, 0.105, 0.200, 0.310, 0.410, 0.525, 0.640, 0.750, 0.870, 0.960, 1.045, 1.035, 1.030, 1.030])
throttles_to_force = (M_MOTOR + throttles_to_weight) * 9.81

# Filter out NaNs
valid = ~np.isnan(throttles_to_weight)
throttles_valid = throttles[valid]
forces_valid = throttles_to_force[valid]

plt.scatter(throttles, throttles_to_force, color='black', label='Data')

degrees = [2]
fits = []
errors = []

throttles_dense = np.linspace(0, 100, 500)


for deg in degrees:
    p = Polynomial.fit(throttles_valid, forces_valid, deg)

    # Plot
    force_dense = p(throttles_dense)
    plt.plot(throttles_dense, force_dense, label=f'Degree {deg}')

plt.title('Polynomial Fits (0% to 100% ESC Throttle Data)')
plt.xlabel('Throttle (%)')
plt.ylabel('Output Value')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()
