#pragma once
#include"interval_tree_node.h"
class interval_tree {
public:
	interval_tree(std::vector<segment> seg_vec) {
		root = new it_node(seg_vec);
	};
	it_node* root;
	std::vector<long> line_number(double x, double y_up, double y_low) {
		it_node* start = root;
		long count = 0;
		std::vector<long> result;
		while (start) {
			if (x-0.5 > start->position) { 
				auto p = start->find_right(x, y_up, y_low);
				result.insert(result.end(), p.begin(), p.end());
				start = start->rc;
			}
			else if (x-0.5 < start->position) {
				auto p = start->find_left(x, y_up, y_low);
				result.insert(result.end(), p.begin(), p.end());
				start = start->lc;
			}
//			else if (x == start->position) { return start->number; }
		}
		return result;
	}
};