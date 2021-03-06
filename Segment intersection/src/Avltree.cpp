#include "Avltree.h"
void avl_tree::traverse(avl_node* root) {
	if (root) {
		if (root->lc) { traverse(root->lc); }
		if (root) std::cout << "lh: " << root->lheight << "  rh: " << root->rheight << "  at: " << position << " is " << root->segm.at(position) << " size: " << size << std::endl;
		if (root->rc) { traverse(root->rc); }
	}
}

void avl_tree::updata_height(avl_node *now) {
	if (now->lc) {
		now->lheight = max(now->lc->lheight, now->lc->rheight) + 1;
	}
	else now->lheight = 0;
	if (now->rc) {
		now->rheight = max(now->rc->lheight, now->rc->rheight) + 1;
	}
	else now->rheight = 0;
}

avl_node* avl_tree::connect34(avl_node* a1, avl_node*a2, avl_node*a3, avl_node*b1, avl_node*b2, avl_node*b3, avl_node*b4) {
	a1->lc = b1; if (b1) { b1->parent = a1; }
	a1->rc = b2; if (b2) { b2->parent = a1; }
	updata_height(a1);
	a3->lc = b3; if (b3) { b3->parent = a3; }
	a3->rc = b4; if (b4) { b4->parent = a3; }
	updata_height(a3);
	a1->parent = a2; a2->lc = a1;
	a3->parent = a2; a2->rc = a3;
	updata_height(a2);
	return a2;
}

void avl_tree::update_above(avl_node *_start) {
	updata_height(_start);
	if (!_start->is_balance()) {
		rotate_at(_start);
	}
	if (_start != root) {
		avl_node* par = _start->parent;
		update_above(par);
	}
}

avl_node* avl_tree::rotate_at(avl_node* par) {
	avl_node* re = NULL;
	avl_node* pp = par->parent;
	if (par->lheight > par->rheight) {
		if (par->lc->lheight > par->lc->rheight) {
			re = from_parent_to(par) = connect34(par->lc->lc, par->lc, par, par->lc->lc->lc, par->lc->lc->rc, par->lc->rc, par->rc);
		}
		else {
			re = from_parent_to(par) = connect34(par->lc, par->lc->rc, par, par->lc->lc, par->lc->rc->lc, par->lc->rc->rc, par->rc);
		}
	}
	else {
		if (par->rc->lheight > par->rc->rheight) {
			re = from_parent_to(par) = connect34(par, par->rc->lc, par->rc, par->lc, par->rc->lc->lc, par->rc->lc->rc, par->rc->rc);
		}
		else {
			re = from_parent_to(par) = connect34(par, par->rc, par->rc->rc, par->lc, par->rc->lc, par->rc->rc->lc, par->rc->rc->rc);
		}
	}
	re->parent = pp;
	return par;
}

avl_node*& avl_tree::search_in(avl_node*& r, segment &to_find, avl_node* &hot, double ref) {   //if same value at p0, then compare value at p0+ref
	if (!r || r->segm == to_find) { return r; }   // if find identical segment
	hot = r;
	avl_node* next = NULL;
	if (is_zero((r->segm.at(position) - to_find.at(position)))) {
		return search_in((r->segm.at(position + ref) > to_find.at(position + ref)) ? r->lc : r->rc, to_find, hot, ref);    //if same value at start position p0, sort by p0+1
	}
	else {
		return search_in((r->segm.at(position) > to_find.at(position)) ? r->lc : r->rc, to_find, hot, ref);
	}
}

avl_node*& avl_tree::search(segment& to_find, double ref) {
	return search_in(root, to_find, hot, ref);
}

avl_node* avl_tree::add_node(segment &to_find) {
	avl_node* & now = search_in(root, to_find, hot, 0.001);  // find the proper position; & is mandatory to get the add not copy
	avl_node* new_node = new avl_node(to_find, hot);
	now = new_node;  // set proper position to new node
					 //	update_above(new_node);
	size++;
	return new_node;
};

avl_node* avl_tree::remove_at(avl_node *&to_remove) {
	avl_node* w = to_remove;
	avl_node* succ = NULL;
	if (!to_remove->lc) succ = to_remove = to_remove->rc;
	else if (!to_remove->rc) succ = to_remove = to_remove->lc;
	else {
		w = to_remove->succ();
		swap_seg(*to_remove, *w);
		avl_node* pa = w->parent;
		((pa == to_remove) ? pa->rc : pa->lc) = succ = w->rc;
	}
	hot = w->parent;
	if (succ) succ->parent = hot;
	delete w;
	return succ;
}

avl_node*  avl_tree::delete_node(segment &to_delete) {
	avl_node* & now = search_in(root, to_delete, hot, -0.001);
	if (!now) return NULL;
	avl_node* pre = now->pre();
	remove_at(now);
	//	if (hot) update_above(hot);
	size--;
	return pre;
}