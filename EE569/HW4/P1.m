% Name: Chengyu Lu
% USC ID Number: 5157638886
% USC Email: luchengy@usc.edu
% Submission Date: 03/29/2023

clear;
close all;
clc;

height = 128;
width = 128;
bytesPerPixel = 1;

filterBank = cell(1,5);
filterBank{1} = [1;4;6;4;1];
filterBank{2} = [-1;-2;0;2;1];
filterBank{3} = [-1;0;2;0;-1];
filterBank{4} = [-1;2;0;-2;1];
filterBank{5} = [1;-4;6;-4;1];

lawFilters = cell(1,25);

for i = 1:5
    for j = 1:5
        lawFilters{i*5-5+j} = filterBank{i}*transpose(filterBank{j});
    end
end

trainingData = cell(4,9);
for i = 1:9
    trainingData{1,i} = readraw("./train/brick_"+int2str(i)+".raw", height,width, bytesPerPixel,false);
    trainingData{2,i} = readraw("./train/grass_"+int2str(i)+".raw", height,width, bytesPerPixel,false);
    trainingData{3,i} = readraw("./train/rice"+int2str(i)+".raw", height,width, bytesPerPixel,false);
    trainingData{4,i} = readraw("./train/stones_"+int2str(i)+".raw", height,width, bytesPerPixel,false);
end

energy = cell(4,9);

for i = 1:4
    for j = 1:9
        temp = trainingData{i,j};
        paddedImage = padarray(temp,[2,2], "replicate","both");
        e = zeros(1,25);
        for fi = 1:25
            filter = lawFilters{fi};
            result = zeros(height, width);
            for r = 3:height+2
                for c = 3:width+2
                    for fr = -2:2
                        for fc = -2:2
                            result(r-2,c-2) = result(r-2,c-2)+paddedImage(r+fr,c+fc)*filter(fr+3,fc+3);
                        end
                    end
                    result(r-2,c-2) = result(r-2,c-2)*result(r-2,c-2)/(height*width);
                end
            end
            nergyFeature(fi) = mean(mean(result));
        end
        energy{i, j} = nergyFeature;
    end
end

yid = zeros(4,25);
ydd = zeros(1,25);
inter = zeros(1,25);
intra = zeros(1,25);
dp = zeros(1,25);

for k = 1:25
    for i = 1:4
        for j = 1:9
            yid(i,k) = yid(i,k) + energy{i,j}(1,k);
        end
        ydd(1,k) = ydd(1,k) + yid(i,k);
        yid(i,k) = yid(i,k)/9;
    end
    ydd(1,k) = ydd(1,k)/(4*9);
end

for k = 1:25
    for i = 1:4
        for j = 1:9
            intra(1,k) = intra(1,k) + (energy{i,j}(1,k)-yid(i,k))*(energy{i,j}(1,k)-yid(i,k));
        end
        inter(1,k) = inter(1,k) + (yid(i,k) - ydd(1,k)) * (yid(i,k) - ydd(1,k));
    end
    dp(1,k) = inter(1,k)/intra(1,k);
end
[~, dpOrder] = sort(dp);

YTrain = zeros(36,1);
XTrain_test = zeros(36,25);

for i = 1:4
    for j = 1:9
        XTrain_test(i*9-9+j, : ) = energy{i,j}(1,:);
        YTrain(i*9-9+j, 1 ) = i;
    end
end
dpFeature = XTrain_test;
%XTrain = XTrain_test(:, 2:25);
dft_loss = get_all_loss(XTrain_test, double(YTrain), 4);
figure(1);
plot(1:25, dft_loss);
hold;
plot(1:25, sort(dft_loss));

[~, Vector_result_position] = sort(dft_loss); % 7,8,2
trainDFTFeatures = zeros(36,3);
for i = 1:36
    for j = 1:3
        trainDFTFeatures(i,j) = XTrain_test(i,Vector_result_position(1,j));
    end
end

PCAdata = XTrain_test(:, 2:25);
[PCAcoeff,score,latent,tsquared,explained,mu] = pca(PCAdata,'NumComponents',3);%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%PCAdata XTrain_test

figure(2);
hold on
scatter3(score(1:9,1),score(1:9,2),score(1:9,3),"blue");
scatter3(score(10:18,1),score(10:18,2),score(10:18,3),"black");
scatter3(score(19:27,1),score(19:27,2),score(19:27,3),"green");
scatter3(score(28:36,1),score(28:36,2),score(28:36,3),"red");
legend("Brick", "Grass", "Rice", "Stones")
title("Training samples features visualization")
grid on
hold off

% Predict the test labels

TestPics = cell(1,12);
for i = 1:12
    trainingData{i} = readraw("./test/"+int2str(i)+".raw", height,width, bytesPerPixel,false);
end

testEnergyFeatures = {};
for i = 1:12
    temp = trainingData{i};
    paddedImage = zeros(height+4, width+4);
    paddedImage(3:height+2, 3:width+2) = temp;
    nergyFeature = zeros(1,25);
    for fi = 1:25
        filter = lawFilters{fi};
        result = zeros(height, width);
        for r = 3:height+2
            for c = 3:width+2
                for fr = -2:2
                    for fc = -2:2
                        result(r-2,c-2) = result(r-2,c-2)+paddedImage(r+fr,c+fc)*filter(fr+3,fc+3);
                    end
                end
                result(r-2,c-2) = result(r-2,c-2)*result(r-2,c-2)/(height*width);
            end
        end
        nergyFeature(fi) = mean(mean(result));
    end
    testEnergyFeatures{i} = nergyFeature;
end

testDPdata = zeros(12,25);
testPCAData = zeros(12,25);
testDFTFeatures = zeros(12,3);
for i = 1:12
    testPCAData(i, :) = testEnergyFeatures{i}(1,:);
    testDPdata(i, :) = testEnergyFeatures{i}(1,:);
end

for i = 1:12
    for j = 1:3
        testDFTFeatures(i,j) = testPCAData(i,Vector_result_position(1,j));
    end
end

testPCAData = testPCAData(:, 2:25);
testPCAResult = (testPCAData-mu)*PCAcoeff;
%testPCAres = testPCAdata*PCAcoeff;%%%%%%%%%%%%%%%%%%%%%%%%%

distDP = zeros(12,36);
distDFT = zeros(12,36);
distPCA = zeros(12,36);
for i = 1:12
    for j = 1:36
        distDP(i,j) = sqrt((testDPdata(i,:)-dpFeature(j,:)) * cov(dpFeature(j,:))^-1 * (testDPdata(i,:)-dpFeature(j,:))');
        distDFT(i,j) = sqrt((testDFTFeatures(i,:)-trainDFTFeatures(j,:)) * cov(trainDFTFeatures)^-1 * (testDFTFeatures(i,:)-trainDFTFeatures(j,:))');
        %mDistDFT(i,j) = sqrt((testDFTFeatures(i,:)-DFTTrainFeatures(j,:)) * (testDFTFeatures(i,:)-DFTTrainFeatures(j,:))');
        distPCA(i,j) = sqrt((testPCAResult(i,:)-score(j,:)) * cov(score(j,:))^-1 * (testPCAResult(i,:)-score(j,:))');
    end
end
rankDP = zeros(12,4);
rankDFT = zeros(12,4);
rankPCA = zeros(12,4);
for i = 1:12
    rank0 = zeros(1,4);
    rank1 = zeros(1,4);
    rank2 = zeros(1,4);
    for j = 1:4
        for k = 1:9
            rank0(1,j) = rank0(1,j) + distDP(i,j*9+k-9);
            rank1(1,j) = rank1(1,j) + distDFT(i,j*9+k-9);
            rank2(1,j) = rank2(1,j) + distPCA(i,j*9+k-9);
        end
    end
    [~, rankDP(i,:)] = sort(rank0);
    [~, rankDFT(i,:)] = sort(rank1);
    [~, rankPCA(i,:)] = sort(rank2);
end
% disp("rankDP:");
% disp(rankDP);
% disp("rankDFT:");
% disp(rankDFT);
% disp("rankPCA:");
% disp(rankPCA);

testLabels = transpose([2 4 4 1 3 2 1 3 3 1 4 2]);
[ClusterData25D,C25D] = kmeans(PCAdata,4);
[ClusterDataDFT,CDFT] = kmeans(trainDFTFeatures,4);
[ClusterDataPCA,CPCA] = kmeans(score,4);
location = ones(3,12);
for i = 1:12
    temp = 999999999999;
    for j = 1:4
        distance = 0;
        for k =1:24
            distance = distance + (testPCAData(i,k)-C25D(j,k))*(testPCAData(i,k)-C25D(j,k));
        end
        if distance<temp
            temp = distance;
            location(1,i) = j;
        end
    end   
end
for i = 1:12
    temp = 999999999999;
    for j = 1:4
        distance = 0;
        for k =1:3
            distance = distance + (testDFTFeatures(i,k)-CDFT(j,k))*(testDFTFeatures(i,k)-CDFT(j,k));
        end
        if distance<temp
            temp = distance;
            location(2,i) = j;
        end
    end   
end
for i = 1:12
    temp = 999999999999;
    for j = 1:4
        distance = 0;
        for k =1:3
            distance = distance + (testPCAResult(i,k)-CPCA(j,k))*(testPCAResult(i,k)-CPCA(j,k));
        end
        if distance<temp
            temp = distance;
            location(3,i) = j;
        end
    end   
end
% k25 = kmeans(testPCAData,4);
% k3DFT = kmeans(testDFTFeatures,4);
% k3PCA = kmeans(testPCAResult,4);

trainingData = score;
trainingLabel = ones(36,1);
trainingLabel(10:18) = 2;
trainingLabel(19:27) = 3;
trainingLabel(28:36) = 4;
testingData = testPCAResult;
testingLabel = testLabels;

SVM = fitcecoc(trainingData, trainingLabel);
SVMResult = predict(SVM, testingData);

rightNum = 0;
for i = 1:12
    if SVMResult(i) == testingLabel(i)
        rightNum = rightNum+1;
    end
end
SVMAccuracy = rightNum/12;
% disp("SVM's accuracy of 3D PCA is "+SVMAccuracy);

%%%%%%

trainingData = trainDFTFeatures;
testingData = testDFTFeatures;
SVM = fitcecoc(trainingData, trainingLabel);
SVMResult = predict(SVM, testingData);

rightNum = 0;
for i = 1:12
    if SVMResult(i) == testingLabel(i)
        rightNum = rightNum+1;
    end
end
SVMAccuracy = rightNum/12;
% disp("SVM's accuracy of 3D DFT is "+SVMAccuracy);

%%%%%%%%%

trainingData = PCAdata;%%%%%%%%%%%%%%%XTrain_test
testingData = testPCAData;
SVM = fitcecoc(trainingData, trainingLabel);
SVMResult = predict(SVM, testingData);

rightNum = 0;
for i = 1:12
    if SVMResult(i) == testingLabel(i)
        rightNum = rightNum+1;
    end
end
SVMAccuracy = rightNum/12;
% disp("SVM's accuracy of 25D is "+SVMAccuracy);


function [entropy] = cal_entropy_from_y(y_array, num_cls)
prob = zeros(1,num_cls);
for c = 1:num_cls
    prob(c) = sum(y_array==c-1)./length(y_array);
end
prob = prob./sum(prob);
tmp = 0;
for i = 1:length(prob)
    if prob(i) > 0
        tmp = tmp - prob(i) * log(prob(i));
    end
end
entropy = tmp./log(num_cls);
end

function [wH] = cal_weighted_H(X, y, bound,num_cls)
if (sum(X<bound)==0 || sum(X>=bound)==0)
    wH = 1;
    return
else
    left_y = y(X<bound);
    right_y = y(X>=bound);
    left_num = length(left_y);
    right_num = length(right_y);
    left_entropy = cal_entropy_from_y(left_y, num_cls);
    right_entropy = cal_entropy_from_y(right_y,  num_cls);
    wH = left_num/(left_num + right_num) * left_entropy + right_num/(left_num + right_num) * right_entropy;
end
end

function [best_loss] = binning(x, y,B, num_class)
min_x = min(x);
max_x = max(x);
if max_x == min_x
    best_loss = 1;
    return
end
candidates = (min_x: (max_x - min_x) / B: max_x);
candidates = candidates(2:length(candidates)-1);
candidates = unique(candidates);
loss_i = zeros(1,length(candidates));

for idx=(1:length(candidates))
    loss_i(idx) = cal_weighted_H(x, y, candidates(idx), num_class);
end
best_loss = min(loss_i);
end

function [feat_loss] = get_all_loss(X, Y, num_class)
[N , D] = size(X);
feat_loss = zeros(1, D);
for k = 1:D
    x = X(:, k);
    y = Y;
    y = y(:, 1);
    feat_loss(k) = binning(x, y, 16, num_class);
end
end