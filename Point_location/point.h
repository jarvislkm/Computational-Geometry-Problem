#pragma once
class point
{
public:
	point(long int x1, double y1) :x(x1), y(y1) {};
	point(point& p) :x(p.x), y(p.y) {};
	point() { x = 0; y = 0; };
	bool operator <(point& s) {
		return x < s.x ? true : (x == s.x ? y < s.y : false);
	}
	bool operator >(point& s) {
		return x > s.x ? true : (x == s.x ? y > s.y : false);
	}
	bool operator ==(point& s) {
		return (x == s.x && y == s.y);
	}
	long int x;
	double y;
};

