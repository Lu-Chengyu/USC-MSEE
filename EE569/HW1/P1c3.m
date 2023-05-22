% Name: Chengyu Lu
% USC ID Number: 5157638886
% USC Email: luchengy@usc.edu
% Submission Date: 01/29/2023
clear
Height = 422;
Width = 750;
BytesPerPixel = 3;
Imagedata = readraw("City.raw", Height, Width,BytesPerPixel);
YUV_Image = zeros(Height, Width, BytesPerPixel);
Result = zeros(Height, Width, BytesPerPixel);

for i = 1:Height
    for j = 1:Width
        YUV_Image(i, j, 1) = 0.257*Imagedata(i, j, 1) + 0.504*Imagedata(i, j, 2) + 0.098*Imagedata(i, j, 3) +16;
        YUV_Image(i, j, 2) = -0.148*Imagedata(i, j, 1) - 0.291*Imagedata(i, j, 2) + 0.439*Imagedata(i, j, 3) +128;
        YUV_Image(i, j, 3) = 0.439*Imagedata(i, j, 1) - 0.368*Imagedata(i, j, 2) - 0.071*Imagedata(i, j, 3) +128;
    end
end

ImageData_Norm = (YUV_Image(:,:,1) - 16)/(235-15) ;
YUV_Image(:,:,1) = floor(adapthisteq(ImageData_Norm, 'clipLimit',0.001, "NumTiles", [2,5])*(235-15) + 16);

for i = 1:Height
    for j = 1:Width
        Result(i, j, 1) = 1.164*(YUV_Image(i,j,1)-16) + 1.596*(YUV_Image(i,j,3)-128);
        Result(i, j, 2) = 1.164*(YUV_Image(i,j,1)-16) - 0.813*(YUV_Image(i,j,3)-128) - 0.391*(YUV_Image(i,j,2)-128);
        Result(i, j, 3) = 1.164*(YUV_Image(i,j,1)-16) + 2.018*(YUV_Image(i,j,2)-128);
    end
end

writeraw(Result, "City0.001_2_5.raw");
