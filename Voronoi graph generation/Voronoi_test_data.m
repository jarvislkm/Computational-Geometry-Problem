%% This is generate the data for voronoi graph generation
clear all;
sitenum = 1000;
min_v = -1e5;
max_v = 1e5;

x = randi([min_v,max_v],sitenum,1)';
y = randi([min_v,max_v],sitenum,1)';
y(1,1:10) = max(y');
fileID = fopen("C:\Users\Kaiming's Jam\source\repos\Voronoi_graph\Voronoi_graph\data.txt",'w');
fprintf(fileID,'%i\r\n',sitenum);
A = [x;y];
fprintf(fileID,'%i %i\r\n',A);

num = 2000;
x = randi([min_v,max_v],num,1)';
y = randi([min_v,max_v],num,1)';
fprintf(fileID,'%i\r\n',num);
A = [x;y];
fprintf(fileID,'%i %i\r\n',A);

fclose(fileID);
%% 
fileID = fopen("C:\Users\Kaiming's Jam\source\repos\Voronoi_graph\Voronoi_graph\data.txt",'r');
formatSpec = '%f';
A = fscanf(fileID,formatSpec);
min_v = -1e4;
max_v = 1e4;
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
fileID2 = fopen("C:\Users\Kaiming's Jam\source\repos\Voronoi_graph\Voronoi_graph\result.txt",'r');
B = fscanf(fileID2,formatSpec);

vx = [];
vy = [];

for k = 1:4:size(B)
   vx = [vx, B(k),B(k+2)];
   vy = [vy, B(k+1),B(k+3)];
   plot([B(k),B(k+2)],[B(k+1),B(k+3)],'r-');
   hold on;
end
axis([min_v-10 max_v+10 min_v-10 max_v+10]);
%% 

hold on;
fileID2 = fopen("C:\Users\Kaiming's Jam\source\repos\Voronoi_graph\Voronoi_graph\result_test.txt",'r');
B = fscanf(fileID2,formatSpec);

vx = [];
vy = [];

for k = 1:4:size(B)
   vx = [vx, B(k),B(k+2)];
   vy = [vy, B(k+1),B(k+3)];
   plot([B(k),B(k+2)],[B(k+1),B(k+3)],'k-');
   hold on;
end
axis([min_v-10 max_v+10 min_v-10 max_v+10]);
