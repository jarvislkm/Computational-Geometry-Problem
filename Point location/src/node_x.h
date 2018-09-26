#pragma once
#include "node.h"
class node_x :public node {
public:
	node_x(point pp):p(pp) {};
	virtual bool is_terminal() { return false; };
	virtual bool compare(point pp) {
		if (pp < p) return true;  //left is true;
		else return false;
	};
	virtual long int compare_x(point pp) { 
		if (pp == p) return id; 
		else return 0;
	};
	point p;
	long int id;
};
