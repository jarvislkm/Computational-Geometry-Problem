#include "coast_line.h"

coast_line::~coast_line()
{
	coast_node* work = root;
}

coast_node* coast_line::find(double x, double pos) {
	coast_node* work = root;
	while (!work->is_leaf()) {
		if (x <= work->break_point(pos)) { work = work->lc; }
		else work = work->rc;
	}
	return work;
}

coast_node*  coast_line::insert(const site& to_insert, std::vector<half_edge*>& edge_vec) {
	coast_node* to_replace = find(to_insert.p.x, to_insert.p.y);

	coast_node* r_parent = to_replace->parent;

	coast_node* inter_1 = new coast_node(to_insert, to_replace->leaf);
	coast_node* leaf_3 = new coast_node(to_replace->leaf);
	leaf_3->parent = inter_1;
	inter_1->rc = leaf_3;
	inter_1->parent = r_parent;

	coast_node* inter_2 = new coast_node(to_replace->leaf, to_insert); 
	coast_node* leaf_1 = new coast_node(to_replace->leaf);
	coast_node* leaf_2 = new coast_node(to_insert);
	inter_2->lc = leaf_1;
	inter_2->rc = leaf_2;
	leaf_1->parent = inter_2;
	leaf_2->parent = inter_2;
	inter_2->parent = inter_1;
	inter_1->lc = inter_2;
	if (to_replace->is_lc()) { r_parent->lc = inter_1; }
	else if (to_replace->is_rc()) { r_parent->rc = inter_1; }
	else if (to_replace->is_root()) { root = inter_1; }

	if(to_replace->pred) to_replace->pred->suc = leaf_1;
	leaf_1->pred = to_replace->pred;
	leaf_1->suc = leaf_2;
	leaf_2->pred = leaf_1;
	leaf_2->suc = leaf_3;
	leaf_3->pred = leaf_2;
	leaf_3->suc = to_replace->suc;
	if (to_replace->suc) to_replace->suc->pred = leaf_3;

	int size = edge_vec.size();
	half_edge* e1 = new half_edge(size);
	edge_vec.push_back(e1);
	half_edge* e2 = new half_edge(size+1);
	edge_vec.push_back(e2);
	e1->twin = e2;
	e2->twin = e1;

	inter_1->edge = e1;
	inter_2->edge = e2;

	to_replace->parent = leaf_2;
	size++;
    return to_replace;
}

coast_node* coast_line::remove(Event_circle* p, vertex* vt, std::vector<half_edge*>& edge_vec) {
	// remove a arc from the coast line; set vertex/edge 
	//coast_node* to_move = find(p->eventpoint.x, p->eventpoint.y+0.01);
	//if (to_move->re_event != p) {
	//	if (to_move->suc && to_move->suc->re_event == p) to_move = to_move->suc;
	//	else if (to_move->pred && to_move->pred->re_event == p) to_move = to_move->pred;
	//}
	coast_node* to_move = p->node;
	coast_node* work = to_move->parent;
	coast_node* another_inter = work->parent;

	to_move->pred->suc = to_move->suc;
	to_move->suc->pred = to_move->pred;
	// find another inter node use same arc. 
	if (to_move->is_rc()) {
			if (work->is_lc()) {
				work->parent->lc = work->lc;
			}
			else {
				work->parent->rc = work->lc;
			}
			work->lc->parent = work->parent;

			while (another_inter) {
				if ((another_inter->p1.id == to_move->leaf.id) && (another_inter->p2.id == to_move->suc->leaf.id)) {
					another_inter->p1 = to_move->pred->leaf; //change site
					another_inter->edge->ori = vt;
					break;
				}
				another_inter = another_inter->parent;
			}
		}
	else {
		if (work->is_lc()) {
			work->parent->lc = work->rc;
		}
		else {
			work->parent->rc = work->rc;
		}
		work->rc->parent = work->parent;

		while (another_inter) {
			if ((another_inter->p1.id == to_move->pred->leaf.id) && (another_inter->p2.id == to_move->leaf.id)) {
				another_inter->p2 = to_move->suc->leaf; //change site
				another_inter->edge->ori = vt;
				break;
			}
			another_inter = another_inter->parent;
		}
	}
	// set vertex to edge
	work->edge->ori = vt;
	vt->inc_edge = work->edge;

	// set edge relation
	work->edge->succ = another_inter->edge->twin;
	another_inter->edge->twin->pre = work->edge;

	// add new edge
	int size_edge = edge_vec.size();
	half_edge* new_edge_a = new half_edge(size_edge);
	half_edge* new_edge_b = new half_edge(size_edge + 1);
	new_edge_a->twin = new_edge_b;
	new_edge_b->twin = new_edge_a;
	new_edge_a->ori = vt;
	
	// set edge relation
	new_edge_a->succ = work->edge->twin;
	work->edge->twin->pre = new_edge_a;
	another_inter->edge->succ = new_edge_b;
	new_edge_b->pre = another_inter->edge;

	// set new edge, have no ori
	another_inter->edge = new_edge_b;

	edge_vec.push_back(new_edge_a);
	edge_vec.push_back(new_edge_b);

	delete work;
	size--;
	return to_move;
}
