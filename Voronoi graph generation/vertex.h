#pragma once
#include <iostream>
#include "half_edge.h"
class half_edge;
class vertex
{
public:
	vertex(int id1, double x1, double y1) : id(id1), x(x1), y(y1) { inc_edge = NULL; };
	int id;
	double x;
	double y;
	double r;
	half_edge* inc_edge;
};

