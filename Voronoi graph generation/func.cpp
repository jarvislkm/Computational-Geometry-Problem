#include "func.h"
#include <math.h>
cir_res circle_bottom(site& a, site& b, site& c) {
	double A1 = 2 * (b.p.x - a.p.x);
	double B1 = 2 * (b.p.y - a.p.y);
	double C1 = b.p.x*b.p.x + b.p.y*b.p.y - a.p.x*a.p.x - a.p.y*a.p.y;
	double A2 = 2 * (c.p.x - b.p.x);
	double B2 = 2 * (c.p.y - b.p.y);
	double C2 = c.p.x*c.p.x + c.p.y*c.p.y - b.p.x*b.p.x - b.p.y*b.p.y;
	double x = (C1*B2 - C2*B1) / (A1*B2 - A2*B1);
	double y = (A1*C2 - A2*C1) / (A1*B2 - A2*B1);
	double r = sqrt((x - a.p.x)*(x - a.p.x) + (y - a.p.y)*(y - a.p.y));
	double y_b = y - r;
	point s(x, y_b);
	point s1(x, y);
	cir_res result;
	result.circle_point = s;
	result.circle_center = s1;
	return result;
}

bool sort_site(site a, site b) {
	if (!(a.p<b.p)) return true;
	else return false;
}

bool to_left(point a, point b, point c) {
	double tem1 = a.x*b.y + b.x*c.y + c.x*a.y - b.y*c.x - c.y*a.x - a.y*b.x;
	if (tem1 >= 0) return true;
	else return false;
}

cir_res circle_detect(coast_node* node) {
	cir_res result;
	double k1, k2;
	int d1=0, d2=0;
	if (node->suc && node->pred && node->suc->leaf.id != node->pred->leaf.id) {
		if (node->pred->leaf.p.y != node->leaf.p.y) {
			 k1 = -(node->pred->leaf.p.x - node->leaf.p.x)/(node->pred->leaf.p.y - node->leaf.p.y);
		}
		else k1 = INFINITY;
		if (node->suc->leaf.p.y != node->leaf.p.y) {
			k2 = -(node->suc->leaf.p.x - node->leaf.p.x)/(node->suc->leaf.p.y - node->leaf.p.y) ;
		}
		else k2 = INFINITY;

		result = circle_bottom(node->pred->leaf, node->leaf, node->suc->leaf);

		if (node->pred->leaf.p.y > node->leaf.p.y) { d1 = -1; }
		else if (node->pred->leaf.p.y < node->leaf.p.y) { d1 = 1; }
		if (node->leaf.p.y > node->suc->leaf.p.y) { d2 = -1; }
		else if (node->leaf.p.y < node->suc->leaf.p.y) { d2 = 1; }

		if (d1 == -1 && d2 == 1) result.success = false;
		else if ((d1 >= 0 && d2 == -1) || (d1 == 1 && d2 == 0)) result.success = true;
		else if (k1>k2) {
			result.success = true;
		}
		else result.success = false;
	}
	else result.success = false;
	return result;
};
