#include "func.h"

double to_left(point a, point b, point c) {
	double tem1 = a.x*b.y + b.x*c.y + c.x*a.y - b.y*c.x - c.y*a.x - a.y*b.x;
	return tem1;
}
double to_left(segment s, point c) {
	if (s.lp.x != s.rp.x) {
		return to_left(s.lp, s.rp, c);
	}
	else {
		if (c.y > s.rp.y) return 1;
		else return -1;
	}
}

void swap(point & a, point& b) {
	point c(b);
	b.x = a.x;
	b.y = a.y;
	a.x = c.x;
	a.y = c.y;
}