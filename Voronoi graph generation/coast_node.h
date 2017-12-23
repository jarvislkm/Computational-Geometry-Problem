#pragma once
#include <iostream>
#include "site.h"
#include "Event_circle.h"
#include "half_edge.h"

class coast_node
{
public:
	explicit coast_node(site p1a, site p2a) :p1(p1a), p2(p2a) { lc = NULL; rc = NULL; pred = NULL; suc = NULL; re_event = NULL; edge = NULL; };
	explicit coast_node(site l) :leaf(l), p1(l), p2(l) { lc = NULL; rc = NULL; pred = NULL; suc = NULL; re_event = NULL;  edge = NULL; };
	explicit coast_node() { lc = NULL; rc = NULL; pred = NULL; suc = NULL; re_event = NULL;};
	site p1, p2;
	site leaf;
	double break_point(double po) {
		if (lc && rc) {
			return intersection(p1, p2, po);
		}
		else return 0;
	}
	bool is_leaf() { return !(lc&&rc); }
	bool is_root() { return !parent; }
	bool is_lc() {
		if (parent && parent->lc == this) return true;
		else return false;
	}
	bool is_rc() {
		if (parent && parent->rc == this) return true;
		else return false;
	}
	double intersection(site &left, site &right, double position) {
		double xa = left.p.x;
		double ya = left.p.y;
		double xb = right.p.x;
		double yb = right.p.y;

		double a = yb - ya;
		if (a == 0) return (xa + xb) / 2;

		double b = xb*(2 * ya - 2 * position) - xa*(2 * yb - 2 * position);
		double c = (xa*xa + ya*ya - position*position)*(yb - position) - (xb*xb + yb*yb - position*position)*(ya - position);

		double x1 = (sqrt(b*b - 4 * a*c) - b) / (2 * a);
		double x2 = (-sqrt(b*b - 4 * a*c) - b) / (2 * a);
		double x1dl = (x1 - xa) / (ya - position);
		double x1dr = (x1 - xb) / (yb - position); // left(x) < right(x)
		if (x1dl > x1dr) return x1;
		else return x2;
	}
	coast_node* pred;
	coast_node* suc;
	Event_circle* re_event;

	half_edge* edge;

	coast_node* parent;
	coast_node* lc;
	coast_node* rc;
	//coast_node* pre() {
	//	if (is_root()) return NULL;
	//	coast_node* work = parent;
	//	while (work && work->is_lc()) {
	//		work = work->parent;
	//	}
	//	if (!work) return NULL;
	//	work = work->lc;
	//	if (!work) return NULL;
	//	while (work->rc) {
	//		work = work->rc;
	//	}
	//	return work;
	//}
	//coast_node* succ() {
	//	if (is_root()) return NULL;
	//	coast_node* work = parent;
	//	while (work && work->is_rc()) {
	//		work = work->parent;
	//	}
	//	if (!work) return NULL;
	//	work = work->rc;
	//	if (!work) return NULL;
	//	while (work->lc) {
	//		work = work->lc;
	//	}
	//	return work;
	//}

};

