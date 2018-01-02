#pragma once
#include "point.h"
#include <vector>
const long max_v = 1e7;
const long min_v = -1e7;

bool compare_y(const point& a, const point& b);

bool compare_x(const point& a, const point& b);

void merge_ylist(std::vector<point>& ylist_l, std::vector<point>& ylist_r, std::vector<point>& ylist);