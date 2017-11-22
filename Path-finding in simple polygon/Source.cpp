#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "Point.h"
#include "Segment.h"
#include "Node.h"
#include "Tree.h"
using namespace std;
point start_point;
point end_point;

struct edge {
	edge(int aa, int bb) {
		if (aa > bb) { a = aa; b = bb; }
		else { a = bb; b = aa; }
	}
	int a;
	int b;
	int distance;
};
vector<edge> mono_edge;
struct circle_node {
	int num;
	bool enable;
	vector<int> relation;
};
struct triangle {
	triangle(int aa,int bb,int cc):a(aa),b(bb),c(cc){};
	int a;
	int b;
	int c;
	triangle* par = NULL;
	triangle* lc = NULL;
	triangle* rc = NULL;
	int position;
};
vector<triangle*> dual_tree;

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

bool start_point_in_triangle(int count, vector<point*>& mo_point) {
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

bool end_point_in_triangle(int count, vector<point*>& mo_point) {
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

void handle_monotone(vector<int>number, vector<point*>& mo_point) {
	auto max = number.begin();
	auto min = number.begin();
	for (auto s = number.begin(); s < number.end();s++) {
		if (*mo_point.at(*s) > *mo_point.at(*max)) max = s;
		if (*mo_point.at(*s) < *mo_point.at(*min)) min = s;
	}
	auto right = max;
	auto left = max;
	if (max+1 == number.end()) {
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
	vector<int> stack;
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
				edge to_add_mono(*to_add,*s);
				mono_edge.push_back(to_add_mono);
			}
			stack.clear();
			stack.push_back(back);
			stack.push_back(*to_add);
			stack_status = point_status;
		}
	}
	if (stack.size() > 2) {
		for (int i = 1; i < stack.size()-1; i++) {
			edge to_add_mono(*left, stack.at(i));
			mono_edge.push_back(to_add_mono);
		}
	}
}

void traverse(triangle* root) {
	if(root->lc) traverse(root->lc);
	cout << root->a << " " << root->b << " " << root->c << endl;
	if (root->rc) traverse(root->rc);
}

int read(vector<point*>&p) {
	int size;
	point* point_to_add;
	cin >> start_point.x >> start_point.y;
	cin >> end_point.x >> end_point.y;
	int count = 0;
	int x;
	int y;
	cin >> size;
	while (count <size) {
		cin >>x >>y;
		point_to_add = new point(x,y,count);
		p.push_back(point_to_add);
		count++;
	}
	return size;
}

int find_common(vector<int> &a,vector<int>&b, int not_this) {
	int i = 0;
	int j = 0;
	while (a.at(i) != b.at(j) || a.at(i)==not_this) {
		if (a.at(i) < b.at(j)) i++;
		else j++;
	}
	return a.at(i);
}

void add_node(int a,int b, vector<circle_node>& table, triangle* &parent, bool is_lc, int not_this) {
	int next = find_common(table.at(a).relation, table.at(b).relation,not_this);
	triangle* to_add = new triangle(a, b, next);
	to_add->par = parent;
	(is_lc ? parent->lc : parent->rc) = to_add;
	dual_tree.push_back(to_add);
	if (a != (next + 1+ table.size()) % table.size() && a != (next - 1+ table.size()) % table.size())add_node(a, next, table, to_add, 0,b);
	if (b != (next + 1+ table.size()) % table.size() && b != (next - 1+ table.size()) % table.size())add_node(b, next, table, to_add, 1,a);
	return;
}

int main() {
	vector<point*> pointqueue;
	vector<edge> inter_edge;
	int size = read(pointqueue);
	pointqueue.at(0)->after = pointqueue.at(1);
	pointqueue.at(0)->before = pointqueue.at(size-1);
	pointqueue.at(size - 1)->after = pointqueue.at(0);
	pointqueue.at(size - 1)->before = pointqueue.at(size - 2);
	for (int i = 1; i < size - 1;i++) {
			pointqueue.at(i)->after = pointqueue.at(i+1);
			pointqueue.at(i)->before = pointqueue.at(i - 1);
	}
	sort(pointqueue.begin(),pointqueue.end(), compare_by_y);

	avl_tree status_tree;
	avl_node* tem,*tem2;
	for (auto p : pointqueue) {
		status_tree.position = p->y;
		if (*p > *(p->after) && *p > *(p->before)) {
			result r = status_tree.search_point(*p);
			if (r.find) {
				p->type = split;
				inter_edge.push_back({ p->num,r.node->helper.num });  //if helper is a  stalactile(merge); then both of them is satisfied;
				segment a1 = r.node->segm1;
				segment a2(*p, *(p->before));
				segment b1(*p, *(p->after));
				segment b2 = r.node->segm2;
				status_tree.delete_node(a1);
				tem = status_tree.add_node(a1, a2);
				tem->helper = *p;
				tem = status_tree.add_node(b1, b2);
				tem->helper = *p;
			}
			else {
				p->type = start;
				segment a1(*p, *(p->after));
				segment a2(*p, *(p->before));
				tem = status_tree.add_node(a1, a2);
				tem->helper = *p;
			}
		}
		else if (*p < *(p->after) && *p < *(p->before)) {
			segment tems1(*p, *(p->after));
			segment tems2(*p, *(p->before));
			tem = status_tree.search(tems1);
			tem2 = status_tree.search(tems2);
			if (tem == tem2) {
				p->type = ending;
				if (tem->helper.type == merging) { inter_edge.push_back({ p->num, tem->helper.num }); }
				status_tree.delete_node(tems1);
			}
			else {
				p->type = merging;
				tems1 = tem->segm1;
				tems2 = tem2->segm2;
				if (tem->helper.type == merging) { inter_edge.push_back({ p->num, tem->helper.num }); }
				if (tem2->helper.type == merging) { inter_edge.push_back({ p->num, tem2->helper.num }); }
				status_tree.delete_node(tems1);
				status_tree.delete_node(tems2);
				tem = status_tree.add_node(tems1, tems2);
				tem->helper = *p;
			}
		}
		else if (*(p->before) > *p && *p> *(p->after)) {
			p->type = regular_left;
			segment tems1(*p, *(p->before));
			segment tems2(*p, *(p->after));
			tem = status_tree.search(tems1);
			tem->segm1 = tems2;
			if (tem->helper.type == merging) { inter_edge.push_back({ p->num, tem->helper.num}); }
			tem->helper = *p;
		}
		else if (*(p->before) < *p && *p< *(p->after)){
			p->type = regular_right;
			segment tems1(*p, *(p->before));
			segment tems2(*p, *(p->after));
			tem = status_tree.search(tems2);
			tem->segm2 = tems1;
			if (tem->helper.type == merging) { inter_edge.push_back({ p->num, tem->helper.num }); }
			tem->helper = *p;
		}
	}
	//for (auto p : pointqueue) {
	//	cout << p->num << "  " << p->type<<endl;
	//}
	for (auto& p : inter_edge) {
		p.distance = min(p.a - p.b, p.b + size - p.a);
	}
	sort(inter_edge.begin(), inter_edge.end(), compare);
	vector<circle_node> circle;
	for (int i = 0; i < size; i++) {
		circle.push_back({ i,true });
	}
	
	sort(pointqueue.begin(), pointqueue.end(), compare_by_num);
	vector<int> point_in_monotone;
	for (auto& p : inter_edge) {
		point_in_monotone.push_back(p.b);
		if (p.a - p.b == p.distance) {
			for (int i = p.b + 1; i < p.a; i++) {
				if (circle.at(i).enable) {
					point_in_monotone.push_back(i);
					circle.at(i).enable = false;
				}
			}
		}
		else {
			for (int i = p.b-1+size ; i > p.a; i--) {
				int ii = (i >= size) ? i - size : i;
				if (circle.at(ii).enable) {
					point_in_monotone.push_back(ii);
					circle.at(ii).enable = false;
				}
			}
			reverse(point_in_monotone.begin(), point_in_monotone.end());
		}
		point_in_monotone.push_back(p.a);
		handle_monotone(point_in_monotone, pointqueue);
		point_in_monotone.clear();
	}
	for (auto s : circle) {
		if (s.enable) point_in_monotone.push_back(s.num);
	}
	handle_monotone(point_in_monotone, pointqueue);
	// start to generate dual tree
	mono_edge.insert(mono_edge.end(), inter_edge.begin(), inter_edge.end());
	for (auto one_edge : mono_edge) {
		circle.at(one_edge.a).relation.push_back(one_edge.b);
		circle.at(one_edge.b).relation.push_back(one_edge.a);
	}
	//find start point which have no inter edge
	int start_at=0;
	while (circle.at(start_at).relation.size()) { start_at++; }
	for (int i = 1; i < size - 1; i++) {
		circle.at(i).relation.push_back(i - 1);
		circle.at(i).relation.push_back(i + 1);
	}
	circle.at(0).relation.push_back(1);
	circle.at(0).relation.push_back(size-1);
	circle.at(size-1).relation.push_back(0);
	circle.at(size - 1).relation.push_back(size-2);

	for (int i = 0; i < size; i++) {
		sort(circle.at(i).relation.begin(), circle.at(i).relation.end());
	}
	triangle* root = new triangle(start_at, circle.at(start_at).relation.at(0), circle.at(start_at).relation.at(1));
	dual_tree.push_back(root); //find the starting triangle and start to explore others
	add_node(circle.at(start_at).relation.at(0), circle.at(start_at).relation.at(1), circle, root, 0, start_at);
	// sort each node for later comparasion
	for (int i = 0; i < dual_tree.size();i++) {
		dual_tree.at(i)->position = i;
	}
	//end building dual tree
	//find triangle of start and end point
	int count = 0;
	while (!start_point_in_triangle(count, pointqueue)) { count++; };
	triangle* start = dual_tree.at(count);
	count = 0;
	while (!end_point_in_triangle(count, pointqueue)) { count++; };
	triangle* end = dual_tree.at(count);
	vector<int> start_sequence,end_sequence;
	while (start) {
		start_sequence.push_back(start->position);
		start = start->par;
	}
	while (end) {
		end_sequence.push_back(end->position);
		end = end->par;
	}
	int ss = start_sequence.size()-1;
	int es = end_sequence.size()-1;
	while (ss>=0 && es>=0 && start_sequence.at(ss) == end_sequence.at(es)) {
		ss--;
		es--;
	}
	if(start_sequence.size()>1) start_sequence.erase(start_sequence.begin() + (2+ss), start_sequence.end());
	end_sequence.erase(end_sequence.begin() + (1+es), end_sequence.end());
	if (end_sequence.size()) {
		reverse(end_sequence.begin(), end_sequence.end());
		start_sequence.insert(start_sequence.end(), end_sequence.begin(), end_sequence.end());
	}

	//start finding the proper cusp. method from network paper;
	vector<int> cusp_record;
	vector<int> cusp_status;
	point* cusp_point = &start_point;
	point* tend_point = &end_point;
	pointqueue.push_back(tend_point);
	pointqueue.push_back(cusp_point);

	if (start_sequence.size()>1) {
		edge d = find_edge(dual_tree.at(start_sequence.at(0)), dual_tree.at(start_sequence.at(1)));
		if (to_left(*pointqueue.at(d.a), *pointqueue.at(d.b), *cusp_point)<=0) { int swap_d = d.a; d.a = d.b; d.b = swap_d; };
		cusp_status.push_back(d.a);
		cusp_status.push_back(pointqueue.size() - 1); //last point in cusp_status is start point
		cusp_status.push_back(d.b);
		bool added_edge_same_side = false;
		edge record = d;
		int adjust = -1;
		for (int i = 1; i < start_sequence.size(); i++) {
			if (i < start_sequence.size() - 1) {
				d = find_edge(dual_tree.at(start_sequence.at(i)), dual_tree.at(start_sequence.at(i + 1)));
			}
			else { d.a = record.a; d.b = int(pointqueue.size() - 2); }

//			if (i == start_sequence.size() - 1 && added_edge_same_side) {
//				cusp_status.pop_back();
//				cusp_status.push_back(pointqueue.size() - 2);
//				break;
//			}

			int common_point_in_edge = find_commom_point_in_edge(d, record);
			record = d;
			int new_point = (d.a == common_point_in_edge ? d.b : d.a);

			if (added_edge_same_side) {
				if (common_point_in_edge == cusp_status.at(0)) {
					cusp_point = pointqueue.at(cusp_status.at(1));
					cusp_record.push_back(cusp_status.at(1));
					cusp_status.push_back(new_point);
					added_edge_same_side = false;
				}
				else {
					cusp_status.at(0) = new_point;
				}
				continue;
			}

				if (common_point_in_edge == cusp_status.at(0)) {
					reverse(cusp_status.begin(), cusp_status.end());
					adjust *= -1;
				}
				int j = 0;
				bool right_side_of_cusp_status = true;
				bool on_left_line_right = true;
				int left_line_count = cusp_status.size() - 1;
				bool below_bottom_line;
				//if (added_edge_same_side == true && common_point_in_edge != cusp_status.at(cusp_status.size() - 1)) {
				//	below_bottom_line = (adjust*to_left(*pointqueue.at(cusp_status.at(0)), *pointqueue.at(cusp_status.at(cusp_status.size() - 2)), *pointqueue.at(new_point)) >= 0);
				//}
				//else below_bottom_line = (adjust*to_left(*pointqueue.at(cusp_status.at(0)), *pointqueue.at(cusp_status.at(cusp_status.size() - 1)), *pointqueue.at(new_point)) >=0);
				// Three category, right of the left line; left of the left line and below the bottom line; higher than bottom line.
				while (adjust*to_left(*pointqueue.at(cusp_status.at(left_line_count)), *pointqueue.at(cusp_status.at(left_line_count - 1)), *pointqueue.at(new_point)) >= 0) {
					left_line_count--;
					if (*pointqueue.at(cusp_status.at(left_line_count)) == *cusp_point) { on_left_line_right = false; break; }
				}

				if (on_left_line_right) {
					while (j < cusp_status.size() - 2 && !(right_side_of_cusp_status ^ adjust*to_left(*pointqueue.at(cusp_status.at(j)), *pointqueue.at(cusp_status.at(j + 1)), *pointqueue.at(new_point)) >= 0)) {
						j++;
						if (right_side_of_cusp_status == 0) {
							cusp_point = pointqueue.at(cusp_status.at(j));
							cusp_record.push_back(cusp_status.at(j));
						}
						if (*pointqueue.at(cusp_status.at(j)) == *cusp_point) {
							right_side_of_cusp_status = 0;
						}
					}
					cusp_status.erase(cusp_status.begin(), cusp_status.begin() + j);
					cusp_status.insert(cusp_status.begin(), new_point);
					added_edge_same_side = false;
				}
				//else if (below_bottom_line) {
				//	if (cusp_status.at(cusp_status.size() - 1) == common_point_in_edge || cusp_status.at(0) == common_point_in_edge) {
				//		cusp_status.push_back(new_point);
				//		added_edge_same_side = true;
				//	}
				//	else {
				//		cusp_status.pop_back();
				//		cusp_status.push_back(new_point);
				//		added_edge_same_side = true;
				//	}
				//}
				else {
					int count_cusp = 0;
					while (!(*pointqueue.at(cusp_status.at(count_cusp)) == *cusp_point)) { count_cusp++; }
					count_cusp++;
					for (int s = count_cusp; s < cusp_status.size() - 1; s++) {
						cusp_record.push_back(cusp_status.at(s));
					}
					cusp_status.erase(cusp_status.begin(), cusp_status.end() - 1);

	//				reverse(cusp_status.begin(), cusp_status.end());
	//				cusp_point = pointqueue.at(cusp_status.at(0));
	//				cusp_record.push_back(cusp_status.at(0));
					cusp_status.insert(cusp_status.begin(), new_point);
					added_edge_same_side = true;
				}
			}
		if (cusp_status.at(0) + 2 != pointqueue.size()) reverse(cusp_status.begin(), cusp_status.end());
		auto cusp_to_add = cusp_status.begin();
		if (added_edge_same_side) cusp_record.push_back(cusp_status.at(1));
		else {
			vector<int> latter_part;
			while (pointqueue.at(*++cusp_to_add) != cusp_point) { latter_part.push_back(*cusp_to_add); }
			reverse(latter_part.begin(), latter_part.end());
			cusp_record.insert(cusp_record.end(), latter_part.begin(), latter_part.end());
		}
	}
	cusp_record.erase(unique(cusp_record.begin(), cusp_record.end()),cusp_record.end());
	
	cout << "s" << endl;
	for (auto p : cusp_record) {
		cout << p<<endl;
	}
	cout << "e" << endl;

	pointqueue.pop_back();
	pointqueue.pop_back();
	for (auto s : pointqueue) {
		delete s;
	}
	for (auto s : dual_tree) {
		delete s;
	}
	return 0;
}