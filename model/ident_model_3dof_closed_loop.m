%% ================= USER SETTINGS =================
modelName  = 'system_3dof';              % Simulink model
dataFolder = '..\monitor\recordings';        % folder with CSV files
Ts         = 0.01;                   % 10 ms
p0         = 0.05;                    % initial guess for p

%% ================= CHECK =================
assert(isfolder(dataFolder), 'Data folder not found');

files = dir(fullfile(dataFolder,'*.txt'));
assert(~isempty(files), 'No CSV files found');

load_system(modelName);

%% ================= OPTIMIZATION =================
costFun = @(p) totalCost(p, modelName, files, Ts);

options = optimset( ...
    'Display','iter', ...
    'TolX',1e-9, ...
    'TolFun',1e-4, ...
    'MaxIter',100);

[p_opt, J_opt] = fminsearch(costFun, p0, options);

fprintf('\n====================================\n');
fprintf('Optimal p = %.6f\n', p_opt);
fprintf('Final cost = %.6f\n', J_opt);
fprintf('====================================\n');

function J = totalCost(p, modelName, files, Ts)
    J = 0;

    for k = 1:numel(files)
        filePath = fullfile(files(k).folder, files(k).name);
        J = J + singleFileCost(p, modelName, filePath, Ts);
    end
end

function J = singleFileCost(p, modelName, filePath, Ts)
    fprintf('Evaluating for p = %.6f\n', p);
    % ---- READ CSV ----
    opts = detectImportOptions(filePath,'Delimiter','\t');
    T = readtable(filePath, opts);

    y_meas = T{:,1};      % columns 1–3
    y_meas = deg2rad(y_meas);
    w_ref  = T{:,7};      % columns 7–9
    w_ref =  deg2rad(w_ref);

    w_ref = [2.0 * ones(size(w_ref)), w_ref, zeros(size(w_ref)), zeros(size(w_ref))];

    N = size(T,1);
    t = (0:N-1)' * Ts;

    % ---- TIMESERIES FOR SIMULINK ----
    inData = timetable(seconds(t), w_ref);

    % ---- SIMULATION INPUT ----
    simIn = Simulink.SimulationInput(modelName);
    simIn = simIn.setExternalInput(inData);

    simIn = simIn.setVariable('p', p);
    simIn = simIn.setModelParameter('StopTime', num2str(t(end)));

    % ---- RUN SIMULATION ----
    simOut = sim(simIn);

    % ---- GET OUTPUT y ----
    y_sim = simOut.yout.signals(2).values(:, 1);

    % ---- COST FUNCTION (L2) ----
    e = y_sim - y_meas;
    J = sum(e(:).^2);
end
