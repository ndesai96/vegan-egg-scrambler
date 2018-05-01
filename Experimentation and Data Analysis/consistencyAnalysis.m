% analysis of current sensor data to determine threshold changes

% clear workspace
clear;

% get data for analysis
filename = '4-20TestData/test7_run1.csv';
M = csvread(filename);

% separate raw data into different arrays
dimM = size(M);
time = (M(:,1) - M(1,1)) / 1000;
currentConsistency = M(:,2);
check = M(:,3); % use the third column to check if current or consistency value;

curCtr = 1;
conCtr = 1;
for ii = 1:1:dimM(1)
    if check(ii) > 0 
        currentTime(curCtr) = time(ii);
        rawCurrent(curCtr) = currentConsistency(ii);
        curCtr = curCtr + 1;
    else
        consistencyTime(conCtr) = time(ii);
        consistency(conCtr) = currentConsistency(ii);
        conCtr = conCtr + 1;
    end
end

        

% ignore outlier data points
ctr = 1;
for ii = 1:1:length(rawCurrent)
    if rawCurrent(ii) < .5 && rawCurrent(ii) > .05
          reducedTime(ctr) = currentTime(ii);
          reducedCurrent(ctr) = rawCurrent(ii);
          ctr = ctr + 1;
    end
end

% exponential filtering
weight = .6;
expFilteredCurrent = zeros(1, length(reducedCurrent) - 1);
for ii = 1:1:length(expFilteredCurrent)
    expFilteredCurrent(ii) = reducedCurrent(ii)*(1-weight) + reducedCurrent(ii + 1)*(weight);
end

% butterworth filtering
[b, a] = butter(6, .2, 'low');
butterFilteredCurrent = filter(b, a, reducedCurrent);

% averaging 
avgCount = 5;
ctr = 1;
while ctr*avgCount < length(reducedCurrent)
    avgCurrent(ctr) = 0;
    for ii = 1:1:avgCount
        avgCurrent(ctr) = avgCurrent(ctr) + reducedCurrent((ctr - 1)*avgCount + ii);
    end
    avgCurrent(ctr) = avgCurrent(ctr) / avgCount;
    ctr = ctr + 1;
end
% polyfit - hard to implement in realtime
p = polyfit(1:1:length(reducedCurrent), reducedCurrent, 1);
linCurrent = p(1)*(1:1:length(reducedCurrent)) + p(2);

% adding a "pseudo-time" dependence
rawCurrentLen = length(rawCurrent);
ctr = 1;
conCtr = 1;
minCurrent = 0;
maxCurrent = 0;
while (ctr + 10 < rawCurrentLen)
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
        consistency(conCtr) = minCurrent*(1 - (time(ctr)/300)) + maxCurrent*(time(ctr)/300);
        conCtr = conCtr + 1;
        
end

% exponentially filtered consistency 
weight = .6;
for ii = 2:1:length(consistency)
    consistency(ii) = consistency(ii)*weight + consistency(ii-1)*(1-weight);
end

    
        

% plotCtr = 1;
% figure(1);
% subplot(plotCtr,1,1);
% plot(reducedTime(2:end), expFilteredCurrent);
% title(strcat('exponentially-filtered current vs time'));
% xlabel('time (seconds)');
% ylabel ('exp-filtered current (A)');
% subplot(plotCtr,1,2);
% plot(1:1:length(reducedCurrent), reducedCurrent);
% title(strcat('reduced current','-', filename));
% subplot(plotCtr,1,3);
% plot(1:1:length(avgCurrent), avgCurrent)
% title(strcat('averaging current','-', filename));
% subplot(plotCtr,1,3);

% testCurrent = .11 + .09*rand(5*length(consistencyTime), 1);
% ctr = 0;
% consistency = zeros(1, length(consistencyTime));
% conCtr = 2;
% while ctr + 5 < length(testCurrent)
%     maxCurrent = 0;
%     minCurrent = 10;
%     for i = 1:1:5
%         maxCurrent = max(testCurrent(i+ctr), maxCurrent);
%         minCurrent = min(testCurrent(i + ctr), minCurrent);
%     end
%     ctr = ctr + 5;
%     consistency(conCtr) = consistency(conCtr - 1)*(1-.6) + (minCurrent*(1-(8*conCtr/300)) + maxCurrent*(8*conCtr/300))*.6;
%     conCtr = conCtr + 1;
% end


plot(consistencyTime,consistency)
title(strcat('consistency vs time - stove off'));
xlabel('time (seconds)');
ylabel('consistency');
hold on;
consistencyThreshold = zeros(1,length(consistency)) + .26;
plot(consistencyTime, consistencyThreshold);
legend('consistency', 'threshold');
hold off;

% subplot(plotCtr,1,plotCtr);
% plot(1:1:length(linCurrent), linCurrent);
% title(strcat('linear fit','-', filename));
% currentFigure = gcf;
% currentFigure.Name = strcat('consistency analysis-', filename);