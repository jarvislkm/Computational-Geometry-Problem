#include "interval_tree_node.h"
#include "func.h"
#include <algorithm>

IntervalTreeNode::IntervalTreeNode(std::vector<Segment> seg_vec) {
	std::vector<Point> point_vec;
	for (auto s : seg_vec) {
		point_vec.push_back(s.p1);
		point_vec.push_back(s.p2);
	}
	sort(point_vec.begin(), point_vec.end(), CompareX);
	position = point_vec.at(point_vec.size() / 2).x;
	std::vector<Segment> left_seg, right_seg;
	std::vector<Point> left_point, right_point;
	for (auto s : seg_vec) {
		if (s.p1.x > position) { right_seg.push_back(s); }
		else if (s.p2.x < position) { left_seg.push_back(s); }
		else {
			left_point.push_back(s.p1);
			right_point.push_back(s.p2);
		}
	}
	number = left_point.size();
	sort(left_point.begin(), left_point.end(), CompareX);
	sort(right_point.begin(), right_point.end(), CompareX);
	range_left = new RangeTree(left_point);
	range_right = new RangeTree(right_point);
	if (left_seg.size()) {
		lc = new IntervalTreeNode(left_seg);
	}
	else lc = NULL;
	if (right_seg.size()) {
		rc = new IntervalTreeNode(right_seg);
	}
	else rc = NULL;
}

void IntervalTreeNode::Remove() {
	if (lc) {
		lc->Remove();
		delete lc;
	}
	if (rc) {
		rc->Remove();
		delete rc;
	}
}

IntervalTreeNode::~IntervalTreeNode() {
	delete range_left;
	delete range_right;
}

std::vector<long> IntervalTreeNode::find_left(double x, double y_up, double y_low){
	range_left->QueryRange(Point(kMinValue, y_low), Point(x, y_up));
	return range_left->point_id;
}

std::vector<long> IntervalTreeNode::find_right(double x, double y_up, double y_low) {
	range_right->QueryRange(Point(x, y_low), Point(kMaxValue, y_up));
	return range_right->point_id;
}