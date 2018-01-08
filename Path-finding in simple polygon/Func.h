#pragma once
#include <vector>
#include "Point.h"

struct circle_node {
	int num;
	bool enable;
	std::vector<int> relation;
};

struct edge {
	edge(int aa, int bb) {
		if (aa > bb) { a = aa; b = bb; }
		else { a = bb; b = aa; }
	}
	int a;
	int b;
	int distance;
};

struct triangle {
	triangle(int aa, int bb, int cc) :a(aa), b(bb), c(cc) {};
	int a;
	int b;
	int c;
	triangle* par = NULL;
	triangle* lc = NULL;
	triangle* rc = NULL;
	int position;
};

bool compare(edge x, edge y);
bool compare_by_y(point* a, point* b);
bool compare_by_num(point* a, point* b);
double to_left(point a, point b, point c);
edge find_edge(triangle* a, triangle* b);
int find_commom_point_in_edge(edge& a, edge& b);
void traverse(triangle* root);
int find_common(std::vector<int> &a, std::vector<int>&b, int not_this);
bool start_point_in_triangle(int count, std::vector<point*>& mo_point, std::vector<triangle*>& dual_tree, point start_point);
bool end_point_in_triangle(int count, std::vector<point*>& mo_point, std::vector<triangle*>& dual_tree, point end_point);
void handle_monotone(std::vector<int>number, std::vector<point*>& mo_point, std::vector<edge>& mono_edge);
void add_node(int a, int b, std::vector<circle_node>& table, triangle* &parent, bool is_lc, int not_this, std::vector<triangle*>& dual_tree);