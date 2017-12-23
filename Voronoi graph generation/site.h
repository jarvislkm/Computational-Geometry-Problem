#pragma once
#include "point.h"
class site{
public:
	int id;
	point p;
	site() { id = 0; };
	site(int x, int y, int num) : p(x,y), id(num){};
};