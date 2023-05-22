% Name: Chengyu Lu
% USC ID Number: 5157638886
% USC Email: luchengy@usc.edu
% Submission Date: 01/29/2023
function [ img ] = readraw( filename, height, width,BytesPerPixel )
%READRAW Write RAW format image file.
%   filename: file name of the file to read
disp(['Read image '  filename ' ...']);
% Get file ID
fr = fopen(filename,'rb');
% Check if file exists
if (fr == -1)
    error('Can not open output image file. Press CTRL-C to exit \n');
    pause
end
temp=fread(fr,inf, 'uchar');


img=zeros(height,width,BytesPerPixel);
    for i=1:height
        for j=1:width
            for k=1:BytesPerPixel
                img(i,j,k)=temp(((i-1)*width+j-1)*BytesPerPixel+k);
            end
        end
    end

    
fclose(fr);

end
