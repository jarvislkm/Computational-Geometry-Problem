#pragma once
#include "Segment.h"
class avl_node {
public:
	avl_node(segment _segm, segment _segm2, avl_node* _parent = NULL) : segm1(_segm), segm2(_segm2), parent(_parent) { rc = NULL; lc = NULL; rheight = 0; lheight = 0; };
	avl_node(avl_node &a) :segm1(a.segm1), segm2(a.segm2), helper(a.helper){};
	bool is_root() { return !(parent); };
	bool is_left_child() { return (!is_root()) && (this == parent->lc); };
	bool is_balance() { return (lheight - rheight)<2 && (lheight - rheight)>-2; };
	avl_node* succ();
	avl_node* pre();
	avl_node* rc;
	avl_node* lc;
	avl_node* parent;
	segment segm1,segm2;
	point helper;
	int lheight;
	int rheight;
};
