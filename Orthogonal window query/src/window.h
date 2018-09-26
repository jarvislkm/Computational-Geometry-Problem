#pragma once
#include "point.h"
class Window {
public:
	Window(Point l, Point r): ll(l), ru(r){};
	Point ll;
	Point ru;
};