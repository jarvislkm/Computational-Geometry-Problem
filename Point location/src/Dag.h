#pragma once
#include "node.h"
#include "node_t.h"
#include "point.h"
class Dag
{
public:
	Dag(node* r);
	node* root;
	node* find(point p);
	void insert(segment* s);
	void handle_intersection(std::vector<node_t*>& intersection, segment* insert);
};

