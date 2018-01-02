#pragma once
#include "point.h"
#include <iostream>
#include <vector>
class RangeTree;
class RangeTreeNode {
public:
	RangeTreeNode(Point pp):p(pp) {
		lc = NULL; rc = NULL; parent = NULL;
	};
	bool is_leaf() { return !(lc || rc); }
	long ylist_find(double top, double bottom);
	long find_top(double top);
	long find_bottom(double bottom);
	void Remove();
	Point p;
	RangeTreeNode* lc;
	RangeTreeNode* rc;
	RangeTreeNode* parent;
	std::vector<Point> ylist;
};