#pragma once
#include "point.h"
#include <vector>
using namespace std;
bool compare_y(const point& a, const point& b);

bool compare_x(const point& a, const point& b);

void merge_ylist(vector<point>& ylist_l, vector<point>& ylist_r, vector<point>& ylist);