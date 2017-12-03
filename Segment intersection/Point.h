#pragma once
#include "Header.h"
#include "func.h"
#include <iostream>
using namespace std;

class point {
public:
	point() {};
	point(double xx, double yy) :x(xx), y(yy) {};
	point(const point &a) { x = a.x; y = a.y; };
	bool operator ==(point &b) { return is_zero(b.x - x) && is_zero(b.y - y); };   //cal _position (a,b) little different from (b,a)
	bool operator !=(point &b) { return !(*this == b); };
	bool operator <(point &b) {
		if (x < b.x - 1e-8) return true;
		else if (is_zero(x - b.x) && y > b.y) return true;
		else return false;
	}
	bool vert(point &b) {
		return is_zero(x - b.x);
	}
	double x;
	double y;
	friend ostream& operator<<(ostream& os, point &a) {
		//		os << " x: " << a.x << " y: " << a.y << endl;
		os << a.x << "  " << a.y << endl;
		return os;
	}
};
