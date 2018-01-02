#pragma once
#include "point.h"
class Segment {
public:
	Segment(Point pp1, Point pp2, long id_i) :p1(pp1), p2(pp2), id(id_i) {};
	Point p1;
	Point p2;
	long id;
};