#pragma once
#include "Point.h"
#include <cmath>

class segment {
public:
	segment() {};
	segment(point aa, point bb, type_of_line _type = type_of_line::seg) :left_end(aa), right_end(bb), type(_type) { r = (bb.x - aa.x) / 2; center = (bb.x + aa.x) / 2; };
	segment(const segment &_seg) :left_end(_seg.left_end), right_end(_seg.right_end), type(_seg.type), temp(_seg.temp), r(_seg.r), center(_seg.center) {};
	bool operator ==(segment &_seg) { return (_seg.left_end == left_end) && (_seg.right_end == right_end) && (_seg.type == type); };
	bool operator !=(segment &_seg) { return !(*this == _seg); };
	double get_temp() const { return temp; }
	double at(double position) {
		if (type == circle_upper || type == circle_lower) {
			double dx = (center - position);
			if (type == circle_upper) {
				if (dx <= r && -r <= dx) {
                                        temp = left_end.y + std::sqrt(r*r - dx*dx);
					return temp;
				}
				else return temp = -1e12;
			}
			else {
				if (dx <= r && -r <= dx) {
                                        temp = left_end.y - std::sqrt(r*r - dx*dx);
					return temp;
				}
				else return temp = 1e12;
			}
		}
		else temp = right_end.y - (double)((right_end.y - left_end.y)*(right_end.x - position)) / (right_end.x - left_end.x); return temp;
	}
	point left_end;
	point right_end;
	double r;
	double center;
	type_of_line type;
	double temp;
};

