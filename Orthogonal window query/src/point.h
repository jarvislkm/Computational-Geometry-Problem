#pragma once
#include<iostream>
class Point {
public:
	Point(long xx, long yy) :x(xx), y(yy) { ref_left = 0; ref_right = 0; id = -1; };
	Point(long xx, long yy, long id_i) :x(xx), y(yy), id(id_i) { ref_left = 0; ref_right = 0; };
	Point(const Point& pp) :x(pp.x), y(pp.y), ref_left(pp.ref_left), ref_right(pp.ref_right), id(pp.id) {};
	Point() { ref_left = 0; ref_right = 0; id = -1; };
	long x;
	long y;
	long ref_left;
	long ref_right;
	long id;
};