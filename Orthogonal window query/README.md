# Orthogonal Windowing Query
Given n axis-paralleled segments in 2D plane and m orthogonal rectangular windows, print the number of segments exists in or crossed by window.  

Method: interval and range tree.

input data:  
* first line  : n  
* next n line : segments position(x1,y1,x2,y2)  
* next line   : m
* next m line : top-left and bottom-right corner of window (x1, y1, x2, y2)

output data:  
* m line: number of segments in query window.
