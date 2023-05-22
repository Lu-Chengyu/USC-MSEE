% Name: Chengyu Lu
% USC ID Number: 5157638886
% USC Email: luchengy@usc.edu
% Submission Date: 03/09/2023

clear;
close all;
clc;

height = 328;
width = 328;
bytesPerPixel = 3;

transferMatrix = [ 0 1 -164; -1 0 164; 0 0 1 ];
centerMatrix = zeros(height, width, 2);
for i = 1:height
    for j = 1:width
        temp1 = [i; j; 1];
        temp2 = transferMatrix * temp1;
        centerMatrix(i, j, 1:2) = temp2(1:2);
    end
end

originalPoints1 = [0 0; 34 34; 68 68; -17 129; -164 164; -82 82];
warpedPoints1= [0 0; 82 82; 164 164; 0 164; -164 164; -82 82];
originalPoints2 = [0 0; 82 -82; 164 -164; 129 -17; 68 68; 34 34];
warpedPoints2 = [0 0; 82 -82; 164 -164; 164 0; 164 164; 82 82];
originalPoints3= [0 0; -82 -82; -164 -164; 0 -100; 164 -164; 82 -82];
warpedPoints3= [0 0; -82 -82; -164 -164; 0 -164; 164 -164; 82 -82];
originalPoints4 = [0 0; -82 82; -164 164; -100 0; -164 -164; -82 -82];
warpedPoints4= [0 0; -82 82; -164 164; -164 0; -164 -164; -82 -82];
tempXY1 = zeros(6,6);tempXY2 = zeros(6,6);tempXY3 = zeros(6,6);tempXY4 = zeros(6,6);
for n = 1:6
    x1 = originalPoints1(n, 1);
    y1 = originalPoints1(n, 2);
    tempXY1(1, n) = 1; tempXY1(2, n) = x1; tempXY1(3, n) = y1; tempXY1(4, n) = x1*x1; tempXY1(5, n) = x1*y1;tempXY1(6, n) = y1*y1;
    x2 = originalPoints2(n, 1);
    y2 = originalPoints2(n, 2);
    tempXY2(1, n) = 1; tempXY2(2, n) = x2; tempXY2(3, n) = y2; tempXY2(4, n) = x2*x2; tempXY2(5, n) = x2*y2;tempXY2(6, n) = y2*y2;
    x3 = originalPoints3(n, 1);
    y3 = originalPoints3(n, 2);
    tempXY3(1, n) = 1; tempXY3(2, n) = x3; tempXY3(3, n) = y3; tempXY3(4, n) = x3*x3; tempXY3(5, n) = x3*y3;tempXY3(6, n) = y3*y3;
    x4 = originalPoints4(n, 1);
    y4 = originalPoints4(n, 2);
    tempXY4(1, n) = 1; tempXY4(2, n) = x4; tempXY4(3, n) = y4; tempXY4(4, n) = x4*x4; tempXY4(5, n) = x4*y4;tempXY4(6, n) = y4*y4;
end
warpingMatrix1 = transpose(warpedPoints1)/tempXY1;
warpingMatrix2 = transpose(warpedPoints2)/tempXY2;
warpingMatrix3 = transpose(warpedPoints3)/tempXY3;
warpingMatrix4 = transpose(warpedPoints4)/tempXY4;

for i = 1:height
    for j = 1:width
        x = centerMatrix(i, j, 1);
        y = centerMatrix(i, j, 2);
        tempXY = zeros(6,1);
        tempXY(1) = 1; tempXY(2) = x; tempXY(3) = y; tempXY(4) = x*x; tempXY(5) = x*y;tempXY(6) = y*y;
        warpedPoints = zeros(2,1);
        if y >= x && y >=(-x)
            warpedPoints = warpingMatrix1 * tempXY;
        elseif y <x && y >= (-x)
            warpedPoints = warpingMatrix2 * tempXY;
        elseif y <x && y < (-x)
            warpedPoints = warpingMatrix3 * tempXY;
        else
            warpedPoints = warpingMatrix4 * tempXY;
        end
        centerMatrix(i, j, 1) = warpedPoints(1);
        centerMatrix(i, j, 2) = warpedPoints(2);
    end
end

for i = 1:height
    for j = 1:width
        x = centerMatrix(i, j, 1);
        y = centerMatrix(i, j, 2);
        originalPoints = [x; y; 1];
        tempXY = zeros(6,1);
        tempXY(1) = 1; tempXY(2) = x; tempXY(3) = y; tempXY(4) = x*x; tempXY(5) = x*y; tempXY(6) = y*y;
        warpedPoints = transferMatrix \ originalPoints;
        centerMatrix(i, j, 1) = warpedPoints(1);
        centerMatrix(i, j, 2) = warpedPoints(2);
    end
end

dogInput = readraw('dog.raw', height, width, bytesPerPixel);
warpedDog = zeros(height,width, bytesPerPixel);
catInput = readraw('cat.raw', height, width, bytesPerPixel);
warpedCat = zeros(height,width, bytesPerPixel);
for i = 1:height
    for j = 1:width
        for channel = 1: bytesPerPixel
            if round(centerMatrix(i, j, 1))>0 && round(centerMatrix(i,j,2))>0 && round(centerMatrix(i, j, 1))<=height &&round(centerMatrix(i,j,2))<=width
                warpedDog(i, j, channel) = dogInput(round(centerMatrix(i, j, 1)), round(centerMatrix(i,j,2)), channel);
                warpedCat(i, j, channel) = catInput(round(centerMatrix(i, j, 1)), round(centerMatrix(i,j,2)), channel);
            end
        end
    end
end

figure(1);
imshow(rescale(warpedDog));
figure(2);
imshow(rescale(warpedCat));

writeraw(warpedDog, "warpedDog.raw");
writeraw(warpedCat, "warpedCat.raw");



centerMatrix = zeros(height, width, 2);
for i = 1:height
    for j = 1:width
        temp1 = [i; j; 1];
        temp2 = transferMatrix * temp1;
        centerMatrix(i, j, 1:2) = temp2(1:2);
    end
end

for n = 1:6
    x1 = warpedPoints1(n, 1);
    y1 = warpedPoints1(n, 2);
    tempXY1(1, n) = 1; tempXY1(2, n) = x1; tempXY1(3, n) = y1; tempXY1(4, n) = x1*x1; tempXY1(5, n) = x1*y1;tempXY1(6, n) = y1*y1;
    x2 = warpedPoints2(n, 1);
    y2 = warpedPoints2(n, 2);
    tempXY2(1, n) = 1; tempXY2(2, n) = x2; tempXY2(3, n) = y2; tempXY2(4, n) = x2*x2; tempXY2(5, n) = x2*y2;tempXY2(6, n) = y2*y2;
    x3 = warpedPoints3(n, 1);
    y3 = warpedPoints3(n, 2);
    tempXY3(1, n) = 1; tempXY3(2, n) = x3; tempXY3(3, n) = y3; tempXY3(4, n) = x3*x3; tempXY3(5, n) = x3*y3;tempXY3(6, n) = y3*y3;
    x4 = warpedPoints4(n, 1);
    y4 = warpedPoints4(n, 2);
    tempXY4(1, n) = 1; tempXY4(2, n) = x4; tempXY4(3, n) = y4; tempXY4(4, n) = x4*x4; tempXY4(5, n) = x4*y4;tempXY4(6, n) = y4*y4;
end
warpingMatrix1 = transpose(originalPoints1)/tempXY1;
warpingMatrix2 = transpose(originalPoints2)/tempXY2;
warpingMatrix3 = transpose(originalPoints3)/tempXY3;
warpingMatrix4 = transpose(originalPoints4)/tempXY4;

for i = 1:height
    for j = 1:width
        x = centerMatrix(i, j, 1);
        y = centerMatrix(i, j, 2);
        tempXY = zeros(6,1);
        tempXY(1) = 1; tempXY(2) = x; tempXY(3) = y;
        tempXY(4) = x*x; tempXY(5) = x*y;tempXY(6) = y*y;
        warpedPoints = zeros(2,1);
        if y >= x && y >=(-x)
            warpedPoints = warpingMatrix1 * tempXY;
        elseif y <x && y >= (-x)
            warpedPoints = warpingMatrix2 * tempXY;
        elseif y <x && y < (-x)
            warpedPoints = warpingMatrix3 * tempXY;
        else
            warpedPoints = warpingMatrix4 * tempXY;
        end
        centerMatrix(i, j, 1) = warpedPoints(1);
        centerMatrix(i, j, 2) = warpedPoints(2);
    end
end

for i = 1:height
    for j = 1:width
        x = centerMatrix(i, j, 1);
        y = centerMatrix(i, j, 2);
        originalPoints = [x; y; 1];
        tempXY = zeros(6,1);
        tempXY(1) = 1; tempXY(2) = x; tempXY(3) = y;
        tempXY(4) = x*x; tempXY(5) = x*y;tempXY(6) = y*y;
        warpedPoints = transferMatrix \ originalPoints;
        centerMatrix(i, j, 1) = warpedPoints(1);
        centerMatrix(i, j, 2) = warpedPoints(2);
    end
end

reversedDog = zeros(height,width, bytesPerPixel);
reversedCat = zeros(height,width, bytesPerPixel);

for i = 1:height
    for j = 1:width
        for channel = 1: bytesPerPixel
            if round(centerMatrix(i, j, 1))>0 && round(centerMatrix(i,j,2))>0 && round(centerMatrix(i, j, 1))<=height &&round(centerMatrix(i,j,2))<=width
                reversedDog(i, j, channel) = warpedDog(round(centerMatrix(i, j, 1)), round(centerMatrix(i,j,2)), channel);
                reversedCat(i, j, channel) = warpedCat(round(centerMatrix(i, j, 1)), round(centerMatrix(i,j,2)), channel);
            end
        end
    end
end 

figure(3);
imshow(rescale(reversedDog));
figure(4);
imshow(rescale(reversedCat));

writeraw(reversedDog, "reversedDog.raw");
writeraw(reversedCat, "reversedCat.raw");