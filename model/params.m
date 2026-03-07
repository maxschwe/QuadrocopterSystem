% Masse und Inertialmomente
J_xx = 0.0258;
J_yy = 0.0268;
J_zz = 0.0680;

J = diag([J_xx, J_yy, J_zz]);

m = 1.014;
g = 9.81;

% Antriebsparameter
a = 13.06;
b = 0.0859;
c = 0.0351;

% Abstand Rotoren zu COG
l = 0.20;

% Abstand COG zu Fixed Point
h = 0.05;

% Control Effektivitätsmodell
B_eff = [
    1 1 1 1;
    l 0 -l 0;
    0 l 0 -l;
    c -c c -c;
];

p_x = 0.0;
p_y = 0.0;
p_z = 0.0;

p = [p_x, p_y, p_z];

% Systemmatrizen des linearisierten Modells
A = [
    0 0 0 1 0 0;
    0 0 0 0 1 0;
    0 0 0 0 0 1;
    (m * g * h) / J_xx 0 0 -p_x 0 0;
    0 (m * g * h) / J_yy 0 0 -p_y 0;
    0 0 0 0 0 -p_z;
];

B = [
    0 0 0;
    0 0 0;
    0 0 0;
    1/J_xx 0 0;
    0 1/J_yy 0;
    0 0 1/J_zz;
];

C = [
    1 0 0 0 0 0;
    0 1 0 0 0 0;
    0 0 1 0 0 0;
];

D = [
    0 0 0;
    0 0 0;
    0 0 0;
];

T_delay_actor = 0; %20e-3 * 0.25;

kp_roll = 1.4;
ki_roll = 1.18;
kd_roll = 0.33;

kp_pitch = 1.42;
ki_pitch = 1.21;
kd_pitch = 0.35;

kp_yaw = 1.2;
ki_yaw = 0.7;
kd_yaw = 0.5;

N = 100;

kp_x = 0.1;
ki_x = 0.1;
kd_x = 0.6;

kp_y = 0.1;
ki_y = 0.1;
kd_y = 0.6;

kp_z = 3.5;
ki_z = 2.5;
kd_z = 2.0;

N_pos = 100;


Q = diag([0.01, 0.01, 0.01, 0.0001, 0.0001, 0.0001]);
R = diag([0.01, 0.01, 0.01]);

K = lqr(A, B, Q, R);
Ki = [1 1 1];

V = -inv(C*inv((A-B*K))* B);
