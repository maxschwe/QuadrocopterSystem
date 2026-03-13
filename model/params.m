% Masse und Inertialmomente
J_xx = 0.0304;
J_yy = 0.0315;
J_zz = 0.0476;

J = diag([J_xx, J_yy, J_zz]);

m = 1.210;
g = 9.81;

% Antriebsparameter
a = 13.06;
b = 0.0859;
c = 0.0351;

% Abstand Rotoren zu COG
l = 0.20;

% Abstand COG zu Fixed Point
h = 0.044;

% Control Effektivitätsmodell
B_eff = [
    1 1 1 1;
    l 0 -l 0;
    0 l 0 -l;
    c -c c -c;
];

% PID Parameters for attitude control
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

% Systemmatrizen des linearisierten Rotationsmodell
% A auf Teststand
A_test_rot = [
    0 0 0 1 0 0;
    0 0 0 0 1 0;
    0 0 0 0 0 1;
    (m * g * h) / J_xx 0 0 0 0 0;
    0 (m * g * h) / J_yy 0 0 0 0;
    0 0 0 0 0 0;
];

% A im freien Flug
A_free_rot = [
    0 0 0 1 0 0;
    0 0 0 0 1 0;
    0 0 0 0 0 1;
    0 0 0 0 0 0;
    0 0 0 0 0 0;
    0 0 0 0 0 0;
];

B_rot = [
    0 0 0;
    0 0 0;
    0 0 0;
    1/J_xx 0 0;
    0 1/J_yy 0;
    0 0 1/J_zz;
];

C_rot = [
    1 0 0 0 0 0;
    0 1 0 0 0 0;
    0 0 1 0 0 0;
];

A_test_rot_erw = [
    A_test_rot zeros(6, 3);
    -C_rot zeros(3, 3);
];

A_free_rot_erw = [
    A_free_rot zeros(6, 3);
    -C_rot zeros(3, 3);
];

B_rot_erw = [
    B_rot;
    zeros(3, 3);
];

C_rot_erw = [
    C_rot, zeros(3, 3)
];

% LQR Parameters for Attitude Control
Q = diag([130, 130, 130, 10, 10, 10, 130, 130, 130]);
R = diag([100, 100, 100]);

% params on teststand
K_test_rot_erw = lqrd(A_test_rot_erw, B_rot_erw, Q, R, 0.005);
K_test_rot = K_test_rot_erw(1:3, 1:6);
Ki_test_rot = K_test_rot_erw(1:3, 7:9);

S_test_rot = -inv(C_rot*inv((A_test_rot-B_rot*K_test_rot))* B_rot);

% params in free flight
K_free_rot_erw = lqrd(A_free_rot_erw, B_rot_erw, Q, R, 0.005);
K_free_rot = K_free_rot_erw(1:3, 1:6);
Ki_free_rot = K_free_rot_erw(1:3, 7:9);

S_free_rot = -inv(C_rot*inv((A_free_rot-B_rot*K_free_rot))* B_rot);

% PID Parameters for Position Control
kp_x = 0.2;
ki_x = 0.2;
kd_x = 0.5;

kp_y = 0.2;
ki_y = 0.2;
kd_y = 0.5;

kp_z = 3.5;
ki_z = 2.5;
kd_z = 2.0;

N_pos = 100;

% translation
A_trans = [
    0 0 0 1 0 0;
    0 0 0 0 1 0;
    0 0 0 0 0 1;
    0 0 0 0 0 0;
    0 0 0 0 0 0;
    0 0 0 0 0 0;
];

% inputs: thrust, 
B_trans = [
    0 0 0;
    0 0 0;
    0 0 0;
    0 0 g;
    0 -g 0;
    1/m 0 0;
];

C_trans = [
    1 0 0 0 0 0;
    0 1 0 0 0 0;
    0 0 1 0 0 0;
];

A_trans_erw = [
    A_trans zeros(6, 3);
    -C_trans zeros(3, 3);
];

B_trans_erw = [
    B_trans;
    zeros(3, 3);
];

C_trans_erw = [
    C_trans, zeros(3, 3)
];

T_delay_actor = 20e-3;

Q_erw = diag([1 1 100 10 10 10 10 10 100]);
R_trans = diag([50 130 130]);

[K_erw, ~, P_erw] = lqrd(A_trans_erw, B_trans_erw, Q_erw, R_trans, 0.02);
K_trans = K_erw(1:3, 1:6);
Ki_trans = K_erw(1:3, 7:9);
