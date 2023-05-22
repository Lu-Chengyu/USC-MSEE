% Name: Chengyu Lu
% USC ID Number: 5157638886
% USC Email: luchengy@usc.edu
% Submission Date: 01/29/2023
clear
Hight = 240;
Width = 400;
BytesPerPixel = 1;
ImageData = readraw("Pepper_gray_noisy.raw", Hight, Width,BytesPerPixel);
Image_NLM = imnlmfilt(ImageData, "SearchWindowSize", 21, "ComparisonWindowSize", 5);
writeraw(Image_NLM, "Pepper_NLM21_5.raw");