% Name: Chengyu Lu
% USC ID Number: 5157638886
% USC Email: luchengy@usc.edu
% Submission Date: 03/29/2023
clear;
close all;
clc;

addpath(genpath('./LiFF-master/'))

%% Part (b)

hight = 400;
width = 600;
bytesPerPixel = 3;

polar_bear_1 = readraw("polar_bear_1.raw", hight, width, bytesPerPixel,true);
polar_bear_2 = readraw("polar_bear_2.raw", hight, width, bytesPerPixel,true);
polar_bear_3 = readraw("polar_bear_3.raw", hight, width, bytesPerPixel,true);
brown_bear_1 = readraw("brown_bear_1.raw", hight, width, bytesPerPixel,true);
Bear = readraw("Bear.raw", hight, width, bytesPerPixel,true);

polar_bear_1_gray = single(rgb2gray(rescale(polar_bear_1)));
[polar_bear_1_f,polar_bear_1_d] = vl_sift(polar_bear_1_gray);

polar_bear_2_gray = single(rgb2gray(rescale(polar_bear_2)));
[polar_bear_2_f,polar_bear_2_d] = vl_sift(polar_bear_2_gray);

polar_bear_3_gray = single(rgb2gray(rescale(polar_bear_3)));
[polar_bear_3_f,polar_bear_3_d] = vl_sift(polar_bear_3_gray);

brown_bear_1_gray = single(rgb2gray(rescale(brown_bear_1)));
[brown_bear_1_f,brown_bear_1_d] = vl_sift(brown_bear_1_gray);

Bear_gray = single(rgb2gray(rescale(Bear)));
[Bear_f,Bear_d] = vl_sift(Bear_gray);

figure("Name","key points of the polar_bear_1 and polar_bear_3");
subplot(1,2,1);
hold on
imshow(rescale(polar_bear_3));
perm = randperm(size(polar_bear_3_f,2));
sel = perm(1:50);
h1 = vl_plotframe(polar_bear_3_f(:, sel));
h2 = vl_plotframe(polar_bear_3_f(:, sel));
set(h1,'color','k','linewidth',3);
set(h2,'color','y','linewidth',2);
hold off

subplot(1,2,2);
hold on
imshow(rescale(polar_bear_1));
h3 = vl_plotframe(polar_bear_1_f(:, sel));
h4 = vl_plotframe(polar_bear_1_f(:, sel));
set(h3,'color','k','linewidth',3);
set(h4,'color','y','linewidth',2);
hold off

% polar_bear_1 and polar_bear_3

largestF = zeros(4,1);
indexF = 0;
for i = 1:size(polar_bear_1_f,2)
    if polar_bear_1_f(3,i) > largestF(3)
        largestF = polar_bear_1_f(:,i);
        indexF = i;
    end
end

minDist = 100000;
matchedIndex = 0;
for i = 1:size(polar_bear_3_d,2)
    temp = pdist2(double(transpose(polar_bear_1_d(:,indexF))), double(transpose(polar_bear_3_d(:,i))),"euclidean");
    if temp<minDist
        minDist = temp;
        matchedIndex = i;
    end
end

figure("Name","largest key point of the polar_bear_1 and polar_bear_3")
subplot(1,2,1);
hold on
imshow(rescale(polar_bear_1));
vl_plotframe(largestF);
hold off

subplot(1,2,2);
hold on
imshow(rescale(polar_bear_3));
vl_plotframe(polar_bear_3_f(:,matchedIndex));
hold off


% brown_bear_1 and polar_bear_3

largestF = zeros(4,1);
indexF = 0;
for i = 1:size(brown_bear_1_f,2)
    if brown_bear_1_f(3,i) > largestF(3)
        largestF = brown_bear_1_f(:,i);
        indexF = i;
    end
end

minDist = 100000;
matchedIndex = 0;
for i = 1:size(polar_bear_3_d,2)
    temp = pdist2(double(transpose(brown_bear_1_d(:,indexF))), double(transpose(polar_bear_3_d(:,i))),"euclidean");
    if temp<minDist
        minDist = temp;
        matchedIndex = i;
    end
end

figure("Name","largest key point of the brown_bear_1 and polar_bear_3")
subplot(1,2,1);
hold on
imshow(rescale(brown_bear_1));
vl_plotframe(largestF);
hold off

subplot(1,2,2);
hold on
imshow(rescale(polar_bear_3));
vl_plotframe(polar_bear_3_f(:,matchedIndex));
hold off

% polar_bear_1 and polar_bear_2

largestF = zeros(4,1);
indexF = 0;
for i = 1:size(polar_bear_1_f,2)
    if polar_bear_1_f(3,i) > largestF(3)
        largestF = polar_bear_1_f(:,i);
        indexF = i;
    end
end

minDist = 100000;
matchedIndex = 0;
for i = 1:size(polar_bear_2_d,2)
    temp = pdist2(double(transpose(polar_bear_1_d(:,indexF))), double(transpose(polar_bear_2_d(:,i))),"euclidean");
    if temp<minDist
        minDist = temp;
        matchedIndex = i;
    end
end

figure("Name","largest key point of the polar_bear_1 and polar_bear_2")
subplot(1,2,1);
hold on
imshow(rescale(polar_bear_1));
vl_plotframe(largestF);
hold off

subplot(1,2,2);
hold on
imshow(rescale(polar_bear_2));
vl_plotframe(polar_bear_2_f(:,matchedIndex));
hold off

% polar_bear_1 and brown_bear_1

largestF = zeros(4,1);
indexF = 0;
for i = 1:size(polar_bear_1_f,2)
    if polar_bear_1_f(3,i) > largestF(3)
        largestF = polar_bear_1_f(:,i);
        indexF = i;
    end
end

minDist = 100000;
matchedIndex = 0;
for i = 1:size(brown_bear_1_d,2)
    temp = pdist2(double(transpose(polar_bear_1_d(:,indexF))), double(transpose(brown_bear_1_d(:,i))),"euclidean");
    if temp<minDist
        minDist = temp;
        matchedIndex = i;
    end
end

figure("Name","largest key point of the polar_bear_1 and brown_bear_1")
subplot(1,2,1);
hold on
imshow(rescale(polar_bear_1));
vl_plotframe(largestF);
hold off

subplot(1,2,2);
hold on
imshow(rescale(brown_bear_1));
vl_plotframe(brown_bear_1_f(:,matchedIndex));
hold off



%% Part (c)
rmpath("LiFF-master\lib\vlfeat-0.9.21\toolbox\noprefix")

trainData = {polar_bear_1_d, polar_bear_2_d, brown_bear_1_d, polar_bear_3_d};
reducedTrainData = zeros(size(polar_bear_1_d,2)+size(polar_bear_2_d,2)+size(brown_bear_1_d,2)+size(polar_bear_3_d,2),20);
loc = 1;
for i = 1:4
    tempData = transpose(trainData{i});
    PCAcoeff = pca(double(tempData), "NumComponents",20);
    reducedData = double(tempData)*PCAcoeff;
    reducedTrainData(loc:loc+size(reducedData,1)-1,:)=reducedData(:,:);
    loc = loc + size(reducedData,1);
end
[ClusterData,C] = kmeans(reducedTrainData,8,'MaxIter',200);
titleName = ["polar bear 1", "polar bear 2", "brown bear 1", "polar bear 3"];
loc = 1;
BoW = {};
for i = 1:4
    tempClusterData = ClusterData(loc:loc+size(trainData{i},2)-1,:);
    loc = loc + size(trainData{i},2);
    subplot(1,4,i);
    histogram(tempClusterData);
    title(titleName{i});
    BoW{i} = tempClusterData;
end

BeartempData = transpose(Bear_d);
BearPCAcoeff = pca(double(BeartempData), "NumComponents",20);
BearreducedData = double(BeartempData)*BearPCAcoeff;
BearClusterData = zeros(size(Bear_d, 2),1);
for i = 1:size(BearreducedData,1)
    lcoation = 1;
    distance = 9999999999999999999 ;
    for j = 1:8
        temp = 0;
        for k = 1:20
            temp = temp + (BearreducedData(i,k)-C(j,k))*(BearreducedData(i,k)-C(j,k));
        end
        if temp < distance
            distance = temp;
            location = j;
        end
    end
    BearClusterData(i,1) = location;
end
figure;
histogram(BearClusterData);
title("Bear");
BoW{5} = BearClusterData;

polar_bear_1_hist = [];
for i = 1:8
    polar_bear_1_hist(i) = length(find(BoW{1} == i));
end
brown_bear_1_hist = [];
for i = 1:8
    brown_bear_1_hist(i) = length(find(BoW{3} == i));
end
Bear_hist = [];
for i = 1:8
    Bear_hist(i) = length(find(BoW{5} == i));
end

uppB = 0;
downpB = 0;
upbB = 0;
downbB = 0;

for i = 1:8
    uppB = uppB+ min([polar_bear_1_hist(i), Bear_hist(i)]);
    downpB = downpB + max([polar_bear_1_hist(i), Bear_hist(i)]);
    upbB = upbB+ min([brown_bear_1_hist(i), Bear_hist(i)]);
    downbB = downbB + max([brown_bear_1_hist(i), Bear_hist(i)]);
end

Similarity_polar_bear_1_Bear = uppB/downpB;
disp("Similarity between polar_bear_1 and Bear is: "+ Similarity_polar_bear_1_Bear);
Similarity_brown_bear_1_Bear = upbB/downbB;
disp("Similarity between brown_bear_1 and Bear is: "+ Similarity_brown_bear_1_Bear);
