#include "Node.h"
avl_node* avl_node::succ() {
	avl_node* tem = NULL;
	if (rc) {
		tem = rc;
		while (tem->lc) {
			tem = tem->lc;
		}
		return tem;
	}
	else {
		tem = this;
		while (!tem->is_left_child() && !tem->is_root()) {
			tem = tem->parent;
		}
		tem = tem->parent; return tem;
	};
}
avl_node* avl_node::pre() {
	avl_node* tem = NULL;
	if (lc) {
		tem = lc;
		while (tem->rc) {
			tem = tem->rc;
		}
		return tem;
	}
	else {
		tem = this;
		while (tem->is_left_child() && !tem->is_root()) {
			tem = tem->parent;
		}
		tem = tem->parent; return tem;
	};
}