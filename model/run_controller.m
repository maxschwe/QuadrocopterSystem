clear; clc;
%% ===== USER SETTINGS =====
port = "COM4";
baud = 115200;
inportSize = 7;

kp = 0.013;
ki = 0.0013;
kd = 0.0027;

%% ===== Serial =====
s = serialport(port, baud, "Timeout", 5);
configureTerminator(s, "LF");
flush(s);

integral_roll = 0.0;
prev_roll_error = 0.0;

%% ===== Main Loop =====
while true
    % readline() blocks until 'LF' is received or timeout occurs
    line = readline(s);
    
    if startsWith(line, "#")
        dataStr = extractAfter(line, 1);
        inputs = sscanf(dataStr, '%f,'); 
        
        if length(inputs) ~= inportSize
            continue;
        end
        
        error_roll = inputs(4) - inputs(1);
        output_roll_moment = kp * error_roll + ki * integral_roll + kd * error_roll - prev_roll_error;

        %% ===== Read & Send =====
        val_out = control_alloc([inputs(7), output_roll_moment, 0, 0]');
      
        outStr = "#" + strjoin(compose("%.2f", val_out'), ',');
        writeline(s, outStr);
    else
        % Log non-data lines (debug info from MCU)
        if ~isempty(line), disp(line); end
    end
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

    throttle = zeros(size(thrust));

    idx = thrust ./ a >= 0;
    throttle(idx) = sqrt(thrust(idx) ./ a) + b;
end
