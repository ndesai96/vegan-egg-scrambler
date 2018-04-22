
clear all; close all;
d1= -1:.1:1;
d2= -1:.1:1;
figure 
%Cook Time: Delay vs Water Temp
subplot(3,3,1)
[D1,D2] = meshgrid(d1,d2);
y = 447.998 + 15.859*D1-30.8151*D2-11.17*D1.*D2;
surf(D1,D2,y);

%Cook Time: Delay vs Propeller
subplot(3,3,2)
[D1,D2] = meshgrid(d1,d2);
y = 447.998 + 15.859*D1-77.95*D2-72.5*D1.*D2;
surf(D1,D2,y);

%Cook Time: Water vs Propeller
subplot(3,3,3)
[D1,D2] = meshgrid(d1,d2);
y = 447.998 + -30.8151*D1-77.95*D2-7.25*D1.*D2;
surf(D1,D2,y);

%Final Temp: Delay vs Water
subplot(3,3,4)
[D1,D2] = meshgrid(d1,d2);
y = 63.64 + 1.205*D1+1.344*D2-2.465*D1.*D2;
surf(D1,D2,y);

%Final Temp: Delay vs Propeller
subplot(3,3,5)
[D1,D2] = meshgrid(d1,d2);
y = 63.6402 + 1.205*D1-0.2153*D2-2.44*D1.*D2;
surf(D1,D2,y);

%Final Temp: Water vs Propeller
subplot(3,3,6)
[D1,D2] = meshgrid(d1,d2);
y = 63.6402 + 1.344*D1-0.215*D2+0.0734*D1.*D2;
surf(D1,D2,y);

%Material Loss: Delay vs Water
subplot(3,3,7)
[D1,D2] = meshgrid(d1,d2);
y = 69 + -.75*D1+-4.75*D2+2*D1.*D2;
surf(D1,D2,y);

%Material Loss: Delay vs Propeller
subplot(3,3,8)
[D1,D2] = meshgrid(d1,d2);
y = 69 + -.75*D1-5*D2+2.75*D1.*D2;
surf(D1,D2,y);

%Material Loss: Water vs Propeller
subplot(3,3,9)
[D1,D2] = meshgrid(d1,d2);
y = 69 + -4.75*D1-5*D2+-3,75*D1.*D2;
surf(D1,D2,y);