#pragma once
#include "coast_node.h"
#include "func.h"
#include "point.h"
#include "site.h"
#include "Event_circle.h"
#include "half_edge.h"
#include "vertex.h"
#include <vector>

class coast_line
{
public:
	coast_line(coast_node* root1) :root(root1) { size = 1; };
	~coast_line();
	coast_node* root;
	double position;
	coast_node* insert(const site& in, std::vector<half_edge*>& edge_vec);
	coast_node* find(double x, double posi);
	coast_node* remove(Event_circle* p, vertex* vt, std::vector<half_edge*>& edge_vec);
	int size;
};

