clc;
clear all;
close all;
clearvars;
dbstop if warning

%FOR THE 57*C SETPOINT
load Recordings57.txt
load Recordings57e.txt



% Raw Data 57 Figure

%Breaking matrix 57 into vectors
time57=Recordings57(:,7);
setpt57=Recordings57(:,1);
block57=Recordings57(:,3);
vial57=Recordings57(:,2);

figure(1)
plot (time57,setpt57,'k',time57,block57,'r',time57,vial57,'m-')
xlabel('Time (sec)')
ylabel('Set Point, Block, Vial (^{o}C)')
title ('Fully Loaded Vials at 57 ')
axis([0 max(time57) 56 max(block57)+0.5])
legend ('Set Point', 'Block', 'Vial')


% Graphical input for 57
a1=ginput(1);
a1i=find(time57>a1(1),1);
a2=ginput(1);
a2i=find(time57>a2(1),1);
a3=ginput(1);
a3i=find(time57>a3(1),1);
a4=ginput(1);
a4i=find(time57>a4(1),1);
a5=ginput(1);
a5i=find(time57>a5(1),1);
a6=ginput(1);
a6i=find(time57>a6(1),1);
a7=ginput(1);
a7i=find(time57>a7(1),1);
a8=ginput(1);
a8i=find(time57>a8(1),1);
a9=ginput(1);
a9i=find(time57>a9(1),1);
a10=ginput(1);
a10i=find(time57>a10(1),1);
a11=ginput(1);
a11i=find(time57>a11(1),1);
a12=ginput(1);
a12i=find(time57>a12(1),1);
a13=ginput(1);
a13i=find(time57>a13(1),1);
a14=ginput(1);
a14i=find(time57>a14(1),1);
a15=ginput(1);
a15i=find(time57>a15(1),1);
a16=ginput(1);
a16i=find(time57>a16(1),1);
a17=ginput(1);
a17i=find(time57>a17(1),1);
a18=ginput(1);
a18i=find(time57>a18(1),1);
a19=ginput(1);
a19i=find(time57>a19(1),1);
a20=ginput(1);
a20i=find(time57>a20(1),1);


% Raw Data 57e Figure

%Breaking matrix 57e into vectors
time57e=Recordings57e(:,7);
setpt57e=Recordings57e(:,1);
block57e=Recordings57e(:,3);
vial57e=Recordings57e(:,2);

figure(2)
plot (time57e,setpt57e,'k',time57e,block57e,'r',time57e,vial57e,'m-')
xlabel('Time (sec)')
ylabel('Set Point, Block, Vial (^{o}C)')
title ('1 Vial Loaded at 57')
axis([0 max(time57e) 56 max(block57e)+0.5])
legend ('Set Point', 'Block', 'Vial')
datacursormode()


% Graphical input for 57e
b1=ginput(1);
b1i=find(time57e>b1(1),1);
b2=ginput(1);
b2i=find(time57e>b2(1),1);
b3=ginput(1);
b3i=find(time57e>b3(1),1);
b4=ginput(1);
b4i=find(time57e>b4(1),1);
b5=ginput(1);
b5i=find(time57e>b5(1),1);
b6=ginput(1);
b6i=find(time57e>b6(1),1);
b7=ginput(1);
b7i=find(time57e>b7(1),1);
b8=ginput(1);
b8i=find(time57e>b8(1),1);
b9=ginput(1);
b9i=find(time57e>b9(1),1);
b10=ginput(1);
b10i=find(time57e>b10(1),1);
b11=ginput(1);
b11i=find(time57e>b11(1),1);
b12=ginput(1);
b12i=find(time57e>b12(1),1);
b13=ginput(1);
b13i=find(time57e>b13(1),1);
b14=ginput(1);
b14i=find(time57e>b14(1),1);
b15=ginput(1);
b15i=find(time57e>b15(1),1);
b16=ginput(1);
b16i=find(time57e>b16(1),1);
b17=ginput(1);
b17i=find(time57e>b17(1),1);
b18=ginput(1);
b18i=find(time57e>b18(1),1);
b19=ginput(1);
b19i=find(time57e>b19(1),1);
b20=ginput(1);
b20i=find(time57e>b20(1),1);



% For Bar Plot 57 and 57e
P1a57=vial57(a1i:a2i);
P2a57=vial57(a3i:a4i);
P3a57=vial57(a5i:a6i);
P4a57=vial57(a7i:a8i);
P5a57=vial57(a9i:a10i);

P1b57=vial57(a11i:a12i);
P2b57=vial57(a13i:a14i);
P3b57=vial57(a15i:a16i);
P4b57=vial57(a17i:a18i);
P5b57=vial57(a19i:a20i);

P1a57e=vial57e(b1i:b2i);
P2a57e=vial57e(b3i:b4i);
P3a57e=vial57e(b5i:b6i);
P4a57e=vial57e(b7i:b8i);
P5a57e=vial57e(b9i:b10i);

P1b57e=vial57e(b11i:b12i);
P2b57e=vial57e(b13i:b14i);
P3b57e=vial57e(b15i:b16i);
P4b57e=vial57e(b17i:b18i);
P5b57e=vial57e(b19i:b20i);

%Vector containing all 57*C bar graph values
AveP57= [mean(P1a57) mean(P1b57) mean(P1a57e) mean(P1b57e);
         mean(P2a57) mean(P2b57) mean(P2a57e) mean(P2b57e);
         mean(P3a57) mean(P3b57) mean(P3a57e) mean(P3b57e);
         mean(P4a57) mean(P4b57) mean(P4a57e) mean(P4b57e);
         mean(P5a57) mean(P5b57) mean(P5a57e) mean(P5b57e)];
          
StdP57=  [std(P1a57) std(P1b57) std(P1a57e) std(P1b57e);
         std(P2a57) std(P2b57) std(P2a57e) std(P2b57e);
         std(P3a57) std(P3b57) std(P3a57e) std(P3b57e);
         std(P4a57) std(P4b57) std(P4a57e) std(P4b57e);
         std(P5a57) std(P5b57) std(P5a57e) std(P5b57e)];    

     
figure (3)
bar(AveP57);
axis ([0 6 56.5 57.5])
set(gca,'XTickLabel',{'P1','P2','P3','P4','P5'})
ylabel('Average Temperature (^{o}C)')
title ('Mean Temperature at Holds')
legend ('Filled P57 Trial 1', 'Filled P57 Trial 2',...
        '1 Vial P57 Trial 1', '1 Vial P57 Trial 2',0)
    grid on
datacursormode()


% Raw Data 95 Figure

%Breaking matrix 95 into vectors
load Recordings95.txt
load Recordings95e.txt

time95=Recordings95(:,7);
setpt95=Recordings95(:,1);
block95=Recordings95(:,3);
vial95=Recordings95(:,2);

figure(4)
plot (time95,setpt95,'k',time95,block95,'r',time95,vial95,'m-')
xlabel('Time (sec)')
ylabel('Set Point, Block, Vial (^{o}C)')
title ('Fully Loaded Vials at 95')
axis([0 max(time95) 92 max(block95)+0.5])
legend ('Set Point', 'Block', 'Vial')
datacursormode()

% Graphical input for 95
c1=ginput(1);
c1i=find(time95>c1(1),1);
c2=ginput(1);
c2i=find(time95>c2(1),1);
c3=ginput(1);
c3i=find(time95>c3(1),1);
c4=ginput(1);
c4i=find(time95>c4(1),1);
c5=ginput(1);
c5i=find(time95>c5(1),1);
c6=ginput(1);
c6i=find(time95>c6(1),1);
c7=ginput(1);
c7i=find(time95>c7(1),1);
c8=ginput(1);
c8i=find(time95>c8(1),1);
c9=ginput(1);
c9i=find(time95>c9(1),1);
c10=ginput(1);
c10i=find(time95>c10(1),1);
c11=ginput(1);
c11i=find(time95>c11(1),1);
c12=ginput(1);
c12i=find(time95>c12(1),1);
c13=ginput(1);
c13i=find(time95>c13(1),1);
c14=ginput(1);
c14i=find(time95>c14(1),1);
c15=ginput(1);
c15i=find(time95>c15(1),1);
c16=ginput(1);
c16i=find(time95>c16(1),1);
c17=ginput(1);
c17i=find(time95>c17(1),1);
c18=ginput(1);
c18i=find(time95>c18(1),1);
c19=ginput(1);
c19i=find(time95>c19(1),1);
c20=ginput(1);
c20i=find(time95>c20(1),1);

% Raw Data 95e Figure

 %Breaking matrix 95e into vectors
time95e=Recordings95e(:,7);
setpt95e=Recordings95e(:,1);
block95e=Recordings95e(:,3);
vial95e=Recordings95e(:,2);


figure(5)
plot (time95e,setpt95e,'k',time95e,block95e,'r',time95e,vial95e,'m-')
xlabel('Time (sec)')
ylabel('Set Point, Block, Vial (^{o}C)')
title ('Mean Temperature at Holds: Al Ni Plated Bracket Heat Sink 46.5')
axis([0 max(time95e) 92 max(block95e)+0.5])
legend ('Set Point', 'Block', 'Vial')
datacursormode()


% Graphical input for 95
d1=ginput(1);
d1i=find(time95e>d1(1),1);
d2=ginput(1);
d2i=find(time95e>d2(1),1);
d3=ginput(1);
d3i=find(time95e>d3(1),1);
d4=ginput(1);
d4i=find(time95e>d4(1),1);
d5=ginput(1);
d5i=find(time95e>d5(1),1);
d6=ginput(1);
d6i=find(time95e>d6(1),1);
d7=ginput(1);
d7i=find(time95e>d7(1),1);
d8=ginput(1);
d8i=find(time95e>d8(1),1);
d9=ginput(1);
d9i=find(time95e>d9(1),1);
d10=ginput(1);
d10i=find(time95e>d10(1),1);
d11=ginput(1);
d11i=find(time95e>d11(1),1);
d12=ginput(1);
d12i=find(time95e>d12(1),1);
d13=ginput(1);
d13i=find(time95e>d13(1),1);
d14=ginput(1);
d14i=find(time95e>d14(1),1);
d15=ginput(1);
d15i=find(time95e>d15(1),1);
d16=ginput(1);
d16i=find(time95e>d16(1),1);
d17=ginput(1);
d17i=find(time95e>d17(1),1);
d18=ginput(1);
d18i=find(time95e>d18(1),1);
d19=ginput(1);
d19i=find(time95e>d19(1),1);
d20=ginput(1);
d20i=find(time95e>d20(1),1);



% For Bar Plot 95 and 95e
P1a95=vial95(c1i:c2i);
P2a95=vial95(c3i:c4i);
P3a95=vial95(c5i:c6i);
P4a95=vial95(c7i:c8i);
P5a95=vial95(c9i:c10i);

P1b95=vial95(c11i:c12i);
P2b95=vial95(c13i:c14i);
P3b95=vial95(c15i:c16i);
P4b95=vial95(c17i:c18i);
P5b95=vial95(c19i:c20i);



P1a95e=vial95e(d1i:d2i);
P2a95e=vial95e(d3i:d4i);
P3a95e=vial95e(d5i:d6i);
P4a95e=vial95e(d7i:d8i);
P5a95e=vial95e(d9i:d10i);

P1b95e=vial95e(d11i:d12i);
P2b95e=vial95e(d13i:d14i);
P3b95e=vial95e(d15i:d16i);
P4b95e=vial95e(d17i:d18i);
P5b95e=vial95e(d19i:d20i);



AveP95= [mean(P1a95) mean(P1b95) mean(P1a95e) mean(P1b95e);
         mean(P2a95) mean(P2b95) mean(P2a95e) mean(P2b95e);
         mean(P3a95) mean(P3b95) mean(P3a95e) mean(P3b95e);
         mean(P4a95) mean(P4b95) mean(P4a95e) mean(P4b95e);
         mean(P5a95) mean(P5b95) mean(P5a95e) mean(P5b95e)];
          
StdP95=  [std(P1a95) std(P1b95) std(P1a95e) std(P1b95e);
         std(P2a95) std(P2b95) std(P2a95e) std(P2b95e);
         std(P3a95) std(P3b95) std(P3a95e) std(P3b95e);
         std(P4a95) std(P4b95) std(P4a95e) std(P4b95e);
         std(P5a95) std(P5b95) std(P5a95e) std(P5b95e)];       
             
figure (6)
bar(AveP95);
set(gca,'XTickLabel',{'P1','P2','P3','P4','P5'})
ylabel('Average Temperature (^{o}C)')
title ('Mean Temperature at Holds: Al Ni Plated Bracket Heat Sink 46.5')
axis ([ 0 6 94.5 96.5])
legend ('Filled P95 Trial 1', 'Filled P95 Trial 2',...
        '1 Vial P95 Trial 1', '1 Vial P95 Trial 2',0)
    grid on
datacursormode()
    
disp(AveP57)
disp(StdP57)
disp(AveP95)
disp(StdP95)
pwr57=Recordings57(:,4);
pwr57i=pwr57(3000:length(pwr57));
disp(mean(pwr57i))
disp(std(pwr57i))

% Standard Dev Bars

figure (7)
bar(StdP57)
set(gca,'XTickLabel',{'P1','P2','P3','P4','P5'})
ylabel('Standard Deviation')
title ('Standard Deviation at Holds')
legend ('Filled P57 Trial 1', 'Filled P57 Trial 2',...
        '1 Vial P57 Trial 1', '1 Vial P57 Trial 2',0)
    grid on
    
 figure (8)   
 bar(StdP95)
set(gca,'XTickLabel',{'P1','P2','P3','P4','P5'})
ylabel('Standard Deviation')
title ('Standard Deviation at Holds')
legend ('Filled P95 Trial 1', 'Filled P95 Trial 2',...
        '1 Vial P95 Trial 1', '1 Vial P95 Trial 2',0)
    grid on