M = 5.4;
Ix = 0.002;
Iy = 0.002;
Iz = 0.0018;

distance = 0.2;

force_coeffs = [ 6.34767350e-04  4.40387423e-02 -1.31423643e+00];
r = roots(force_coeffs);
r_real = r(imag(r) == 0);    % nur reale
throttle_minimum = max(r_real);

% minimum force which fits polynomial fit
force_minimum = polyval(force_coeffs, throttle_minimum);

torque_coeffs = [ 0.00460737 -0.1452505 ];
torque_minimum = - torque_coeffs(2) / torque_coeffs(1);

A = [
    0 0 0 0 0 0 0 0 0 0 -9.81 0; 
    0 0 0 0 0 0 0 0 0 9.81 0 0; 
    0 0 0 0 0 0 0 0 0 0 0 0; 
    1 0 0 0 0 0 0 0 0 0 0 0; 
    0 1 0 0 0 0 0 0 0 0 0 0; 
    0 0 1 0 0 0 0 0 0 0 0 0; 
    0 0 0 0 0 0 0 0 0 0 0 0; 
    0 0 0 0 0 0 0 0 0 0 0 0; 
    0 0 0 0 0 0 0 0 0 0 0 0; 
    0 0 0 0 0 0 1 0 0 0 0 0; 
    0 0 0 0 0 0 0 1 0 0 0 0; 
    0 0 0 0 0 0 0 0 1 0 0 0
];

B = [
    0 0 0 0;
    0 0 0 0;
    1/M 0 0 0;
    0 0 0 0;
    0 0 0 0;
    0 0 0 0;
    0 1/Ix 0 0;
    0 0 1/Iy 0;
    0 0 0 1/Iz;
    0 0 0 0;
    0 0 0 0;
    0 0 0 0;
];

C = [
    0 0 0 1 0 0 0 0 0 0 0 0;
    0 0 0 0 1 0 0 0 0 0 0 0;
    0 0 0 0 0 1 0 0 0 0 0 0;
    0 0 0 0 0 0 0 0 0 1 0 0;
    0 0 0 0 0 0 0 0 0 0 1 0;
    0 0 0 0 0 0 0 0 0 0 0 1;
];

D = [
    0 0 0 0;
    0 0 0 0;
    0 0 0 0;
    0 0 0 0;
    0 0 0 0;
    0 0 0 0;
];
