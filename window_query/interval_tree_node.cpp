#include "interval_tree_node.h"
#include "func.h"
#include <algorithm>
using namespace std;
it_node::it_node(vector<segment> seg_vec) {
	vector<point> point_vec;
	for (auto s : seg_vec) {
		point_vec.push_back(s.p1);
		point_vec.push_back(s.p2);
	}
	sort(point_vec.begin(), point_vec.end(), compare_x);
	position = point_vec.at(point_vec.size() / 2).x;
	vector<segment> left_seg, right_seg;
	vector<point> left_point, right_point;
	for (auto s : seg_vec) {
		if (s.p1.x > position) { right_seg.push_back(s); }
		else if (s.p2.x < position) { left_seg.push_back(s); }
		else {
			left_point.push_back(s.p1);
			right_point.push_back(s.p2);
		}
	}
	number = left_point.size();
	sort(left_point.begin(), left_point.end(), compare_x);
	sort(right_point.begin(), right_point.end(), compare_x);
	range_left = new range_tree(left_point);
	range_right = new range_tree(right_point);
	if (left_seg.size()) {
		lc = new it_node(left_seg);
	}
	else lc = NULL;
	if (right_seg.size()) {
		rc = new it_node(right_seg);
	}
	else rc = NULL;
}

vector<long> it_node::find_left(double x, double y_up, double y_low){
	range_left->range(point(min_v, y_low), point(x, y_up));
	return range_left->point_id;
}

vector<long> it_node::find_right(double x, double y_up, double y_low) {
	range_right->range(point(x, y_low), point(max_v, y_up));
	return range_right->point_id;
}