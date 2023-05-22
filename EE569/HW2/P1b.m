% Name: Chengyu Lu
% USC ID Number: 5157638886
% USC Email: luchengy@usc.edu
% Submission Date: 01/29/2023
clear all
close all
clc

tigerRGB = imread('Tiger.jpg');
pigRGB = imread('Pig.jpg');
tigerGrayscale = rgb2gray(tigerRGB);
pigGrayscale = rgb2gray(pigRGB);

tigerResult12 = edge(tigerGrayscale, 'canny', [0.1 0.2]);
pigResult12 = edge(pigGrayscale, 'canny', [0.1 0.2]);
tigerResult24 = edge(tigerGrayscale, 'canny', [0.2 0.4]);
pigResult24 = edge(pigGrayscale, 'canny', [0.2 0.4]);
tigerResult36 = edge(tigerGrayscale, 'canny', [0.3 0.6]);
pigResult36 = edge(pigGrayscale, 'canny', [0.3 0.6]);
tigerResult48 = edge(tigerGrayscale, 'canny', [0.4 0.8]);
pigResult48 = edge(pigGrayscale, 'canny', [0.4 0.8]);
tigerResult13 = edge(tigerGrayscale, 'canny', [0.1 0.3]);
pigResult13 = edge(pigGrayscale, 'canny', [0.1 0.3]);
tigerResult26 = edge(tigerGrayscale, 'canny', [0.2 0.6]);
pigResult26 = edge(pigGrayscale, 'canny', [0.2 0.6]);
tigerResult39 = edge(tigerGrayscale, 'canny', [0.3 0.9]);
pigResult39 = edge(pigGrayscale, 'canny', [0.3 0.9]);
tigerResult14 = edge(tigerGrayscale, 'canny', [0.1 0.4]);
pigResult14 = edge(pigGrayscale, 'canny', [0.1 0.4]);
tigerResult28 = edge(tigerGrayscale, 'canny', [0.2 0.8]);
pigResult28 = edge(pigGrayscale, 'canny', [0.2 0.8]);

figure('Name','Tiger');
subplot(3,3,1),imshow(tigerResult12),title('[0.1 0.2]');
subplot(3,3,2),imshow(tigerResult24),title('[0.2 0.4]');
subplot(3,3,3),imshow(tigerResult36),title('[0.3 0.6]');
subplot(3,3,4),imshow(tigerResult48),title('[0.4 0.8]');
subplot(3,3,5),imshow(tigerResult13),title('[0.1 0.3]');
subplot(3,3,6),imshow(tigerResult26),title('[0.2 0.6]');
subplot(3,3,7),imshow(tigerResult39),title('[0.3 0.9]');
subplot(3,3,8),imshow(tigerResult14),title('[0.1 0.4]');
subplot(3,3,9),imshow(tigerResult28),title('[0.2 0.8]');

figure('Name','Pig');
subplot(3,3,1),imshow(pigResult12),title('[0.1 0.2]');
subplot(3,3,2),imshow(pigResult24),title('[0.2 0.4]');
subplot(3,3,3),imshow(pigResult36),title('[0.3 0.6]');
subplot(3,3,4),imshow(pigResult48),title('[0.4 0.8]');
subplot(3,3,5),imshow(pigResult13),title('[0.1 0.3]');
subplot(3,3,6),imshow(pigResult26),title('[0.2 0.6]');
subplot(3,3,7),imshow(pigResult39),title('[0.3 0.9]');
subplot(3,3,8),imshow(pigResult14),title('[0.1 0.4]');
subplot(3,3,9),imshow(pigResult28),title('[0.2 0.8]');

imwrite(tigerResult12, 'TigerOutput12.jpg');
imwrite(pigResult12, 'PigOutput12.jpg');
imwrite(tigerResult24, 'TigerOutput24.jpg');
imwrite(pigResult24, 'PigOutput24.jpg');
imwrite(tigerResult36, 'TigerOutput36.jpg');
imwrite(pigResult36, 'PigOutput36.jpg');
imwrite(tigerResult48, 'TigerOutput48.jpg');
imwrite(pigResult48, 'PigOutput48.jpg');
imwrite(tigerResult13, 'TigerOutput13.jpg');
imwrite(pigResult13, 'PigOutput13.jpg');
imwrite(tigerResult26, 'TigerOutput26.jpg');
imwrite(pigResult26, 'PigOutput26.jpg');
imwrite(tigerResult39, 'TigerOutput39.jpg');
imwrite(pigResult39, 'PigOutput39.jpg');
imwrite(tigerResult14, 'TigerOutput14.jpg');
imwrite(pigResult14, 'PigOutput14.jpg');
imwrite(tigerResult28, 'TigerOutput28.jpg');
imwrite(pigResult28, 'PigOutput28.jpg');