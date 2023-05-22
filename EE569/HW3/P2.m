% Name: Chengyu Lu
% USC ID Number: 5157638886
% USC Email: luchengy@usc.edu
% Submission Date: 03/09/2023
clear all
close all
clc

width = 576;
height = 432;
bytesPerPixel = 3;

leftImagePath = "left.raw";
rightImagePath = "right.raw";
middleImagePath = "middle.raw";

leftImage = readraw(leftImagePath, height, width, bytesPerPixel);
rightImage = readraw(rightImagePath, height, width, bytesPerPixel);
middleImage = readraw(middleImagePath, height, width, bytesPerPixel);

leftGrayImage = im2gray(leftImage);
rightGrayImage = im2gray(rightImage);
middleGrayImage = im2gray(middleImage);

leftSURFPoints = detectSURFFeatures(leftGrayImage);
rightSURFPoints = detectSURFFeatures(rightGrayImage);
middleSURFPoints = detectSURFFeatures(middleGrayImage);

[leftFeatures, leftPoints] = extractFeatures(leftGrayImage, leftSURFPoints);
[rightFeatures, rightPoints] = extractFeatures(rightGrayImage, rightSURFPoints);
[middleFeatures, middlePoints] = extractFeatures(middleGrayImage, middleSURFPoints);

matchedFeaturesLM = matchFeatures(middleFeatures, leftFeatures, 'Unique', true);
matchedFeaturesRM = matchFeatures(middleFeatures, rightFeatures, 'Unique', true);

matchedPointsL = leftPoints(matchedFeaturesLM(:,2), :);
matchedPointsR = rightPoints(matchedFeaturesRM(:,2), :);
matchedPointsLM = middlePoints(matchedFeaturesLM(:,1), :);
matchedPointsRM = middlePoints(matchedFeaturesRM(:,1), :);

figure(1); showMatchedFeatures(leftImage,middleImage,matchedPointsL,matchedPointsLM,'montage');
legend('matched points of left image','matched points of middle image');

figure(2); showMatchedFeatures(middleImage,rightImage,matchedPointsRM,matchedPointsR,'montage');
legend('matched points of middle image','matched points of right image');

figure(3); imshow(leftImage);
hold on;
plot(matchedPointsL([1,10,17,20]));

figure(4); imshow(middleImage);
hold on;
plot(matchedPointsLM([1,10,17,20]));

figure(5); imshow(rightImage);
hold on;
plot(matchedPointsR([6,12,21,32]));

figure(6); imshow(middleImage);
hold on;
plot(matchedPointsRM([6,12,21,32]));

canvas = zeros(height*3, width*5, 3);

canvas((height+1):(2*height), 1:width, 1) = leftImage(:,:,1);
canvas((height+1):(2*height), 1:width, 2) = leftImage(:,:,2);
canvas((height+1):(2*height), 1:width, 3) = leftImage(:,:,3);

canvas((height+1):(2*height), (2*width+1):(3*width), 1) = middleImage(:,:,1);
canvas((height+1):(2*height), (2*width+1):(3*width), 2) = middleImage(:,:,2);
canvas((height+1):(2*height), (2*width+1):(3*width), 3) = middleImage(:,:,3);

canvas((height+1):(2*height), (4*width+1):(5*width), 1) = rightImage(:,:,1);
canvas((height+1):(2*height), (4*width+1):(5*width), 2) = rightImage(:,:,2);
canvas((height+1):(2*height), (4*width+1):(5*width), 3) = rightImage(:,:,3);

figure(7);imshow(uint8(canvas));


leftPointsX = matchedPointsL.Location([1,10,17,20],1);
leftPointsY = matchedPointsL.Location([1,10,17,20],2);

middleLeftPointsX =  matchedPointsLM.Location([1,10,17,20],1);
middleLeftPointsY =  matchedPointsLM.Location([1,10,17,20],2);

middleRightPointsX =  matchedPointsRM.Location([6,12,21,32],1);
middleRightPointsY =  matchedPointsRM.Location([6,12,21,32],2);

rightPointsX = matchedPointsR.Location([6,12,21,32],1);
rightPointsY = matchedPointsR.Location([6,12,21,32],2);

leftPointsY = leftPointsY + height;
 
middleLeftPointsX = middleLeftPointsX + 2*width;
middleLeftPointsY = middleLeftPointsY + height;

middleRightPointsX = middleRightPointsX + 2*width;
middleRightPointsY = middleRightPointsY + height;

rightPointsX = rightPointsX + 4*width;
rightPointsY = rightPointsY + height;

syms h11Left h12Left h13Left h21Left h22Left h23Left h31Left h32Left
eqn1 = h11Left*leftPointsX(1) + h12Left*leftPointsY(1) + h13Left == middleLeftPointsX(1)*(h31Left*leftPointsX(1) + h32Left*leftPointsY(1) + 1);
eqn2 = h21Left*leftPointsX(1) + h22Left*leftPointsY(1) + h23Left == middleLeftPointsY(1)*(h31Left*leftPointsX(1) + h32Left*leftPointsY(1) + 1);
eqn3 = h11Left*leftPointsX(2) + h12Left*leftPointsY(2) + h13Left == middleLeftPointsX(2)*(h31Left*leftPointsX(2) + h32Left*leftPointsY(2) + 1);
eqn4 = h21Left*leftPointsX(2) + h22Left*leftPointsY(2) + h23Left == middleLeftPointsY(2)*(h31Left*leftPointsX(2) + h32Left*leftPointsY(2) + 1);
eqn5 = h11Left*leftPointsX(3) + h12Left*leftPointsY(3) + h13Left == middleLeftPointsX(3)*(h31Left*leftPointsX(3) + h32Left*leftPointsY(3) + 1);
eqn6 = h21Left*leftPointsX(3) + h22Left*leftPointsY(3) + h23Left == middleLeftPointsY(3)*(h31Left*leftPointsX(3) + h32Left*leftPointsY(3) + 1);
eqn7 = h11Left*leftPointsX(4) + h12Left*leftPointsY(4) + h13Left == middleLeftPointsX(4)*(h31Left*leftPointsX(4) + h32Left*leftPointsY(4) + 1);
eqn8 = h21Left*leftPointsX(4) + h22Left*leftPointsY(4) + h23Left == middleLeftPointsY(4)*(h31Left*leftPointsX(4) + h32Left*leftPointsY(4) + 1);
[A,B] = equationsToMatrix([eqn1, eqn2, eqn3, eqn4, eqn5, eqn6, eqn7, eqn8], [h11Left, h12Left, h13Left, h21Left, h22Left, h23Left, h31Left, h32Left]);
X = linsolve(A,B);
leftParameter = [double(X(1)) double(X(2)) double(X(3)); double(X(4)) double(X(5)) double(X(6)); double(X(7)) double(X(8)) double(1)];

syms h11Right h12Right h13Right h21Right h22Right h23Right h31Right h32Right
eqn1 = h11Right*rightPointsX(1) + h12Right*rightPointsY(1) + h13Right == middleRightPointsX(1)*(h31Right*rightPointsX(1) + h32Right*rightPointsY(1) + 1);
eqn2 = h21Right*rightPointsX(1) + h22Right*rightPointsY(1) + h23Right == middleRightPointsY(1)*(h31Right*rightPointsX(1) + h32Right*rightPointsY(1) + 1);
eqn3 = h11Right*rightPointsX(2) + h12Right*rightPointsY(2) + h13Right == middleRightPointsX(2)*(h31Right*rightPointsX(2) + h32Right*rightPointsY(2) + 1);
eqn4 = h21Right*rightPointsX(2) + h22Right*rightPointsY(2) + h23Right == middleRightPointsY(2)*(h31Right*rightPointsX(2) + h32Right*rightPointsY(2) + 1);
eqn5 = h11Right*rightPointsX(3) + h12Right*rightPointsY(3) + h13Right == middleRightPointsX(3)*(h31Right*rightPointsX(3) + h32Right*rightPointsY(3) + 1);
eqn6 = h21Right*rightPointsX(3) + h22Right*rightPointsY(3) + h23Right == middleRightPointsY(3)*(h31Right*rightPointsX(3) + h32Right*rightPointsY(3) + 1);
eqn7 = h11Right*rightPointsX(4) + h12Right*rightPointsY(4) + h13Right == middleRightPointsX(4)*(h31Right*rightPointsX(4) + h32Right*rightPointsY(4) + 1);
eqn8 = h21Right*rightPointsX(4) + h22Right*rightPointsY(4) + h23Right == middleRightPointsY(4)*(h31Right*rightPointsX(4) + h32Right*rightPointsY(4) + 1);
[A,B] = equationsToMatrix([eqn1, eqn2, eqn3, eqn4, eqn5, eqn6, eqn7, eqn8], [h11Right, h12Right, h13Right, h21Right, h22Right, h23Right, h31Right, h32Right]);
X = linsolve(A,B);
rightParameter = [double(X(1)) double(X(2)) double(X(3)); double(X(4)) double(X(5)) double(X(6)); double(X(7)) double(X(8)) double(1)];

tempCanvas = zeros(height*3, width*5, 3);
tempCanvas((height+1):(2*height), (2*width+1):(3*width), 1) = middleImage(:,:,1);
tempCanvas((height+1):(2*height), (2*width+1):(3*width), 2) = middleImage(:,:,2);
tempCanvas((height+1):(2*height), (2*width+1):(3*width), 3) = middleImage(:,:,3);
tempCanvas = uint8(tempCanvas);

for i = 1:height
    for j = 1:width
        for k = 1:bytesPerPixel
            xL = j-0.5;
            yL = (i+height)-0.5;
            tempXL = xL*leftParameter(1,1) + yL*leftParameter(1,2) + leftParameter(1,3);
            tempYL = xL*leftParameter(2,1) + yL*leftParameter(2,2) + leftParameter(2,3);
            tempWL = xL*leftParameter(3,1) + yL*leftParameter(3,2) + leftParameter(3,3);
            xTempL = tempXL/tempWL;
            yTempL = tempYL/tempWL;
            iTempL = round(yTempL-0.5);
            jTempL = round(xTempL+0.5);
            if (((height+1)<=iTempL)&&(iTempL<=(2*height))) && (((2*width+1)<=jTempL)&&(jTempL<=(3*width)))
                tempCanvas(iTempL, jTempL, k) = tempCanvas(iTempL, jTempL, k);
            else
                tempCanvas(iTempL, jTempL, k) = leftImage(i,j,k);
            end
            
            xR = (j+4*width)-0.5;
            yR = (i+height)-0.5;
            tempXR = xR*rightParameter(1,1) + yR*rightParameter(1,2) + rightParameter(1,3);
            tempYR = xR*rightParameter(2,1) + yR*rightParameter(2,2) + rightParameter(2,3);
            tempWR = xR*rightParameter(3,1) + yR*rightParameter(3,2) + rightParameter(3,3);
            xTempR = tempXR/tempWR;
            yTempR = tempYR/tempWR;
            iTempR = round(yTempR-0.5);
            jTempR = round(xTempR+0.5);
            if (((height+1)<=iTempR)&&(iTempR<=(2*height))) && (((2*width+1)<=jTempR)&&(jTempR<=(3*width)))
                tempCanvas(iTempR, jTempR, k) = tempCanvas(iTempR, jTempR, k);
            else
                tempCanvas(iTempR, jTempR, k) = rightImage(i,j,k);
            end
        end
    end
end

figure(8); imshow(tempCanvas);
result = tempCanvas;

for i = 2:(height*3-1)
    for j = 2:(width*5-1)
        for k = 1:3
            if tempCanvas(i,j, k) == 0
                temp = 0;
                number = 0;
                if tempCanvas(i-1, j-1, k) ~= 0
                    temp = temp + double(tempCanvas(i-1, j-1, k));
                    number = number + 1;
                end
                if tempCanvas(i-1, j, k) ~= 0
                    temp = temp + double(tempCanvas(i-1, j, k));
                    number = number + 1;
                end
                if tempCanvas(i-1, j+1, k) ~= 0
                    temp = temp + double(tempCanvas(i-1, j+1, k));
                    number = number + 1;
                end
                if tempCanvas(i, j-1, k) ~= 0
                    temp = temp + double(tempCanvas(i, j-1, k));
                    number = number + 1;
                end
                if tempCanvas(i, j+1, k) ~= 0
                    temp = temp + double(tempCanvas(i, j+1, k));
                    number = number + 1;
                end
                if tempCanvas(i+1, j-1, k) ~= 0
                    temp = temp + double(tempCanvas(i+1, j-1, k));
                    number = number + 1;
                end
                if tempCanvas(i+1, j+1, k) ~= 0
                    temp = temp + double(tempCanvas(i+1, j+1, k));
                    number = number + 1;
                end
                if tempCanvas(i+1, j, k) ~= 0
                    temp = temp + double(tempCanvas(i+1, j, k));
                    number = number + 1;
                end
                if number ~= 0
                    result(i,j, k) = uint8(temp/number);
                end
            end
        end
    end
end

figure(9);imshow(result);