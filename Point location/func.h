#pragma once
#include "point.h"
#include "segment.h"

double to_left(point a, point b, point c);
double to_left(segment s, point c);
void swap(point & a, point& b);
