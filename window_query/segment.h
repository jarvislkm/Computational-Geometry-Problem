#pragma once
#include "point.h"
class segment {
public:
	segment(point pp1, point pp2, long id_i) :p1(pp1), p2(pp2), id(id_i) {};
	point p1;
	point p2;
	long id;
};