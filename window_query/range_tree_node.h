#pragma once
#include "point.h"
#include <iostream>
#include <vector>
class range_tree;
class node {
public:
	node(point pp):p(pp) {
		lc = NULL; rc = NULL; parent = NULL;
	};
	bool is_leaf() { return !(lc || rc); }
	long ylist_find(double top, double bottom);
	long find_top(double top);
	long find_bottom(double bottom);
	point p;
	node* lc;
	node* rc;
	node* parent;
	std::vector<point> ylist;
};