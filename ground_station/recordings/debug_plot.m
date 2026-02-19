m = table2array(readtable("log_20260204_172606_Sine.csv"));
tvec = 1:1:size(m,1);
tvec = tvec/200;

figure()

% roll measurements
subplot(2,1,1)
hold on 
plot(tvec, m(:,1))
plot(tvec, m(:,4))
plot(tvec, m(:,12))
legend("pitch real", "pitch ref", "pitch model")
ylabel("angle [deg]")
grid on

% command inputs
subplot(2,1,2)
hold on 
plot(tvec, -m(:,9)+m(:,11))
grid on
ylabel("combined throttle") 
%plot(tvec, m(:,9))
%plot(tvec, m(:,11))
%ylabel("throttle [%]")

xlabel("time [sec]")

% for i = [8,9,10,11]
%     subplot(4,1,i-7)
%     plot(, m(:,i))
% end
