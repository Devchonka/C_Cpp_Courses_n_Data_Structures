clear; close all; clc
dbstop if error

% Finding Parameters 
Nsamples = 25;
fs = 50e3;

u = linspace(-Nsamples,Nsamples,1000);

a = 1.5;
b = 0.001:1e-3:0.005 ;

figure(1)
for i = 1:length(b)

    y = a*exp(-b(i)*u.^2); 
    plot(u,y)
    hold on;
    
    
end
% a = 1.5 mJ;
% b = 0.005 um;