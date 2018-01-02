#pragma once
#include "point.h"
#include <iostream>
#include <vector>
using namespace std;
class range_tree;
class node {
public:
	node(point pp):p(pp) {
		lc = NULL; rc = NULL; parent = NULL;
	};
	bool is_leaf() { return !(lc || rc); }
	long int ylist_find(double top, double bottom);
	long int find_top(double top);
	long int find_bottom(double bottom);
	point p;
	node* lc;
	node* rc;
	node* parent;
	vector<point> ylist;
};