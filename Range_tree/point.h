#pragma once
#include<iostream>
class point {
public:
	point(long int xx, long int yy) :x(xx), y(yy) { ref_left = 0; ref_right = 0; };
	point(const point& pp) :x(pp.x), y(pp.y), ref_left(pp.ref_left), ref_right(pp.ref_right) {};
	point() { ref_left = 0; ref_right = 0; };
	long int x;
	long int y;
	long int ref_left;
	long int ref_right;
	//bool operator <(point & p) {
	//	return x < p.x ? true : (x == p.x ? y < p.y : false);
	//}
};