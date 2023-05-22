% Name: Chengyu Lu
% USC ID Number: 5157638886
% USC Email: luchengy@usc.edu
% Submission Date: 02/19/2023
clear all;
close all;
clc

tigerInput = imread('tiger.jpg');
pigInput = imread('pig.jpg');

opts=edgesTrain();                % default options (good settings)
opts.modelDir='models/';          % model will be in models/forest
opts.modelFnm='modelBsds';        % model name
opts.nPos=5e5; opts.nNeg=5e5;     % decrease to speedup training
opts.useParfor=0;                 % parallelize if sufficient memory

tic, model=edgesTrain(opts); toc; % will load model if already trained

model.opts.multiscale=1;          % for top accuracy set multiscale=1
model.opts.sharpen=2;             % for top speed set sharpen=0
model.opts.nTreesEval=20;          % for top speed set nTreesEval=1
model.opts.nThreads=4;            % max number threads for evaluation
model.opts.nms=1;                 % set to true to enable nms

tic, tigerED = edgesDetect(tigerInput, model); toc;
figure(1); im(tigerInput); figure(2); im(tigerED);

tic, pigED = edgesDetect(pigInput, model); toc;
figure(3); im(pigInput); figure(4); im(pigED);

imwrite(tigerED, '../tigerED.jpg');
imwrite(pigED, '../pigED.jpg');

save('../Tiger.mat', 'tigerED');
save('../Pig.mat', 'pigED');

tigerBinary = zeros(321, 481);
pigBinary = zeros(321, 481);
for i = 1 : 321
   for j = 1 : 481
      if tigerED(i,j) >= 0.1 %threshold
          tigerBinary(i,j) = 255;
      else
          tigerBinary(i,j) = 0;
      end
      if pigED(i,j) >= 0.15 %threshold
          pigBinary(i,j) = 255;
      else
          pigBinary(i,j) = 0;
      end
   end
end

figure(5); imshow(tigerBinary);
figure(6); imshow(pigBinary);

imwrite(tigerBinary, '../tigerBinary1.jpg');
imwrite(pigBinary, '../pigBinary15.jpg');