#pragma once
#include "range_tree_node.h"
#include <vector>

class range_tree {
public:
	range_tree(std::vector<point> &p_v) { root = construct(p_v); };
	node* construct(std::vector<point> &p_v);
	long range(point left, point right);
	node* root;
	std::vector<long> point_id;
};