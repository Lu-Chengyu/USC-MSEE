% Name: Chengyu Lu
% USC ID Number: 5157638886
% USC Email: luchengy@usc.edu
% Submission Date: 02/19/2023
clear all;
close all;
clc

tigerGT = 'Tiger_GT.mat';
pigGT = 'Pig_GT.mat';
numThresh = 20;
tigerSobel = load('tigerSobel.txt');
pigSobel = load('pigSobel.txt');
tigerCanny = load('tigerCanny.txt');
pigCanny = load('pigCanny.txt');
tigerSE = load('Tiger.mat');
tigerSE = tigerSE.tigerED;
pigSE = load('Pig.mat');
pigSE = pigSE.pigED;

% [meanP, meanR, F, P, R]
[tigerSobelMeanP, tigerSobelMeanR, tigerSobelF, tigerSobelP, tigerSobelR] = sobelCanny(tigerGT, tigerSobel);
[pigSobelMeanP, pigSobelMeanR, pigSobelF, pigSobelP, pigSobelR] = sobelCanny(pigGT, pigSobel);
[tigerCannyMeanP, tigerCannyMeanR, tigerCannyF, tigerCannyP, tigerCannyR] = sobelCanny(tigerGT, tigerCanny);
[pigCannyMeanP, pigCannyMeanR, pigCannyF, pigCannyP, pigCannyR] = sobelCanny(pigGT, pigCanny);

% [meanP, meanR, F, T]
[tigerSEP, tigerSER, tigerSEF, tigerSET] = structuredEdge(tigerGT, tigerSE, numThresh);
[pigSEP, pigSER, pigSEF, pigSET] = structuredEdge(pigGT, pigSE, numThresh);

function [meanP, meanR, F, P, R] = sobelCanny(GT, E)
    g = load(GT);
    g = g.groundTruth;
    numGT = size(g, 2);
    P = zeros(numGT, 1);
    R = zeros(numGT, 1);
    for i = 1 : numGT
       groundTruth{1} = g{i};
       G = ['gt_temp_', num2str(i), '.mat'];
       save(G, 'groundTruth');
       [thrs, cntR, sumR, cntP, sumP, V] = edgesEvalImg(E, G, {'thrs', 1}); 
       delete(G);
       P(i) = cntP / sumP;
       R(i) = cntR / sumR;
    end
    meanP = mean(P);
    meanR = mean(R);   
    F = 2 * (meanP * meanR) / (meanP + meanR);
end

function [meanP, meanR, F, T] = structuredEdge(GT, E, numThresh)
    g = load(GT);
    g = g.groundTruth;
    numGT = size(g, 2);
    P = zeros(numGT, numThresh);
    R = zeros(numGT, numThresh);
    for i = 1 : numGT
       groundTruth{1} = g{i};
       G = ['gt_temp_', num2str(i), '.mat'];
       save(G, 'groundTruth');
       [thrs, cntR, sumR, cntP, sumP, V] = edgesEvalImg(E, G, {'thrs', numThresh}); 
       delete(G);
       P(i,:) = cntP ./ sumP;
       R(i,:) = cntR ./ sumR;
       T = thrs;
    end
    meanP = zeros(numThresh, 1);
    meanR = zeros(numThresh, 1);
    F = zeros(numThresh, 1);
    for i = 1 : numThresh
        meanP(i) = mean(P(:,i));
        meanR(i) = mean(R(:,i));
        F(i) = 2 * (meanP(i) * meanR(i)) / (meanP(i)+meanR(i));
    end
end