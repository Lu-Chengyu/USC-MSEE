% Name: Chengyu Lu
% USC ID Number: 5157638886
% USC Email: luchengy@usc.edu
% Submission Date: 01/29/2023
function count = writeraw(G, filename)
%writeraw - write RAW format image file 
% Usage :	writeraw(G, filename) or writeraw(G, filename, true)
% G:		input image matrix
% filename: file name of the file to write to disk
% gray:     true for gray scale img, false for RGB img. (default true)
% count:	return value, the elements written to file

disp([' Write image data to '  filename ' ...']);

% Get file ID
fid = fopen(filename,'wb');

% Check if file exists
if (fid == -1)
    error('Can not open output image file. Press CTRL-C to exit \n');
    pause
end

    [height,Width,BytesPerPixel]=size(G);
    temp=zeros(1,height*Width*BytesPerPixel);
for k = 1:BytesPerPixel
    temp(k:BytesPerPixel:height*Width*BytesPerPixel)=reshape(G(:,:,k)',[],1);
end
    %temp(1:3:height*Width*3)=reshape(G(:,:,1)',[],1);
    %temp(2:3:height*Width*3)=reshape(G(:,:,2)',[],1);
    %temp(3:3:height*Width*3)=reshape(G(:,:,3)',[],1);

% Write and close file
count = fwrite(fid,temp, 'uchar');
fclose(fid);

end %function
                            
