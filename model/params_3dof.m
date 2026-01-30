% Masse und Inertialmomente
I_xx = 0.0258;
I_yy = 0.0268;
I_zz = 0.0680;

I = diag([I_xx, I_yy, I_zz]);

m = 1.014;
g = 9.81;

% Antriebsparameter
a = 0.0013;
b = 8.5908;
c = 0.0351;

T_thrusters = 0.2;

% Abstand Rotoren zu COG
l = 0.20;

% Abstand COG zu Fixed Point
d = 0.05;

% Control Effektivitätsmodell
E = [
    1 1 1 1;
    0 -l 0 l;
    l 0 -l 0;
    c -c c -c;
];

% Systemmatrizen des linearisierten Modells
A = [
    0 0 0 1 0 0;
    0 0 0 0 1 0;
    0 0 0 0 0 1;
    (m * g * d) / I_xx 0 0 0 0 0;
    0 (m * g * d) / I_yy 0 0 0 0;
    0 0 0 0 0 0;
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
