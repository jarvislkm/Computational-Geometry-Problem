#include "Func.h"

bool compare(edge x, edge y) {
	return x.distance < y.distance;
}
bool compare_by_y(point* a, point* b) {
	return a->y == b->y ? a->x < b->x : a->y > b->y;
}
bool compare_by_num(point* a, point* b) {
	return a->num<b->num;
}

double to_left(point a, point b, point c) {
	double tem1 = a.x*b.y + b.x*c.y + c.x*a.y - b.y*c.x - c.y*a.x - a.y*b.x;
	return tem1;
}

edge find_edge(triangle* a, triangle* b) {
	if (a->a == b->a || a->a == b->b || a->a == b->c) {}
	else return edge{ a->b,a->c };
	if (a->b == b->a || a->b == b->b || a->b == b->c) { return edge{ a->b,a->a }; }
	else return edge{ a->a,a->c };
}

int find_commom_point_in_edge(edge& a, edge& b) {
	if (a.a == b.a || a.a == b.b) return a.a;
	else return a.b;
}

void traverse(triangle* root) {
	if (root->lc) traverse(root->lc);
	std::cout << root->a << " " << root->b << " " << root->c << std::endl;
	if (root->rc) traverse(root->rc);
}

int find_common(std::vector<int> &a, std::vector<int>&b, int not_this) {
	int i = 0;
	int j = 0;
	while (a.at(i) != b.at(j) || a.at(i) == not_this) {
		if (a.at(i) < b.at(j)) i++;
		else j++;
	}
	return a.at(i);
}

bool start_point_in_triangle(int count, std::vector<point*>& mo_point, std::vector<triangle*>& dual_tree, point start_point) {
	point* a = mo_point.at(dual_tree.at(count)->a);
	point* b = mo_point.at(dual_tree.at(count)->b);
	point* c = mo_point.at(dual_tree.at(count)->c);
	if (to_left(*a, *b, *c) < 0) {
		c = mo_point.at(dual_tree.at(count)->b);
		b = mo_point.at(dual_tree.at(count)->c);
	}
	if (to_left(*a, *b, start_point) >= 0 && to_left(*b, *c, start_point) >= 0 && to_left(*c, *a, start_point) >= 0) return true;
	else return false;
}

bool end_point_in_triangle(int count, std::vector<point*>& mo_point, std::vector<triangle*>& dual_tree, point end_point) {
	point* a = mo_point.at(dual_tree.at(count)->a);
	point* b = mo_point.at(dual_tree.at(count)->b);
	point* c = mo_point.at(dual_tree.at(count)->c);
	if (to_left(*a, *b, *c) < 0) {
		c = mo_point.at(dual_tree.at(count)->b);
		b = mo_point.at(dual_tree.at(count)->c);
	}
	if (to_left(*a, *b, end_point) >= 0 && to_left(*b, *c, end_point) >= 0 && to_left(*c, *a, end_point) >= 0) return true;
	else return false;
}

void handle_monotone(std::vector<int>number, std::vector<point*>& mo_point, std::vector<edge>& mono_edge) {
	auto max = number.begin();
	auto min = number.begin();
	for (auto s = number.begin(); s < number.end(); s++) {
		if (*mo_point.at(*s) > *mo_point.at(*max)) max = s;
		if (*mo_point.at(*s) < *mo_point.at(*min)) min = s;
	}
	auto right = max;
	auto left = max;
	if (max + 1 == number.end()) {
		left = number.begin();
		right = max - 1;
	}
	else if (max == number.begin()) {
		right = number.end() - 1;
		left = max + 1;
	}
	else {
		right = max - 1;
		left = max + 1;
	}
	std::vector<int> stack;
	stack.push_back(*max);
	int stack_status = 0;
	int point_status = 0;
	while (right != min || left != min) {
		auto to_add = max;
		if (*mo_point.at(*right) > *mo_point.at(*left)) {
			to_add = right;
			point_status = 1;
			if (right == number.begin()) { right = number.end() - 1; }
			else right = right - 1;
		}
		else {
			to_add = left;
			point_status = -1;
			if (left == number.end() - 1) { left = number.begin(); }
			else left = left + 1;
		}
		if (stack.size() <= 1) {
			stack_status = point_status;
			stack.push_back(*to_add);
			continue;
		}
		if (stack_status == point_status) {
			while (stack.size() > 1) {
				auto stack_end = stack.end() - 1;
				auto stack_end_2 = stack.end() - 2;
				if (stack_status*to_left(*mo_point.at(*to_add), *mo_point.at(*stack_end), *mo_point.at(*stack_end_2)) <= 0) { break; }
				else {
					stack.pop_back();
					edge to_add_mono(*to_add, *stack_end_2);
					mono_edge.push_back(to_add_mono);
				}
			}
			stack.push_back(*to_add);
		}
		else {
			int back = *(stack.end() - 1);
			for (auto s = stack.begin() + 1; s < stack.end(); s++) {
				edge to_add_mono(*to_add, *s);
				mono_edge.push_back(to_add_mono);
			}
			stack.clear();
			stack.push_back(back);
			stack.push_back(*to_add);
			stack_status = point_status;
		}
	}
	if (stack.size() > 2) {
		for (int i = 1; i < stack.size() - 1; i++) {
			edge to_add_mono(*left, stack.at(i));
			mono_edge.push_back(to_add_mono);
		}
	}
}

void add_node(int a, int b, std::vector<circle_node>& table, triangle* &parent, bool is_lc, int not_this, std::vector<triangle*>& dual_tree) {
	int next = find_common(table.at(a).relation, table.at(b).relation, not_this);
	triangle* to_add = new triangle(a, b, next);
	to_add->par = parent;
	(is_lc ? parent->lc : parent->rc) = to_add;
	dual_tree.push_back(to_add);
	if (a != (next + 1 + table.size()) % table.size() && a != (next - 1 + table.size()) % table.size())add_node(a, next, table, to_add, 0, b, dual_tree);
	if (b != (next + 1 + table.size()) % table.size() && b != (next - 1 + table.size()) % table.size())add_node(b, next, table, to_add, 1, a, dual_tree);
	return;
}