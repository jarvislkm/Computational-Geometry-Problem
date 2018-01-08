#pragma once
#include "point.h"
#include "segment.h"
#include "trapezoid.h"
#include <iostream>
class node{
public:
	node() { lc = NULL; rc = NULL; };
	node(node& n) { parent = n.parent; lc = n.lc; rc = n.rc; };
	virtual bool compare(point p) = 0;
	virtual trapezoid* get_trap() { return NULL; };
	virtual long int compare_x(point p) { return 0; };
	virtual bool is_terminal() = 0;
	node* lc;
	node* rc;
	std::vector<node*> parent;
};
