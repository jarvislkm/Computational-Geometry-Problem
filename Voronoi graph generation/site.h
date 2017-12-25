#pragma once
#include "point.h"
class site{
public:
	int id;
	point p;
	site() { id = 0; };
	site(double x, double y, int num) : p(x,y), id(num){};
};