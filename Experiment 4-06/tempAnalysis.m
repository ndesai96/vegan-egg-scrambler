% analysis of IR camera data from experiment 4-06 to determine threshold changes

% clear workspace
clear;

% get data for analysis
filename = 'test2.csv';
M = csvread(filename);

% separate raw data into different arrays
dimM = size(M);
rawTempMat = M(:, 2:dimM(2));

% eliminate sure outliers
if  
reducedTempMat = 
