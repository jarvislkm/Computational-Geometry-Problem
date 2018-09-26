#pragma once
#include"interval_tree_node.h"
class IntervalTree {
public:
	IntervalTree(std::vector<Segment> seg_vec) {
		root = new IntervalTreeNode(seg_vec);
	};
	~IntervalTree();
	IntervalTreeNode* root;
	std::vector<long> QueryStabNum(double x, double y_up, double y_low);
};