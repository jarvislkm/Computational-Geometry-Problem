%% This is generate the data for Delaunay triangle generation
clear all;
sitenum = 30;
min = -1e6;
max = 1e6;

x = randi([min,max],sitenum,1)';
y = randi([min,max],sitenum,1)';
fileID = fopen("data.txt",'w');
fprintf(fileID,'%i\r\n',sitenum);
A = [x;y];
fprintf(fileID,'%i %i\r\n',A);

% num = 1000;
% x = randi([min,max],num,1)';
% y = randi([min,max],num,1)';
% fprintf(fileID,'%i\r\n',num);
% A = [x;y];
% fprintf(fileID,'%i %i\r\n',A);

fclose(fileID);
%% 
fileID = fopen("data.txt",'r');
formatSpec = '%f';
A = fscanf(fileID,formatSpec);
min = -1e5;
max = 1e5;
px = [];
py = [];
for i=2:2:2*sitenum
    px = [px,A(i)/10];
    py = [py,A(i+1)/10];
end
figure
plot(px,py,'bo');
daspect([1 1 1])
hold on;
%% 
hold on;
fileID2 = fopen("result.txt",'r');
B = fscanf(fileID2,formatSpec);

vx = [];
vy = [];

for k = 1:4:size(B)
   vx = [vx, B(k),B(k+2)];
   vy = [vy, B(k+1),B(k+3)];
   plot([B(k),B(k+2)],[B(k+1),B(k+3)],'r-');
   hold on;
end
axis([min-10 max+10 min-10 max+10]);
