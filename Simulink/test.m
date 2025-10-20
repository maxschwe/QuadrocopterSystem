function inputs = convert_inputs(throttles)
    inputs = zeros(4, 1);

    COEFFS_FORCE = [3.98646882e-04, 7.66327150e-02, -2.28383170e+00];
    COEFFS_TORQUE = [7.20894649e-06, 2.80295913e-03, -7.45248620e-02];
    DISTANCE_ROTOR_CENTER = 0.3;

    forces = polyval(COEFFS_FORCE, throttles);
    torque = polyval(COEFFS_TORQUE, throttles);

    inputs(1) = sum(forces); % thrust
    inputs(2) = DISTANCE_ROTOR_CENTER * (forces(1) - forces(2) - forces(3) + forces(4)); % roll_torque
    inputs(3) = DISTANCE_ROTOR_CENTER * (forces(1) - forces(3) + forces(2) - forces(4)); % pitch_torque
    
    
    inputs(4) = torque(1) - torque(2) + torque(3) - torque(4)% yaw torque
end

convert_inputs([0.2, 0.3, 0.2, 0.3])
