% analysis of current sensor data to determine threshold changes

% clear workspace
clear;

% get data for analysis
filename = '4-06TestData/test2.csv';
M = csvread(filename);

% separate raw data into different arrays
dimM = size(M);
rawCurrent = M(:,1);

% % ignore outlier data points
% ctr = 1;
% for ii = 1:1:dimM(1)
%     if rawCurrent(ii) < .5 && rawCurrent(ii) > .05
%           reducedCurrent(ctr) = rawCurrent(ii);
%           ctr = ctr + 1;
%     end
% end
% 
% % exponential filtering
% weight = .9;
% expFilteredCurrent = zeros(1, length(reducedCurrent) - 1);
% for ii = 1:1:length(expFilteredCurrent)
%     expFilteredCurrent(ii) = reducedCurrent(ii)*(1-weight) + reducedCurrent(ii + 1)*(weight);
% end
% 
% % butterworth filtering
% [b, a] = butter(6, .7, 'low');
% butterFilteredCurrent = filter(b, a, reducedCurrent);
% 
% % averaging 
% avgCount = 5;
% ctr = 1;
% while ctr*avgCount < length(reducedCurrent)
%     avgCurrent(ctr) = 0;
%     for ii = 1:1:avgCount
%         avgCurrent(ctr) = avgCurrent(ctr) + reducedCurrent((ctr - 1)*avgCount + ii);
%     end
%     avgCurrent(ctr) = avgCurrent(ctr) / avgCount;
%     ctr = ctr + 1;
% end
% % polyfit - hard to implement in realtime
% p = polyfit(1:1:length(reducedCurrent), reducedCurrent, 1);
% linCurrent = p(1)*(1:1:length(reducedCurrent)) + p(2);

% adding a "pseudo-time" dependence
rawCurrentLen = length(rawCurrent);
ctr = 1;
conCtr = 1;
minCurrent = 0;
maxCurrent = 0;
while (ctr + 5 < rawCurrentLen)
    if rawCurrent(ctr) > .05 && rawCurrent(ctr) < .5
        for ii = 1:1:10
                if ii == 1
                    minCurrent = rawCurrent(ctr);
                    maxCurrent = rawCurrent(ctr);
                else
                    minCurrent = min(rawCurrent(ctr), minCurrent);
                    maxCurrent = max(rawCurrent(ctr), maxCurrent);
                end
                ctr = ctr + 1;
        end
        ctr = ctr - 1;
    end
        ctr = ctr + 1;
        consistency(conCtr) = minCurrent*(1 - (ctr/300)) + maxCurrent*(ctr/300);
        conCtr = conCtr + 1;
        
end

% exponentially filtered consistency 
weight = .3;
for ii = 2:1:length(consistency)
    consistency(ii) = consistency(ii)*weight + consistency(ii-1)*(1-weight);
end

    
        

plotCtr = 5;
figure(1);
% subplot(plotCtr,1,1);
% plot(1:1:length(rawCurrent), rawCurrent);
% title(strcat('raw current','-', filename));
% subplot(plotCtr,1,2);
% plot(1:1:length(reducedCurrent), reducedCurrent);
% title(strcat('reduced current','-', filename));
% subplot(plotCtr,1,3);
% plot(1:1:length(avgCurrent), avgCurrent)
% title(strcat('averaging current','-', filename));
% subplot(plotCtr,1,3);
plot(1:1:conCtr - 1,consistency)
title(strcat('time dependent consistency','-', filename));
% subplot(plotCtr,1,plotCtr);
% plot(1:1:length(linCurrent), linCurrent);
% title(strcat('linear fit','-', filename));
% currentFigure = gcf;
% currentFigure.Name = strcat('consistency analysis-', filename);