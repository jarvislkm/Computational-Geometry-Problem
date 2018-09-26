#pragma once
#include <iostream>
#include <vector>
enum type_of_point{ start, ending, regular_left, regular_right, split, merging};
class point {
public:
	point() {};
	point(double xx, double yy, int n) :x(xx), y(yy),num(n) {};
	point(const point &a) { x = a.x; y = a.y; num = a.num; type = a.type; };
	bool operator >(point& b) { return y == b.y ? x < b.x:y > b.y; }
	bool operator <(point&b) { return !((*this > b)||(*this==b)); }
	bool operator ==(point &b) { return (!(b.x - x)) && (!(b.y - y)); };   //cal _position (a,b) little different from (b,a)
	double x;
	double y;
	int num;
	type_of_point type;
	point* before;
	point* after;
	std::vector<int> connected;
	friend std::ostream& operator<<(std::ostream& os, point &a) {
		//		os << " x: " << a.x << " y: " << a.y << endl;
		os<<"num:  " <<a.num<<"  "<< a.x << "  " << a.y << std::endl;
		return os;
	}
};
