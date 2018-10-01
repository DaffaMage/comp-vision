mask = [0 -1 0;-1 5 -1;0 -1 0];
maskX = [0 0 0;-1 1 0;0 0 0];
maskY = [0 -1 0;0 1 0;0 0 0];
maskXY = [0 -1 0;-1 2 0;0 0 0];
scale = 5;
hpass = 0;
lpass = 0;

img = imread('imgx.jpg');
img = rgb2gray(img);
figure(1)
img = conv2(img, maskXY, 'same');
img = img/255;
img = abs(img);
img = img*scale;
imshow(img)
imwrite(img,'outputn.jpg');