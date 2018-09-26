#pragma once
#include "half_edge.h"
class half_edge;
class face
{
public:
	face(int id1) : id(id1) { inc_edge = NULL; };
	int id;
	half_edge* inc_edge;
};

