clc;
close all;

dbstop if warning

 
% load RecordingsVLim.txt


VPos=[2 4 6 8 10 12 14 16 18 19 20 21];
VNeg=[0 -2 -4 -6 -8 -10 -12 -14 -16 -18 -19 -20 -21];

% Define Block Ramp Rates
RR2=RecordingsVLim(:,1);
RR4=RecordingsVLim(:,2);
RR6=RecordingsVLim(:,3);
RR8=RecordingsVLim(:,4);
RR10=RecordingsVLim(:,5);
RR12=RecordingsVLim(:,6);
RR14=RecordingsVLim(:,7);
RR16=RecordingsVLim(:,8);
RR18=RecordingsVLim(:,9);
RR19=RecordingsVLim(:,10);
RR20=RecordingsVLim(:,11);
RR21=RecordingsVLim(:,12);

MaxpRR=[max(RR2) max(RR4) max(RR6) max(RR8) max(RR10) max(RR12),...
    max(RR14) max(RR16) max(RR18) max(RR19) max(RR20) max(RR21)];

RRn0=RecordingsVLim(:,13);
RRn2=RecordingsVLim(:,14);
RRn4=RecordingsVLim(:,15);
RRn6=RecordingsVLim(:,16);
RRn8=RecordingsVLim(:,17);
RRn10=RecordingsVLim(:,18);
RRn12=RecordingsVLim(:,19);
RRn14=RecordingsVLim(:,20);
RRn16=RecordingsVLim(:,21);
RRn18=RecordingsVLim(:,22);
RRn19=RecordingsVLim(:,23);
RRn20=RecordingsVLim(:,24);
RRn21=RecordingsVLim(:,25);

MaxnRR=[min(RRn0) min(RRn2) min(RRn4) min(RRn6) min(RRn8) min(RRn10),...
    min(RRn12) min(RRn14) min(RRn16) min(RRn18) min(RRn19),...
    min(RRn20) min(RRn21)];

figure(1)
plot (VPos,MaxpRR,'r',VNeg,MaxnRR,'r')
xlabel('Voltage(V)')
ylabel('Max Ramp Rates (^{o}C/sec)')
title ('Max Ramp Rates vs Voltages')
axis([-22 22 -9 9])
datacursormode()
