min_v = -1e6;
max_v = 1e6;
line_num = 100; 
interval = (max_v-min_v)/line_num;
windownum = 1000;
segment = [];
figure
for i = min_v:interval:max_v
    num_of_line = randi([1,20]);
    if mod(num_of_line,2) ==1
        num_of_line = num_of_line + 1;
    end
    point_end = randperm(max_v-min_v,num_of_line) - max_v;
    point_end = sort(point_end);
    for j = 1:2:num_of_line
        point = [point_end(1,j+1),i,point_end(1,j),i];
        plot([point_end(1,j),point_end(1,j+1)],[i,i]);
        hold on;
        segment = [segment;point];
    end
end

fileID = fopen("C:\Users\Kaiming's Jam\source\repos\Window_query\Window_query\data.txt",'w');
fprintf(fileID,'%i %i\r\n',size(segment,1),windownum);
fprintf(fileID,'%i %i %i %i\r\n',segment');

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
window = [x1;y1;x2;y2];
fprintf(fileID,'%i %i %i %i\r\n',window);
fclose(fileID);
%% 
result_a = [];
result_b = [];
for i = 1:windownum
    type_a = 0;
    type_b = 0;
    w1x = window(1,i)-0.5;
    w1y = window(2,i)-0.5;
    w2x = window(3,i)+0.5;
    w2y = window(4,i)+0.5;
    plot([w1x,w2x;w1x,w2x;],[w1y,w1y;w2y,w2y],'r-');
    hold on;
    plot([w1x,w1x;w2x,w2x;],[w1y,w2y;w1y,w2y],'r-');
    hold on;
    for j = 1:size(segment,1)
        p1x = segment(j,1);
        p1y = segment(j,2);
        p2x = segment(j,3);
        p2y = segment(j,4);
        if(p1x>p2x) 
            c = p1x;
            p1x = p2x;
            p2x = c;
        end
        p1 = p1x>= w1x && p1x <= w2x && p1y >= w1y && p1y<= w2y;
        p2 = p2x>= w1x && p2x <= w2x && p2y >= w1y && p2y<= w2y;
        if(p1 || p2)
            type_a = type_a+1;
        else
            if(p1x<w1x && p2x>w2x && p1y>w1y && p1y<w2y)
                type_b = type_b+1;
            end
        end
    end
    result_a = [result_a,type_a];
    result_b = [result_b,type_b];
end
result = result_a + result_b;
%% 
formatSpec = '%f';
fileID2 = fopen("C:\Users\Kaiming's Jam\source\repos\Window_query\Window_query\result.txt",'r');
program_result = fscanf(fileID2,formatSpec)';
diff = abs(program_result - result);
diff_max = max(diff);