% Name: Chengyu Lu
% USC ID Number: 5157638886
% USC Email: luchengy@usc.edu
% Submission Date: 03/09/2023

clear;
close all;
clc;

height = 305;
width = 410;
bytesPerPixel = 1;

chestInput = readraw("chest_cavity.raw", height, width, bytesPerPixel);

max = 0;
for i = 1:height
    for j = 1:width
        if chestInput(i, j) > max
            max = chestInput(i, j);
        end
    end
end
for i = 1:height
    for j = 1:width
        if chestInput(i, j) >= max/2
            chestInput(i, j) = 255;
        else
            chestInput(i, j) = 0;
        end
    end
end

inversedChest = 255 - chestInput;
shrinkedImage = bwmorph(inversedChest/255, 'shrink', Inf);

figure(1);
imshow(shrinkedImage, []);
writeraw(shrinkedImage*255, "shrinkResult.raw");

pointPos = [];
pointNum = 0;

for i = 1:height
    for j = 1:width
        if shrinkedImage(i, j) == 1
            pointNum = pointNum +1;
            pointPos(pointNum, 1) = i;
            pointPos(pointNum, 2) = j;
        end
    end
end
disp("The number of points is :"+pointNum);

chestOutput = bwmorph(inversedChest, 'clean');
defects = bwconncomp(inversedChest);
chestOutput(defects.PixelIdxList{1, 12})=0;
chestOutput = 255 - chestOutput;
figure(2);
imshow(chestOutput, []);
writeraw(chestOutput, "chestOutput.raw");


%% Part c

clear;

height = 82;
width = 494;
bytesPerPixel = 3;

beansInput = readraw("beans.raw", height, width, bytesPerPixel);

grayBeans = rgb2gray(beansInput/255);
binaryBeans = ones(height,width);
for i = 1:height
    for j = 1:width
        if grayBeans(i, j) <= 0.95
            binaryBeans(i, j) = 0;
        end
    end
end
figure(3);
imshow(binaryBeans);

cleanImage = bwmorph(binaryBeans, 'shrink',1);
cleanImage = bwmorph(cleanImage, 'clean');
inversedShrinkedImage = 1- cleanImage;
inversedShrinkedImage = bwmorph(inversedShrinkedImage, 'shrink', Inf);
figure(4);
imshow(inversedShrinkedImage);

whiteDots = bwconncomp(binaryBeans);
binaryBeans(whiteDots.PixelIdxList{1, 2})=0;
binaryBeans(whiteDots.PixelIdxList{1, 3})=0;
binaryBeans(whiteDots.PixelIdxList{1, 4})=0;
figure(5);
imshow(binaryBeans);
inversedBinaryBeans = 1-binaryBeans;
figure(6);
imshow(inversedBinaryBeans);
figure(7);
diffBeans = bwconncomp(inversedBinaryBeans);
RGB_label = label2rgb(labelmatrix(diffBeans),'jet','k');
imshow(RGB_label);

rankBean = bwmorph(1-binaryBeans, 'shrink',9);
figure(8);
imshow(rankBean);
rankBean = bwmorph(rankBean, 'shrink',1);
figure(9);
imshow(rankBean);
rankBean = bwmorph(rankBean, 'shrink',6);
figure(10);
imshow(rankBean);
rankBean = bwmorph(rankBean, 'shrink',3);
figure(11);
imshow(rankBean);