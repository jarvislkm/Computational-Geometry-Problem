#pragma once
#include "point.h"
#include <vector>
namespace range_tree_project {
bool compare_y(const point& a, const point& b);
bool compare_x(const point& a, const point& b);
void merge_ylist(std::vector<point>& ylist_l, std::vector<point>& ylist_r, std::vector<point>& ylist);
}

