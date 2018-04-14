% analysis of IR camera data from experiment 4-06 to determine threshold changes

% clear workspace
clear;

% get data for analysis
filename = '4-13TestData/config3.csv';
M = csvread(filename);

% separate raw data into different arrays
dimM = size(M);
% start at 135 for test3, start at 120 for test 2
rawTempMat = M(135:dimM(1), 3:dimM(2) - 1);
dimTempMat = size(rawTempMat);

% make list of outlier points
ctr = 1;
for ii = 1:1:dimTempMat(1)
    for jj = 1:1:dimTempMat(2)
        if rawTempMat(ii,jj) > 140 || rawTempMat(ii,jj) < 20
            m_outlier(ctr) = ii;
            n_outlier(ctr) = jj;
            ctr = ctr + 1;
        end
    end
end

% ignore outer perimeter of data points and outliers
averageTemp = zeros(1,dimTempMat(1));
ignorePoints = [1:8, 57:64, 9:8:49, 16:8:56];
jjDesired = [10:15, 18:23, 26:31, 34:39, 42:47, 50:55];
for ii = 1:1:dimTempMat(1)
    ctr = 0;
    for jj = jjDesired
        if (~(ismember(ii, m_outlier) && ismember(jj, n_outlier)))
            averageTemp(ii) = averageTemp(ii) + rawTempMat(ii, jj);
            ctr = ctr + 1;
        end
    end
    averageTemp(ii) = averageTemp(ii)/ctr;
end

% exponential filtering
weight = .9;
expFilteredTemp = zeros(1, length(averageTemp) - 1);
for ii = 1:1:length(expFilteredTemp)
    expFilteredTemp(ii) = averageTemp(ii)*(1-weight) + averageTemp(ii + 1)*(weight);
end

% butterworth filtering
[b, a] = butter(6, .7, 'low');
butterFilteredCurrent = filter(b, a, averageTemp);

% averaging 
avgCount = 10;
ctr = 1;
while ctr*avgCount < length(averageTemp)
    timeAvgTemp(ctr) = 0;
    for ii = 1:1:avgCount
        timeAvgTemp(ctr) = timeAvgTemp(ctr) + averageTemp((ctr - 1)*avgCount + ii);
    end
    timeAvgTemp(ctr) = timeAvgTemp(ctr) / avgCount;
    ctr = ctr + 1;
end

% polyfit - hard to implement in realtime
p = polyfit(1:1:length(averageTemp), averageTemp, 1);
linCurrent = p(1)*(1:1:length(averageTemp)) + p(2);

plotCtr = 5;
figure(1);
subplot(plotCtr,1,1);
plot(1:1:length(averageTemp), averageTemp);
title(strcat('inner pan space average temp','-', filename));
subplot(plotCtr,1,2);
plot(1:1:length(expFilteredTemp), expFilteredTemp);
title(strcat('exponentially filtered average temp','-', filename));
subplot(plotCtr,1,3);
plot(1:1:length(butterFilteredCurrent), butterFilteredCurrent);
title(strcat('butterworth filtered average temp','-', filename));
subplot(plotCtr,1,4);
plot(1:1:length(timeAvgTemp), timeAvgTemp)
title(strcat('time-averaging average temp','-', filename));
subplot(plotCtr,1,plotCtr);
plot(1:1:length(linCurrent), linCurrent);
title(strcat('linear fit','-', filename));
currentFigure = gcf;
currentFigure.Name = strcat('temperature analysis-', filename);