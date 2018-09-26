%% This is generate the data for planar point range query
clear all;
sitenum = 1000;
windownum = 2000;

min_v = -1e5;
max_v = 1e5;

x = randi([min_v,max_v],sitenum,1)';
y = randi([min_v,max_v],sitenum,1)';
fileID = fopen("data.txt",'w');
fprintf(fileID,'%i %i\r\n',sitenum, windownum);
A = [x;y];
fprintf(fileID,'%i %i\r\n',A);

x1 = randi([min_v,max_v],windownum,1)';
y1 = randi([min_v,max_v],windownum,1)';
x2 = randi([min_v,max_v],windownum,1)';
y2 = randi([min_v,max_v],windownum,1)';
for i = 1:windownum
    if(x1(1,i)>x2(1,i))
        s = x2(1,i);
        x2(1,i) = x1(1,i);
        x1(1,i) = s;
    end
    if(y1(1,i)>y2(1,i))
        s = y2(1,i);
        y2(1,i) = y1(1,i);
        y1(1,i) = s;
    end    
end
Aa = [x1;y1;x2;y2];
fprintf(fileID,'%i %i %i %i\r\n',Aa);

fclose(fileID);
%% 

count = zeros(1,windownum);
for j = 1:sitenum
    x = A(1,j)*ones(1,windownum);
    y = A(2,j)*ones(1,windownum);
    left = x>=Aa(1,:);
    right = x<=Aa(3,:);
    bottom = y>=Aa(2,:);
    top = y<=Aa(4,:);
    result = left.*right.*bottom.*top;
    count = count+result;
end
%% 
figure
plot(A(1,:),A(2,:),'bo');
daspect([1 1 1])
hold on;
for i = 1:1
   plot([Aa(1,i) Aa(1,i)],[Aa(2,i) Aa(4,i)],'r-');
   hold on;
   plot([Aa(1,i) Aa(3,i)],[Aa(2,i) Aa(2,i)],'r-');
   hold on;   
   plot([Aa(3,i) Aa(3,i)],[Aa(2,i) Aa(4,i)],'r-');
   hold on; 
   plot([Aa(1,i) Aa(3,i)],[Aa(4,i) Aa(4,i)],'r-');
   hold on;   
end
axis([min_v-10 max_v+10 min_v-10 max_v+10]);
%% 
hold on;
formatSpec = '%f';
fileID2 = fopen("result.txt",'r');
B = fscanf(fileID2,formatSpec)';
diff = B-count;
diff_max = sum(abs(diff));
