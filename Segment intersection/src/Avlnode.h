#pragma once
#include "Header.h"
#include "Segment.h"
extern point tem_cal;
extern point tem_cal2;
class avl_node {
public:
	avl_node(segment _segm, avl_node* _parent = NULL) : segm(_segm), parent(_parent) { rc = NULL; lc = NULL; rheight = 0; lheight = 0; };
	avl_node(avl_node &a) :segm(a.segm) {};
	bool is_root() { return !(parent); };
	bool is_left_child() { return (!is_root()) && (this == parent->lc); };
	bool is_balance() { return (lheight - rheight)<2 && (lheight - rheight)>-2; };
	avl_node* succ();
	avl_node* pre();
	avl_node* rc;
	avl_node* lc;
	avl_node* parent;
	segment segm;
	int lheight;
	int rheight;
};


