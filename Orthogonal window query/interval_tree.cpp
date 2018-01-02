#include "interval_tree.h"

IntervalTree::~IntervalTree() {
	root->Remove();
	delete root;
}

std::vector<long> IntervalTree::QueryStabNum(double x, double y_up, double y_low) {
	IntervalTreeNode* start = root;
	long count = 0;
	std::vector<long> result;
	while (start) {
		if (x - 0.5 > start->position) {
			auto p = start->find_right(x, y_up, y_low);
			result.insert(result.end(), p.begin(), p.end());
			start = start->rc;
		}
		else if (x - 0.5 < start->position) {
			auto p = start->find_left(x, y_up, y_low);
			result.insert(result.end(), p.begin(), p.end());
			start = start->lc;
		}
	}
	return result;
}