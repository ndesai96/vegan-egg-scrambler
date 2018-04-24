
clear all; close all;
d1= -1:.1:1;
d2= -1:.1:1;
figure 
%Cook Time: Delay vs Water Temp
subplot(2,3,1)
[D1,D2] = meshgrid(d1,d2);
y = 0.15667 -0.00839*D1-0.00132*D2+0.008679*D1.*D2;
surf(D1,D2,y);
title("Cook Rate: Delay vs Water Temp");
xlabel("Delay");
ylabel("Water Temp");

%Cook Time: Delay vs Propeller
subplot(2,3,2)
[D1,D2] = meshgrid(d1,d2);
y = 0.15667 -0.00839*D1+0.03707*D2-.01342*D1.*D2;
surf(D1,D2,y);
title("Cook Rate: Delay vs Propeller");
xlabel("Delay");
ylabel("Propeller");


%Cook Time: Water vs Propeller
subplot(2,3,3)
[D1,D2] = meshgrid(d1,d2);
y = 0.15667 -0.00132*D1+0.03707*D2-.01079*D1.*D2;
surf(D1,D2,y);
title("Cook Rate: Water vs Propeller");
xlabel("Water");
ylabel("Propeller");


%Final Temp: Delay vs Water
subplot(2,3,4)
[D1,D2] = meshgrid(d1,d2);
y = 66.5046 -2.60756*D1+1.779782*D2-.81431*D1.*D2;
surf(D1,D2,y);
title("Temperature: Delay vs Water");
xlabel("Delay");
ylabel("Water");

%Final Temp: Delay vs Propeller
subplot(2,3,5)
[D1,D2] = meshgrid(d1,d2);
y = 66.50546+ -2.60756*D1-3.689*D2-.15803*D1.*D2;
surf(D1,D2,y);
title("Temperature: Delay vs Propeller");
xlabel("Delay");
ylabel("Propeller");

%Final Temp: Water vs Propeller
subplot(2,3,6)
[D1,D2] = meshgrid(d1,d2);
y = 66.5046 + 1.779782*D1-3.689*D2+3.376498*D1.*D2;
surf(D1,D2,y);
title("Temperature: Water vs Propeller");
xlabel("Water");
ylabel("Propeller");

