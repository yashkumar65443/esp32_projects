function [result normalizetrafficarea]=videodetection(a,b,Thre,Area)
result=0;
trafficarea=0;
a=rgb2gray(a);
b=rgb2gray(b);
a=imresize(a,[300 600]);
b=imresize(b,[300 600]);
 Ip = imsubtract(a,b);
 
 Imbin=Ip<Thre;
 Imbin=imcomplement(Imbin);
 Imbin = medfilt2(Imbin,[5,5]);
 [L num]=bwlabel(Imbin);
 % imshow(L);

 STATS = regionprops(L,'all');
%  figure;
%  imshow(Imbin);
 
 


%         K6 = medfilt2(K,[5,5]);
%        [L num]=bwlabel(K6);
%        STATS = regionprops(L,'all');
removed=0;
result=0;

for i=1:num
    dd=STATS(i).Area;
    trafficarea=trafficarea+dd;
    if dd > Area
        result=1;
    end

    if dd < 100
        L(L==i)=0;
        removed = removed + 1;
        num=num-1;
    else

    end
    
    
end
normalizetrafficarea=((trafficarea -0)/(210129)) * 100

  disp('exit');

