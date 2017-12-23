#include "func.h"

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

cir_res circle_detect(coast_node* node) {
	cir_res result;
	if (node->suc && node->pred && node->suc->leaf.id != node->pred->leaf.id) {
		result = circle_bottom(node->pred->leaf, node->leaf, node->suc->leaf);
		result.success = true;
	}
	else result.success = false;
	return result;
};
