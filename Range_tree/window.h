#pragma once
#include "point.h"
class window {
public:
	window(point l, point r): ll(l), ru(r){};
	point ll;
	point ru;
};