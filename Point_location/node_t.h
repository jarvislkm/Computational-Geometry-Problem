#pragma once
#include "node.h"
class node_t :public node {
public:
	node_t(point l, point r, segment* up, segment* low): t(l, r, up, low) {
		left_up_neighbor = NULL;
		right_up_neighbor = NULL;
		left_low_neighbor = NULL;
		right_low_neighbor = NULL;
	};
	node_t(node_t & n): node(n),t(n.t) {
		left_up_neighbor = n.left_up_neighbor;
		right_up_neighbor = n.right_up_neighbor;
		left_low_neighbor = n.left_low_neighbor;
		right_low_neighbor = n.right_low_neighbor;
	};
	virtual bool is_terminal() { return true; };
	virtual bool compare(point pp) { return false; };
	virtual trapezoid* get_trap() override { return &t; };
	trapezoid t;
	node_t* left_up_neighbor;
	node_t* right_up_neighbor;
	node_t* left_low_neighbor;
	node_t* right_low_neighbor;
};
