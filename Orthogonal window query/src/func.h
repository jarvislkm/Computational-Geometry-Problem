#pragma once
#include "point.h"
#include <vector>

const long kMaxValue = 1e7;  //
const long kMinValue = -1e7;

bool CompareY(const Point& a, const Point& b);

bool CompareX(const Point& a, const Point& b);

void MergeYList(std::vector<Point>& ylist_l, std::vector<Point>& ylist_r, std::vector<Point>& ylist);
