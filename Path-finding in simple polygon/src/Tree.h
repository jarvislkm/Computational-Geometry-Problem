#pragma once
#include "Node.h"
struct result {
	bool find;
	avl_node*& node;
};

class avl_tree {
public:
	avl_tree(avl_node *_root) : root(_root) { size = 1; hot = NULL; };
	avl_tree() { root = NULL; size = 0; hot = NULL; };
	void set_position(double po) { position = po; };
	avl_node* & search_in(avl_node*& r, segment& to_find, avl_node* &hot);
	avl_node* & search(segment &to_find);
	result search_point(point &p);
	result search_point_in(avl_node*& now,point &p);
	void update_above(avl_node *_start);
	void updata_height(avl_node *now);
	void traverse(avl_node* root);
	avl_node* connect34(avl_node* a1, avl_node*a2, avl_node*a3, avl_node*b1, avl_node*b2, avl_node*b3, avl_node*b4);
	avl_node* remove_at(avl_node *&to_remove);
	avl_node* rotate_at(avl_node* node);
	avl_node* add_node(segment &to_find1, segment &to_find2);
	avl_node* delete_node(segment &to_delete);
	avl_node* root;
	avl_node* hot;
	double position;
	int size;
};