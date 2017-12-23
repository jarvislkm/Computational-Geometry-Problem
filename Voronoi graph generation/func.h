#pragma once
#include "coast_node.h"
#include "point.h"
#include "site.h"
#include <math.h>

struct cir_res {
	bool success;
	point circle_point;
	point circle_center;
};
cir_res circle_detect(coast_node* node);
cir_res circle_bottom(site& a, site& b, site& c);
bool sort_site(site a, site b);