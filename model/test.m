function tau = mixer(u)
    l = 0.2;
    c = 0.0351;

    E = [
        1 1 1 1;
        0 -l 0 l;
        l 0 -l 0;
        c -c c -c;
    ];

    tau = E * throttle_to_thrust(u);
end

function thrust = throttle_to_thrust(throttle)
    a = 0.0013;
    b = 8.5908;

    thrust = a * (throttle - b).^2;
end

function u = control_alloc(tau)
    E_inv = [
        0.2500         0    2.5000    7.1225
        0.2500   -2.5000         0   -7.1225
        0.2500         0   -2.5000    7.1225
        0.2500    2.5000         0   -7.1225
    ];

    u = thrust_to_throttle(E_inv * tau);
end

function throttle = thrust_to_throttle(thrust)
    a = 0.0013;
    b = 8.5908;

    throttle = ones(size(thrust));

    idx = thrust ./ a >= 0;
    throttle(idx) = sqrt(thrust(idx) ./ a) + b;
end
