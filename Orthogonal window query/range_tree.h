#pragma once
#include "range_tree_node.h"
#include <vector>

class RangeTree {
public:
	RangeTree(std::vector<Point> &p_v) { root = construct(p_v); };
	~RangeTree();
	RangeTreeNode* construct(std::vector<Point> &p_v);
	long QueryRange(Point left, Point right);
	RangeTreeNode* root;
	std::vector<long> point_id;
};