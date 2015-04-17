clearvars
close all

%Define Desired Block Slopes
m1=7;
m2=-7;

% Define Amplitude Parameters 
%NOTE: A2 & A5 are pre-determined by continuity
A1=55;
%A2= pre-determined;
A3=99;
A4=96;
%A5= pre-determined;
A6=52;

% Define Time Parameters 
%NOTE: T1 & T6 are pre-determined by continuity
% T1= pre-determined 
T2=8;
T3=14;
T4=8;
T5=9;
% T6= pre-determined  
T7=7;
T8=4;
T9=10;
T10=19;


%Sinusoid Parameters
w1 = (2 * pi)/(4*(T2));
w2 = (2 * pi)/(2*(T4));
w3 = (2 * pi)/(4*(T7));
w4 = (2 * pi)/(2*(T9));

A2=A3-(m1/w1);
A5=A6-(m2/w3);

A =(A3-A2);
B=0.5*(A3-A4);
C=(A5-A6);
D=0.5*(A1-A6);

% Linear Parameters 
T1=(A2-A1)/m1;
T6=(A5-A4)/m2;

Tfinal=T1+T2+T3+T4+T5+T6+T7+T8+T9+T10;
t = 0:0.001:Tfinal;

% Display values in Command Window for Block
fprintf ('\nFor max slope up %0.2f & max slope dwn %0.2f,\n',m1,m2);
fprintf('And Ave up %0.2f and Down %0.2f,\n',(A3-A1)/(T1+T2),(A6-A4)/(T6+T7))

fprintf('\n T1=%0.2f',T1)
fprintf ('\n T6=%0.2f \n',T6)

fprintf('\n A2=%0.2f',A2)
fprintf ('\n A5=%0.2f \n',A5)




% Piecewise Waveform
y = ...
  (m1*(t)+A1          ) .* (t<T1) + ...
  (A2+A*sin(w1*(t-T1))) .* (T1<= t & t < T1+T2) + ...
  (A3                    ) .* (T1+T2 <= t & t < T1+T2+T3)+ ...
  (A3-B+B*cos((w2*(t-(T1+T2+T3))))) .* (T1+T2+T3 <= t & t < T1+T2+T3+T4)+...
  (A4                    ) .* (T1+T2+T3+T4 <= t & t < T1+T2+T3+T4+T5) + ...
  (m2*(t-(T1+T2+T3+T4+T5))+A4) .* (T1+T2+T3+T4+T5 <= t & t < T1+T2+T3+T4+T5+T6) + ...
  (A5-C*sin(w3*(t-(T1+T2+T3+T4+T5+T6)))   ) .* (T1+T2+T3+T4+T5+T6 <= t & t < T1+T2+T3+T4+T5+T6+T7)+ ...
  (A6                    ) .* (T1+T2+T3+T4+T5+T6+T7 <= t & t < T1+T2+T3+T4+T5+T6+T7+T8) + ...
  (A6+D-D*cos(w4*(t-(T1+T2+T3+T4+T5+T6+T7+T8)))   ) .* (T1+T2+T3+T4+T5+T6+T7+T8 <= t & t < T1+T2+T3+T4+T5+T6+T7+T8+T9)+ ...
  (A1                    ) .* (T1+T2+T3+T4+T5+T6+T7+T8+T9 <= t & t < T1+T2+T3+T4+T5+T6+T7+T8+T9+T10);

% Outputted Plot
f= plot (t,y,'m');
hold on
set (f, 'LineWidth', 2);
axis([0 Tfinal+3 A6-2 A3+2]);
xlabel('Time (sec)')
ylabel('Set Point Signal (^{o}C)')
title('Set Point')
hold off