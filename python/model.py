import numpy as np

coeffs_force = [3.98646882e-04, 7.66327150e-02, -2.28383170e+00]
coeffs_torque = [7.20894649e-06, 2.80295913e-03, -7.45248620e-02]

throttle_to_force = np.poly1d(coeffs_force)
throttle_to_torque = np.poly1d(coeffs_torque)

def calc_force_inputs(throttles):
    upward_thrust = sum(throttles)
