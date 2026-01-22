clear; clc;
%% ===== USER SETTINGS =====
port = "COM4";
baud = 115200;
model = "run_external_mode";
step_size = 0.02;
inportSize = 7;

%% ===== Serial =====
s = serialport(port, baud, "Timeout", 5); % Reduced timeout for responsiveness
configureTerminator(s, "LF");
flush(s);

%% ===== Load & Initialize System =====
load_system(model);
sm = simulation(model);
sm.setModelParameter(SolverType="Fixed-step", FixedStep=num2str(step_size), StopTime="inf");
inputs = zeros(7, 1);
sm.initialize();

% Cache Outport Runtime Objects once
outport_paths = sort(find_system(model, 'SearchDepth', 1, 'BlockType', 'Outport'));
num_outports = length(outport_paths);
rto_list = cell(1, num_outports);
for i = 1:num_outports
    rto_list{i} = get_param(outport_paths{i}, 'RuntimeObject');
end

disp("Simulation Running...");

%% ===== Main Loop =====
while true
    % readline() blocks until 'LF' is received or timeout occurs
    line = readline(s);

    disp(s.NumBytesAvailable);
    
    if startsWith(line, "#")
        % Faster Parsing: strsplit + sscanf is often faster than split + str2double
        dataStr = extractAfter(line, 1);
        inputs = sscanf(dataStr, '%f,'); 
        
        if length(inputs) ~= inportSize
            continue;
        end
        
        % Inject and Step
        sm.setVariable("inputs", inputs);
        sm.step();

        %% ===== Read & Send =====
        val_out = zeros(1, num_outports);
        for i = 1:num_outports
            val_out(i) = rto_list{i}.InputPort(1).Data;
        end
      
        outStr = "#" + strjoin(string(num2str(val_out', '%.2f')), ',');
        writeline(s, outStr);
    else
        % Log non-data lines (debug info from MCU)
        if ~isempty(line), disp(line); end
    end
end