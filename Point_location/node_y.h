#pragma once
#include "node.h"
#include "func.h"
class node_y :public node {
public:
	node_y(segment* ss) { s = ss; };
	virtual bool is_terminal() { return false; };
	virtual bool compare(point pp) {
		if (to_left(*s, pp) > 0) return true; // upper is true;
		else return false;
	};
	segment* s;
};
