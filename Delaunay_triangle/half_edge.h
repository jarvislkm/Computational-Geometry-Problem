#pragma once
#include "vertex.h"
#include "face.h"
class vertex;
class face;
class half_edge
{
public:
	half_edge(int num) :id(num) { twin = NULL; pre = NULL; succ = NULL; ori = NULL; inc_face = NULL; };
	half_edge(int num, vertex* o) :id(num), ori(o) { twin = NULL; pre = NULL; succ = NULL; inc_face = NULL; };
	int id;
	half_edge* twin;
	half_edge* pre;
	half_edge* succ;
	vertex* ori;
	face* inc_face;
};

