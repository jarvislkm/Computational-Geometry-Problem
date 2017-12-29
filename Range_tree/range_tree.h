#pragma once
#include "range_tree_node.h"
#include <vector>
using namespace std;
class range_tree {
public:
	range_tree(vector<point> &p_v) { root = construct(p_v); };
	node* construct(vector<point> &p_v);
	long int range(point left, point right);
	node* root;
};