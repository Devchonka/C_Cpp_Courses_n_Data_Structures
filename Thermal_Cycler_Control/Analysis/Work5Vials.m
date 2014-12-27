%When graphical input, make sure 1st cycle is the shortest one as others
%are truncated to its size!

clc;
clear all;
close all;
clearvars;
dbstop if warning

%Load Data
load Recordings5Vials.txt

%Raw Data 5 Vials Figure

% Break Matrix into vectors

time5vials=Recordings5Vials(:,5);
block5vials=Recordings5Vials(:,3);
setpt5vials=Recordings5Vials(:,1);
vial5vials=Recordings5Vials(:,2);

%Raw Data Figure
figure(1)
plot (time5vials,setpt5vials,'k',time5vials,block5vials,'r',time5vials,vial5vials,'m-')
xlabel('Time (sec)')
ylabel('Set Point, Block, Vial (^{o}C)')
title ('1 Vial Cycled in Each of 5 Positions ')
axis([0 max(time5vials) 40 100])
% legend ('Set Point', 'Block', 'Vial')
datacursormode()


% Graphical input for Selecting Overlapping 5 Vials Plots 
a1=ginput(1);
a1i=find(time5vials>a1(1),1);
a2=ginput(1);
a2i=find(time5vials>a2(1),1);
a3=ginput(1);
a3i=find(time5vials>a3(1),1);
a4=ginput(1);
a4i=find(time5vials>a4(1),1);
a5=ginput(1);
a5i=find(time5vials>a5(1),1);
a6=ginput(1);
a6i=find(time5vials>a6(1),1);
a7=ginput(1);
a7i=find(time5vials>a7(1),1);
a8=ginput(1);
a8i=find(time5vials>a8(1),1);
a9=ginput(1);
a9i=find(time5vials>a9(1),1);
a10=ginput(1);
a10i=find(time5vials>a10(1),1);


%Choose Intervals For Overlappig Vials Plot Raw Data
Inttime1=time5vials(a1i:a2i);
Intsetpt1=setpt5vials(a1i:a2i);
Intblock1=block5vials(a1i:a2i);

Intv1=vial5vials(a1i:a2i);
Intv2=vial5vials(a3i:a4i);
Intv2=Intv2 (1: size(Intv1));
Intv3=vial5vials(a5i:a6i);
Intv3=Intv3 (1: size(Intv1));
Intv4=vial5vials(a7i:a8i);
Intv4=Intv4 (1: size(Intv1));
Intv5=vial5vials(a9i:a10i);
Intv5=Intv5 (1: size(Intv1));

% Plot 5 Vials Overlapping
figure(2)
plot (Inttime1,Intsetpt1,'k-')
hold on
plot (Inttime1,Intblock1,'r-')
plot (Inttime1,Intv1,'m-')
plot (Inttime1,Intv2,'c-')
plot (Inttime1,Intv3,'y-')
plot (Inttime1,Intv4,'g-')
plot (Inttime1,Intv5,'b-')
grid on

xlabel('Time (sec)')
ylabel('Set Point, Block, Vial (^{o}C)')
title ('1 Vial Cycled in Each of 5 Positions ')
axis([time5vials(a1i) time5vials(a10i) min(block5vials)-0.5 max(block5vials)+0.5])
legend ('Set Point', 'Block', 'VialP1','VialsP2', 'VialsP3', 'VialP4','VialsP5')
hold off

%For Average Vial Ramp Rates









