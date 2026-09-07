clear;
close all;
cam2=webcam(2);
framecnt=1;
while(framecnt< 100)
inputframe=snapshot(cam2);
Rgbframe=inputframe;
a=imread('mask.bmp');
b=rgb2gray(a);
c=b>253;
% figure;imshow(c);
[Label Num]=bwlabel(c);
prop=regionprops(Label,'BoundingBox');
for i=1:Num
    filename=strcat(num2str(i),'.bmp');
    Bbox=prop(i).BoundingBox;
    Bbox=round(Bbox);
    backgroundframe=imread(filename);
    currentframe=imcrop(inputframe,Bbox);
    Area=200;
    Thre=100;
    [result normalizetrafficarea]=videodetection(backgroundframe,currentframe,Thre,Area);
    if i==1
      str1='south'
      south=normalizetrafficarea;
    elseif i ==2
           str1='west'
      west=normalizetrafficarea;
    elseif i==3
         str1='east'
      east=normalizetrafficarea;
    else
         str1='north'
      north=normalizetrafficarea;
        
    end
    
    if result==1
      Rgbframe = insertObjectAnnotation(Rgbframe, 'rectangle',Bbox,str1,'Color',{'red'});
    else
      Rgbframe = insertObjectAnnotation(Rgbframe, 'rectangle',Bbox,str1,'Color',{'cyan'});

        
    end
    
%     imshow(Label ==i);
%     imwrite(data, filename);  
framecnt=framecnt+1;
end
imshow(Rgbframe);
thingSpeakWrite(0000000,{north,south,east,west},'WriteKey','YOUR_WRITE_KEY')
disp('data written');
pause(20);

end