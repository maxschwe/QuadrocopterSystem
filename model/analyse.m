%% Phasenportrait für zwei DGL-Systeme
clear; clc; close all;

% Parameter definieren (Beispielwerte für Instabilität und Dämpfung)
a0 = -2;   % "Federkonstante" / Schwerkraft-Term (positiv = instabil)
a1 = -0.5; % Dämpfungsterm (negativ = Reibung)

% Zeitspanne und Startpunkte für Trajektorien
tspan = [0 5];
y0_list = [-2, -1, 0, 1, 2;   % Startwerte y
           -2, 2, -2, 2, -1];  % Startwerte y_punkt

%% Plot 1: y_double_dot = a0 * y
figure('Name', 'Phasenportrait: Ohne Dämpfung', 'Color', 'w');
subplot(1,2,1); hold on; grid on;
f1 = @(t, x) [x(2); a0 * x(1)]; % Zustandsraum: x1' = x2, x2' = a0*x1
plot_phase_portrait(f1, a0, 0, '$\ddot{y} = a_0 y$ (Instabiler Sattel)');

%% Plot 2: y_double_dot = a1 * y_dot + a0 * y
subplot(1,2,2); hold on; grid on;
f2 = @(t, x) [x(2); a0 * x(1) + a1 * x(2)]; % x1' = x2, x2' = a0*x1 + a1*x2
plot_phase_portrait(f2, a0, a1, '$\ddot{y} = a_1 \dot{y} + a_0 y$ (Gedämpfte Instabilität)');

% Hilfsfunktion zum Zeichnen
function plot_phase_portrait(dgl_fun, a0, a1, titel)
    % Vektorfeld berechnen
    [Y, Ydot] = meshgrid(-3:0.4:3, -3:0.4:3);
    U = Ydot;
    V = a0 * Y + a1 * Ydot;
    
    % Vektoren normieren für bessere Sichtbarkeit
    L = sqrt(U.^2 + V.^2);
    quiver(Y, Ydot, U./L, V./L, 0.5, 'Color', [0.7 0.7 0.7]);
    
    % Beispiel-Trajektorien zeichnen
    colors = lines(10);
    for i = -2:1:2
        for j = -2:2:2
            [t, x] = ode45(dgl_fun, [0 2], [i; j]);
            plot(x(:,1), x(:,2), 'Color', colors(mod(i+j+4,10)+1,:), 'LineWidth', 1.5);
        end
    end
    
    xlabel('$y$', 'Interpreter', 'latex', 'FontSize', 12);
    ylabel('$\dot{y}$', 'Interpreter', 'latex', 'FontSize', 12);
    title(titel, 'Interpreter', 'latex', 'FontSize', 14);
    axis([-3 3 -3 3]);
    plot(0,0, 'ko', 'MarkerFaceColor', 'k'); % Gleichgewichtspunkt
end