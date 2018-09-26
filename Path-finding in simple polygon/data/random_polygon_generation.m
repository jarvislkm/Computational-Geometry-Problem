N = 300;
[x,y] = simple_polygon(N);
a1 = randi([1,N-1]);
a2 = randi([1,N-1]);
x = round(x*10000);
y = round(y*10000);
x1 = mean(x(a1:a1+1));
y1 = mean(y(a1:a1+1));
x2 = mean(x(a2:a2+1));
y2 = mean(y(a2:a2+1));

fileID = fopen("C:\Users\Kaiming's Jam\source\repos\PA_2A\PA_2A\data1.txt",'w');
fprintf(fileID,'%d %d %d %d\r\n',[x1 y1 x2 y2]);
fprintf(fileID,'%d\r\n',N);

fprintf(fileID,'%d %d\r\n',[x,y]');
fclose(fileID);