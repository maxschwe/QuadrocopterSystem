% Masse und Inertialmomente
I_xx = 0.0258;
I_yy = 0.0268;
I_zz = 0.0680;

I = diag([I_xx, I_yy, I_zz]);

m = 1.114;
g = 9.81;

% Antriebsparameter
a = 13.00;
b = 0.085908;
c = 0.0351;

% Abstand Rotoren zu COG
l = 0.20;

% Abstand COG zu Fixed Point
d = 0.03;

% Control Effektivitätsmodell
E = [
    1 1 1 1;
    0 -l 0 l;
    l 0 -l 0;
    c -c c -c;
];

p = 0.08;

% Systemmatrizen des linearisierten Modells
A = [
    0 0 0 1 0 0;
    0 0 0 0 1 0;
    0 0 0 0 0 1;
    (m * g * d) / I_xx 0 0 -p 0 0;
    0 (m * g * d) / I_yy 0 0 -p 0;
    0 0 0 0 0 -p;
];

B = [
    0 0 0;
    0 0 0;
    0 0 0;
    1/I_xx 0 0;
    0 1/I_yy 0;
    0 0 1/I_zz;
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

guenther = 1.0;

T_delay_actor = 0; %20e-3 * 0.25;

kp_roll = 1.4;
ki_roll = 1.18;
kd_roll = 0.33;

kp_pitch = 1.42;
ki_pitch = 1.21;
kd_pitch = 0.35;

kp_yaw = 2.8;
ki_yaw = 2.5;
kd_yaw = 0.51;

ke = 100;


n = size(A, 1);
n_C = size(C, 1);

A_ext = [A,           zeros(n, n_C);
         C,          zeros(n_C, n_C)];

B_ext = [B; 
         zeros(n_C, size(B, 2))];

Q = diag([0.01, 0.01, 0.01, 0.0001, 0.0001, 0.0001]);
R = diag([0.01, 0.01, 0.01]);

K = lqr(A, B, Q, R);
Ki = [1 1 1];

V = -inv(C*inv((A-B*K))* B);
