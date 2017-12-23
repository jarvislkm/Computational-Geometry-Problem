#pragma once
class point
{
public:
	point(double x1, double y1) :x(x1), y(y1) {};
	point() { x = 0; y = 0; };
	bool operator <(point& s) {
		return y < s.y ? true : (y == s.y ? x < s.x : false);
	}
	double x;
	double y;
};

