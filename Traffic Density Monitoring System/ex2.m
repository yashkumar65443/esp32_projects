clc;
clear;
close all;
background=imread('background.bmp');
a=imread('mask.bmp');
b=rgb2gray(a);
c=b>253;
figure;imshow(c);
[Label Num]=bwlabel(c);
prop=regionprops(Label,'BoundingBox');
for i=1:Num
    filename=strcat(num2str(i),'.bmp');
    Bbox=prop(i).BoundingBox;
    Bbox=round(Bbox);
    data=imcrop(background,Bbox);
    imshow(Label ==i);
    imwrite(data, filename);   
end
    