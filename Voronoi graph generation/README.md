# Voronoi graph generation
Given m points in graph, find the closest one from other n points.  

Method:  
* First generate the Voronoi graph of n point stored in DCEL, then use DCEL to determine if point is in cell.

input data:  
* first line  : n  
* next n line : position of point(x,y)  
* next line   : m  
* next m line : position of point(x,y)  

output data:  
* m line in total: index of point(from 0 to n-1) 
