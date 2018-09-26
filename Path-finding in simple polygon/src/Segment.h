#pragma once
#include "Point.h"
class segment {
public:
	segment() {};
	segment(point aa, point bb) { if (aa > bb) { upper_end = aa; lower_end = bb; } else { upper_end = bb; lower_end = aa; } };
	segment(const segment &_seg) :upper_end(_seg.upper_end), lower_end(_seg.lower_end), temp(_seg.temp){};
	bool operator ==(segment &_seg) { return (_seg.upper_end == upper_end) && (_seg.lower_end == lower_end); };
	bool operator !=(segment &_seg) { return !(*this == _seg); };
	double get_temp() const { return temp; }
	double at(double position) {
		if (upper_end.y == lower_end.y) {
			temp = lower_end.x-0.1;
		}
		else { temp = upper_end.x - (double)((lower_end.x - upper_end.x)*(position - upper_end.y)) / (upper_end.y - lower_end.y); }
		return temp;
	}
	point upper_end;
	point lower_end;
	double temp;
};