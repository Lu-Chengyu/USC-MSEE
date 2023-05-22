% Name: Chengyu Lu
% USC ID Number: 5157638886
% USC Email: luchengy@usc.edu
% Submission Date: 03/29/2023
clear;
close all;
clc;

height = 450;
width = 600;
bytesPerPixel = 1;

colors = {
    [107 143 159]; [114 99 107]; [175 128 74]; [167 57 32]; [144 147 104]; [157 189 204]
    };

mosaic = readraw("Mosaic.raw", height, width, bytesPerPixel, true);

% for i=1:height
%     for j=1:width
%         mosaic(i,j) = mosaic(i,j) / max(max(mosaic));
%     end
% end

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

paddingPicture = padarray(mosaic,[2,2], "replicate","both");
filteredImages = {1,25};
for num = 1:25
    filter = lawFilters{num};
    result = zeros(height, width);
    for i = 3:height+2
        for j = 3:width+2
            for fr = -2:2
                for fc = -2:2
                    result(i-2,j-2) = result(i-2,j-2)+paddingPicture(i+fr,j+fc)*filter(fr+3,fc+3);
                end
            end
            result(i-2,j-2) = result(i-2,j-2)*result(i-2,j-2);
        end
    end
    filteredImages{num} = result;
end

windowSizes = [7 11 15 19 23 27 31 35 39];
figure(1);
for i = 1:size(windowSizes,2)
    energy = WindowEnergy(filteredImages, windowSizes(i));
    for j = 1:height
        for k = 1:width
            for l = 2:size(energy,3)
                energy(j,k,l) = energy(j,k,l)/energy(j,k,1);
            end
        end
    end
    energy(:,:,1)=[];
    segmentation = kmeansSegmentation(energy, colors);
    subplot(3,3,i);
    imshow(rescale(segmentation));
    title("Window Size: "+windowSizes(i));
end

function E = WindowEnergy(ImageSet, windowSize)
num = size(ImageSet, 2);
paddingSize = floor(windowSize/2);
[height, width] = size(ImageSet{1});
E = zeros(height, width, num);
for index = 1:num
    paddedImage = padarray(ImageSet{index}, [paddingSize, paddingSize], "replicate", "both");
    energyAverageImage = zeros(height, width);
    for i = paddingSize+1:height+paddingSize
        for j = paddingSize+1:width+paddingSize
            for wr = 1:windowSize
                for wc = 1:windowSize
                    energyAverageImage(i-paddingSize,j-paddingSize) = energyAverageImage(i-paddingSize,j-paddingSize)+paddedImage(i+wr-1-paddingSize,j+wc-1-paddingSize);
                end
            end
            energyAverageImage(i-paddingSize,j-paddingSize) = energyAverageImage(i-paddingSize,j-paddingSize) / (windowSize*windowSize);
        end
    end
    E(:,:,index) = energyAverageImage;
end
end

function output = kmeansSegmentation(input, colors)
[height, width, bytesPerPixel] = size(input);
energy = input;
classfiedData = zeros(height*width, bytesPerPixel);
for i= 1:height
    for j = 1:width
        classfiedData(i*width-width+j, :) = energy(i, j, :);
    end
end
kmeansResult = kmeans(classfiedData, 6,'MaxIter',200);
segmentation = zeros(height,width,3);
for i= 1:height
    for j = 1:width
        segmentation(i, j, :) = colors{kmeansResult(i*width-width+j)};
    end
end
output = segmentation;
end
