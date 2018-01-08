#pragma once
#include "point.h"
#include "func.h"
#include "segment.h"
#include <vector>
class trapezoid {
public:
	trapezoid(point l, point r, segment* up, segment* low) {left = l; right = r; upper = up; lower = low;};
	trapezoid(trapezoid& t) {
		left = t.left;
		right = t.right;
		upper = t.upper;
		lower = t.lower;
	};
	//bool in_trap(point p) {
	//	if (p > left && p < right && to_left(*lower, p)>0 && to_left(*upper, p)<=0) { return true; }
	//	else return false;
	//};
	segment* upper;
	segment* lower;
	point left;
	point right;
};

