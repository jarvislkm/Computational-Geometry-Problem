#pragma once
#include "point.h"
class segment {
public:
	segment(point l, point r, long int i):lp(l), rp(r), id(i){};
	point at(long int po) {
		if (rp.x != lp.x) {
			double k =  (rp.y - lp.y) / (rp.x - lp.x);
			double y = k*(po - lp.x) + lp.y;
			point p(po, y);
			return p;
		}
		else {
			point p(po, rp.y);
			return p;
		}
	}
	long int id;
	point lp;
	point rp;
};