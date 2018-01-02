#include "Dag.h"
#include "node_x.h"
#include "node_y.h"
#include "node_t.h"
#include "Header.h"

Dag::Dag(node* r)
{
	root = r;
}

node* Dag::find(point p) {
	node* work = root;
	while (!work->is_terminal()) {
		if (work->compare(p)) {
			work = work->lc;
		}
		else work = work->rc;
	}
	return work;
}

void Dag::handle_intersection(vector<node_t*>& intersection, segment* insert) {
	node_t* begin = intersection.at(0);
	node_t* U = NULL;
	node_t* L = NULL;

	node_x* x = new node_x(insert->lp);
	x->id = insert->id;

	node_y* y = new node_y(insert);
	node_t* front = new node_t(begin->t.left, insert->lp, begin->t.upper, begin->t.lower);
	U = new node_t(insert->lp, begin->t.right, begin->t.upper, insert);
	L = new node_t(insert->lp, begin->t.right, insert, begin->t.lower);
	x->parent = begin->parent;
	for (node* p : begin->parent) {
		(dynamic_cast<node_t*>(p->lc) == begin ? p->lc : p->rc) = x;
	}
	x->lc = front;  x->rc = y;
	y->lc = U; y->rc = L;
	front->parent.push_back(x); y->parent.push_back(x);
	U->parent.push_back(y); L->parent.push_back(y);

	front->left_low_neighbor = begin->left_low_neighbor;
	front->left_up_neighbor = begin->left_up_neighbor;

	if (begin->left_low_neighbor) begin->left_low_neighbor->right_low_neighbor = front;
	if (begin->left_up_neighbor) begin->left_up_neighbor->right_up_neighbor = front;

	front->right_up_neighbor = U;
	front->right_low_neighbor = L;
	U->left_up_neighbor = front;
	L->left_low_neighbor = front;	

	// for (long int i = 1; i < intersection.size(); i++) {
		// node_t* work = intersection.at(i);
		// node_t* pre = intersection.at(i-1);
		// node_t* new_node = NULL;
		// node_y* y = new node_y(insert);

		// if (pre->right_up_neighbor == work) {
			// y->lc = U;
			// U->parent.push_back(y);
			// U->t.right = small(work->t.right, insert->rp);  //extend common area;
			// new_node = new node_t(*work);
			// new_node->t.upper = insert;

			// new_node->left_up_neighbor = L;
			// L->right_up_neighbor = new_node;
			// L->right_low_neighbor = pre->right_low_neighbor;
			// if (pre->right_low_neighbor) pre->right_low_neighbor->left_low_neighbor = L;
			// if (work->left_low_neighbor) work->left_low_neighbor->right_low_neighbor = new_node;

			// y->rc = new_node;
			// new_node->parent.clear();
			// new_node->parent.push_back(y);
			// L = new_node;
		// }
		// else if (pre->right_low_neighbor == work) {
			// y->rc = L;
			// L->parent.push_back(y);
			// L->t.right = small(work->t.right, insert->rp);  //extend common area;
			// new_node = new node_t(*work);
			// new_node->t.lower = insert;

			// new_node->left_low_neighbor = U;
			// U->right_low_neighbor = new_node;
			// U->right_up_neighbor = pre->right_up_neighbor;
			// if (pre->right_up_neighbor) { pre->right_up_neighbor->left_up_neighbor = U; }
			// if (work->left_up_neighbor) { work->left_up_neighbor->right_up_neighbor = new_node; }
			// y->lc = new_node;
			// new_node->parent.clear();
			// new_node->parent.push_back(y);
			// U = new_node;
		// }

		// if (i != intersection.size() - 1) {
			// y->parent = work->parent;
			// for (node* p : work->parent) {
				// (dynamic_cast<node_t*>(p->lc) == work ? p->lc : p->rc) = y;
			// }
		// }
		// else {
			// new_node->t.right = insert->rp;
			// node_x* x = new node_x(insert->rp);
			// x->id = insert->id;

			// x->parent = work->parent;
			// for (node* p : work->parent) {
				// (dynamic_cast<node_t*>(p->lc) == work ? p->lc : p->rc) = x;
			// }
			// x->lc = y; y->parent.push_back(x);
			// node_t* back = new node_t(insert->rp, work->t.right, work->t.upper, work->t.lower);
			// back->parent.push_back(x); x->rc = back;

			// back->left_up_neighbor = U; U->right_up_neighbor = back;
			// back->left_low_neighbor = L; L->right_low_neighbor = back;

			// back->right_low_neighbor = work->right_low_neighbor;
			// back->right_up_neighbor = work->right_up_neighbor;
			// if (work->right_low_neighbor) work->right_low_neighbor->left_low_neighbor = back;
			// if (work->right_up_neighbor) work->right_up_neighbor->left_up_neighbor = back;
		// }
	// }
	// for (auto n : intersection) {
		// delete n;
	// }
}

void Dag::insert(segment* s) {
	node* start = find(s->lp);
	node* end = find(s->rp);

	node_t* start_t = dynamic_cast<node_t*>(start);
	node_t* end_t = dynamic_cast<node_t*>(end);
	trapezoid* trap = start_t->get_trap();
	trapezoid* trap_end = end_t->get_trap();

	if (trap && trap == trap_end) {
		node_x* x1 = new node_x(s->lp);
		x1->id = s->id;
		node_x* x2 = new node_x(s->rp);
		x2->id = s->id;

		node_y* y = new node_y(s);
		node_t* L = new node_t(trap->left, s->lp, trap->upper, trap->lower);
		node_t* R = new node_t(s->rp, trap->right, trap->upper, trap->lower);
		node_t* A = new node_t(s->lp, s->rp, trap->upper, s);
		node_t* B = new node_t(s->lp, s->rp, s, trap->lower);
		for (node* p: start->parent) {
			(p->lc == start ? p->lc : p->rc) = x1;
		}
		if (root == start) { root = x1; }
		x1->parent = start->parent;
		x2->parent.push_back(x1);
		y->parent.push_back(x2);
		L->parent.push_back(x1);
		A->parent.push_back(y);
		B->parent.push_back(y);
		R->parent.push_back(x2);

		x1->lc = L; x1->rc = x2;
		x2->lc = y; x2->rc = R;
		y->lc = A; y->rc = B;

		L->left_low_neighbor = start_t->left_low_neighbor;
		L->left_up_neighbor = start_t->left_up_neighbor;
		L->right_up_neighbor = A;
		L->right_low_neighbor = B;

		A->left_up_neighbor = L;
		A->right_up_neighbor = R;
		B->left_low_neighbor = L;
		B->right_low_neighbor = R;

		R->left_up_neighbor = A;
		R->left_low_neighbor = B;
		R->right_low_neighbor = start_t->right_low_neighbor;
		R->right_up_neighbor = start_t->right_up_neighbor;

		if (start_t->left_low_neighbor) start_t->left_low_neighbor->right_low_neighbor = L;
		if (start_t->left_up_neighbor) start_t->left_up_neighbor->right_up_neighbor = L;
		if (start_t->right_low_neighbor) start_t->right_low_neighbor->left_low_neighbor = R;
		if (start_t->right_up_neighbor) start_t->right_up_neighbor->left_up_neighbor = R;

		delete start_t;
		return;
	}  // two endpoint in same trap;
	else {
		vector<node_t*> intersection;
		while (trap!=trap_end) {
			intersection.push_back(start_t);
			node_t* next = NULL;
			node_t* up = start_t->right_up_neighbor;
			node_t* low = start_t->right_low_neighbor;
			next = low;
			if (up) {
				point use_p(up->t.lower->at(up->t.left.x).x, up->t.lower->at(up->t.left.x).y);
				if (to_left(*s, use_p) < 0) {next = up;}
			}
			start_t = next;
			trap = start_t->get_trap();
		}
		intersection.push_back(start_t); // all intersection node;
		handle_intersection(intersection, s);
	}
}