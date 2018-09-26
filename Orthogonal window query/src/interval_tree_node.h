#pragma once
#include "range_tree.h"
#include "segment.h"
#include <vector>
class IntervalTreeNode {
public:
	IntervalTreeNode(std::vector<Segment> seg_vec);
	~IntervalTreeNode();
	long position;
	long number;
	RangeTree* range_left;
	RangeTree* range_right;
	IntervalTreeNode* lc;
	IntervalTreeNode* rc;
	std::vector<long> find_left(double x, double y_up, double y_low);
	std::vector<long> find_right(double x, double y_up, double y_low);
	void Remove();
};