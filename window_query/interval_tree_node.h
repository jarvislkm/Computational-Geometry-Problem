#pragma once
#include "range_tree.h"
#include "segment.h"
#include <vector>
class it_node {
public:
	it_node(std::vector<segment> seg_vec);
	long position;
	long number;
	range_tree* range_left;
	range_tree* range_right;
	it_node* lc;
	it_node* rc;
	std::vector<long> find_left(double x, double y_up, double y_low);
	std::vector<long> find_right(double x, double y_up, double y_low);
};