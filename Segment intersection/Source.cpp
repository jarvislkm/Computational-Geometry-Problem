#include <stdio.h>
#include <tchar.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

#include "Header.h"
#include "Point.h"
#include "Segment.h"
#include "Event.h"
#include "Eventqueue.h"
#include "Avlnode.h"
#include "Avltree.h"
#include "func.h"
using namespace std;
point tem_cal;
point tem_cal2;
class event_intersection_list {
public:
	std::vector<segment> segment_list;
	point intersection_point;
};

double read(int & S, int &R, int &L, int &C, eventqueue &eq, std::vector<segment*> &left) {
	ifstream in;
	in.open("data.txt");
	in >> S >> R >> L >> C;
	point tem1, tem2;
	double r;
	double xholdmin = 0;
	double xholdmax = 0;
	event* newevent = NULL;
	std::vector<segment*> ray_tem_vec;
	std::vector<segment*> line_tem_vec;
	segment* ray_tem;
	segment* line_tem;
	// read segment
	int itr = S;
	while (itr-- > 0) {
		in >> tem1.x >> tem1.y >> tem2.x >> tem2.y;
		if (tem1.vert(tem2)) {
			if (tem1 < tem2) {
				segment ts(tem1, tem2);
				newevent = new event(verticle_line_open, ts);
				eq.insert(newevent);
				newevent = new event(verticle_line_close, ts);
				eq.insert(newevent);
				if (xholdmin > tem1.x) xholdmin = tem1.x;
				if (xholdmax < tem2.x) xholdmax = tem2.x;
			}
			else {
				segment ts(tem2, tem1);
				newevent = new event(verticle_line_open, ts);
				eq.insert(newevent);
				newevent = new event(verticle_line_close, ts);
				eq.insert(newevent);
				if (xholdmin > tem2.x) xholdmin = tem2.x;
				if (xholdmax < tem1.x) xholdmax = tem1.x;
			}
		}
		else if (tem1 < tem2) {
			segment ts(tem1, tem2);
			newevent = new event(insert_seg, ts);
			eq.insert(newevent);
			newevent = new event(remove_seg, ts);
			eq.insert(newevent);
			if (xholdmin > tem1.x) xholdmin = tem1.x;
			if (xholdmax < tem2.x) xholdmax = tem2.x;
		}
		else {
			segment ts(tem2, tem1);
			newevent = new event(insert_seg, ts);
			eq.insert(newevent);
			newevent = new event(remove_seg, ts);
			eq.insert(newevent);
			if (xholdmin > tem2.x) xholdmin = tem2.x;
			if (xholdmax < tem1.x) xholdmax = tem1.x;
		}
	}
	//read ray; traverse first to find xholdmin; make sure all start point is on right side of xholdmin;
	itr = R;
	while (itr-- > 0) {
		in >> tem1.x >> tem1.y >> tem2.x >> tem2.y;
		ray_tem = new segment(tem1, tem2, ray);
		if (xholdmin > tem1.x) xholdmin = tem1.x;
		if (xholdmax < tem1.x) xholdmax = tem1.x;
		ray_tem_vec.push_back(ray_tem);
	}
	//read line;
	itr = L;
	while (itr-- > 0) {
		in >> tem1.x >> tem1.y >> tem2.x >> tem2.y;
		line_tem = new segment(tem1, tem2, line);
		line_tem_vec.push_back(line_tem);
	}

	itr = C;
	while (itr-- > 0) {
		in >> tem1.x >> tem1.y >> r;
		tem2.x = tem1.x + r;
		tem2.y = tem1.y;
		tem1.x -= r;
		if (xholdmin > tem1.x) xholdmin = tem1.x;
		if (xholdmax < tem1.x) xholdmax = tem1.x;
		segment ts(tem1, tem2, circle_upper);
		segment ts2(tem1, tem2, circle_lower);
		newevent = new event(insert_seg, ts);
		eq.insert(newevent);
		newevent = new event(insert_seg, ts2);
		eq.insert(newevent);
		newevent = new event(remove_seg, ts);
		eq.insert(newevent);
		newevent = new event(remove_seg, ts2);
		eq.insert(newevent);
	}
	xholdmin = xholdmin - 0.5;
	xholdmax = xholdmax + 0.5;
	for (auto ray_t : ray_tem_vec) {
		if (ray_t->left_end.vert(ray_t->right_end)) {
			if (ray_t->left_end < ray_t->right_end) {
				ray_t->right_end.y = -1e12;
				segment ts(*ray_t);
				newevent = new event(verticle_line_open, ts);
				eq.insert(newevent);
				newevent = new event(verticle_line_close, ts);
				eq.insert(newevent);
			}
			else {
				ray_t->right_end.y = 1e12;
				segment ts(ray_t->right_end, ray_t->left_end);
				newevent = new event(verticle_line_open, ts);
				eq.insert(newevent);
				newevent = new event(verticle_line_close, ts);
				eq.insert(newevent);
			}
			delete ray_t;
		}
		else if (ray_t->left_end < ray_t->right_end) {
			double max = ray_t->at(xholdmax);
			ray_t->right_end.x = xholdmax;
			ray_t->right_end.y = max;
			segment tem_r(*ray_t);
			delete ray_t;
			newevent = new event(insert_seg, tem_r);
			eq.insert(newevent);
		}
		else {
			point tp(xholdmin, ray_t->at(xholdmin));
			segment ts(tp, ray_t->left_end);
			newevent = new event(insert_seg, ts);    //segment
			eq.insert(newevent);
			newevent = new event(remove_seg, ts);
			eq.insert(newevent);
			left.push_back(ray_t);
		}
	}
	for (auto line_t : line_tem_vec) {
		if (line_t->left_end.vert(line_t->right_end)) {
			if (line_t->left_end.x < xholdmin) {
				left.push_back(line_t);
			}
			else {
				tem1.x = tem2.x = line_t->left_end.x;
				tem1.y = 1e12;
				tem2.y = -1e12;
				segment ts(tem1, tem2);
				newevent = new event(verticle_line_open, ts);
				eq.insert(newevent);
				newevent = new event(verticle_line_close, ts);
				eq.insert(newevent);
				delete line_t;
			}
		}
		else {
			point tp1(xholdmin, line_t->at(xholdmin));
			point tp2(xholdmax, line_t->at(xholdmax));
			segment ts(tp1, tp2, ray);
			newevent = new event(insert_seg, ts);
			eq.insert(newevent);
			left.push_back(line_t);
		}
	}
	return xholdmin;
}

void write(std::vector<point*> result) {
	ofstream out;
	out.open("result.txt");
	for (auto p : result) {
		out << *p;
	}
	out.close();
}

int main()
{
	eventqueue eq;
	std::vector<segment*> left;
	avl_tree status_tree;
	point point_now;
	int point_count = 1;
	point* tem_point;
	int S, R, L, C;
	status_tree.position = read(S, R, L, C, eq, left);

	std::vector<point*> result;
	int event_count = 0;
	avl_node* now = NULL;
	event* event_to_add = NULL;
	point* point_to_add = NULL;
	avl_node* n1 = NULL;
	avl_node* n2 = NULL;
	avl_node* verticle_start = NULL;
	avl_node* record = NULL;
	avl_node* delete_pre = NULL;
	event* handle = NULL;
	segment ss1;
	segment ss2;
	int intersection_in_left = 0;
	double max, min;
	int cal_number = 0;
	bool this_point_delete = false;
	int verticle_signal = 0;

	event_intersection_list inter_list;

	while (left.size() > 0) {
		auto left_seg = left.at(left.size() - 1);
		for (auto rest = left.begin(); rest < left.end() - 1; rest++) {
			if (is_zero(to_left(left_seg->left_end, left_seg->right_end, (*rest)->left_end) - to_left(left_seg->left_end, left_seg->right_end, (*rest)->right_end))) {//if parallel
				continue;
			}
			if (left_seg->left_end.vert(left_seg->right_end)) {// verticle line
				point_to_add = new point(left_seg->left_end.x, (*rest)->at(left_seg->left_end.x));
				result.push_back(point_to_add);
			}
			else if ((*rest)->left_end.vert((*rest)->right_end)) {
				point_to_add = new point((*rest)->right_end.x, left_seg->at((*rest)->right_end.x));
				result.push_back(point_to_add);
			}
			else {
				double denominator = ((*rest)->left_end.x - (*rest)->right_end.x)*(left_seg->left_end.y - left_seg->right_end.y) -
					(left_seg->left_end.x - left_seg->right_end.x)*((*rest)->left_end.y - (*rest)->right_end.y);
				double numerator = (left_seg->left_end.x - left_seg->right_end.x)*((*rest)->right_end.y - left_seg->right_end.y) -
					(left_seg->left_end.y - left_seg->right_end.y)*((*rest)->right_end.x - left_seg->right_end.x);
				double x = ((*rest)->left_end.x - (*rest)->right_end.x)*numerator / denominator + (*rest)->right_end.x;
				double y = ((*rest)->left_end.y - (*rest)->right_end.y)*numerator / denominator + (*rest)->right_end.y;
				if (x < status_tree.position) { // if in left
					point_to_add = new point(x, y);
					result.push_back(point_to_add);
				}
			}
		}
		left.pop_back();
	}

	while (eq.queue.size() != 0) {
		handle = eq.delMax();
		if (!(handle->event_posi == point_now)) {  //point_now is the working event point
			point_count = 1;
			this_point_delete = false;
			point_now = handle->event_posi;
		}
		else point_count++;
		switch (handle->type)
		{
		case verticle_line_open:
			status_tree.position = handle->event_posi.x;
			verticle_start = status_tree.root;
			if (verticle_signal) {
				point_to_add = new point(handle->s1.left_end);
				result.push_back(point_to_add);
			}
			max = handle->s1.left_end.y;
			min = handle->s1.right_end.y;
			while (verticle_start) {
				record = verticle_start;
				if (verticle_start->segm.at(handle->event_posi.x) < max) {
					verticle_start = verticle_start->rc;
				}
				else verticle_start = verticle_start->lc;
			}
			if (record) verticle_start = record;
			if (verticle_start && verticle_start->segm.at(handle->event_posi.x) > max) { verticle_start = verticle_start->pre(); } // find largest point below max
			if (verticle_start && verticle_start->succ() && verticle_start->succ()->segm.at(handle->event_posi.x) <= max)
			{
				verticle_start = verticle_start->succ();
			}
			while (verticle_start && verticle_start->segm.at(handle->event_posi.x) >= min &&verticle_start->segm.at(handle->event_posi.x) <= max) {
				point_to_add = new point(handle->event_posi.x, verticle_start->segm.at(handle->event_posi.x));
				result.push_back(point_to_add);
				verticle_start = verticle_start->pre();
			}
			verticle_signal += 1;
			break;
		case verticle_line_close:
			verticle_signal -= 1;
			break;
		case insert_seg:
			if (this_point_delete || verticle_signal) { // if verticle line open or delete point
				tem_point = new point(handle->event_posi);
				result.push_back(tem_point);
			}
			status_tree.position = handle->event_posi.x;
			now = status_tree.add_node(handle->s1);
			if (detection_pre(now) && (cal_number = cal_intersection(now, now->pre()))) {
				if (tem_cal.x >= handle->event_posi.x) {
					if (is_zero(tem_cal.x - handle->event_posi.x)) {
						tem_point = new point(handle->event_posi);
						result.push_back(tem_point);
					}
					else {
						event_to_add = new event(intersection, now->pre()->segm, tem_cal);
						eq.insert(event_to_add);
						event_to_add = new event(intersection, now->segm, tem_cal);
						eq.insert(event_to_add);
					}
				}
				if (cal_number == 2 && tem_cal2.x>handle->event_posi.x) {
					event_to_add = new event(intersection, now->pre()->segm, tem_cal2);
					eq.insert(event_to_add);
					event_to_add = new event(intersection, now->segm, tem_cal2);
					eq.insert(event_to_add);
				}
			}
			if (detection_succ(now) && (cal_number = cal_intersection(now, now->succ()))) {
				if (tem_cal.x >= handle->event_posi.x) {
					if (is_zero(tem_cal.x - handle->event_posi.x)) {      // insert point is a intersection
						tem_point = new point(handle->event_posi);
						result.push_back(tem_point);
					}
					else {
						event_to_add = new event(intersection, now->segm, tem_cal);
						eq.insert(event_to_add);
						event_to_add = new event(intersection, now->succ()->segm, tem_cal);
						eq.insert(event_to_add);
					}
				}
				if (cal_number == 2 && tem_cal2.x>handle->event_posi.x) {
					event_to_add = new event(intersection, now->segm, tem_cal2);
					eq.insert(event_to_add);
					event_to_add = new event(intersection, now->succ()->segm, tem_cal2);
					eq.insert(event_to_add);
				}
			}
			break;
		case remove_seg:
			status_tree.position = handle->event_posi.x;
			delete_pre = status_tree.delete_node(handle->s1);
			if (delete_pre&& detection_succ(delete_pre) && (cal_number = cal_intersection(delete_pre, delete_pre->succ()))) {
				if (tem_cal.x > handle->event_posi.x) {
					event_to_add = new event(intersection, delete_pre->succ()->segm, tem_cal);
					eq.insert(event_to_add);
					event_to_add = new event(intersection, delete_pre->segm, tem_cal);
					eq.insert(event_to_add);
				}
				if (cal_number == 2 && tem_cal2.x>handle->event_posi.x) {
					event_to_add = new event(intersection, delete_pre->succ()->segm, tem_cal2);
					eq.insert(event_to_add);
					event_to_add = new event(intersection, delete_pre->segm, tem_cal2);
					eq.insert(event_to_add);
				}
			}
			this_point_delete = true;
			break;
		case intersection:
			status_tree.position = handle->event_posi.x;
			if (!inter_list.segment_list.size()) inter_list.intersection_point = handle->event_posi;    // set event point for first intersection
			if (inter_list.intersection_point == handle->event_posi) {
				if (status_tree.search(handle->s1, -0.001)) {
					inter_list.segment_list.push_back(handle->s1);
				}
			} // add if intersection point is same
			event_to_add = eq.getMax();
			if (event_to_add&&event_to_add->event_posi == inter_list.intersection_point && event_to_add->type == intersection) { break; } //if intersection still have same event point
			tem_point = new point(handle->event_posi);
			result.push_back(tem_point);
			for (auto s = inter_list.segment_list.begin(); s != inter_list.segment_list.end(); s++) { s->at(inter_list.intersection_point.x + 0.001); }// sorting in later sequence
			sort(inter_list.segment_list.begin(), inter_list.segment_list.end(), inter_compare);
			inter_list.segment_list.erase(unique(inter_list.segment_list.begin(), inter_list.segment_list.end()), inter_list.segment_list.end());
			if (!inter_list.segment_list.size()) break;
			n1 = status_tree.search(inter_list.segment_list.at(0), -0.001);
			while (n1->succ() && is_zero(n1->succ()->segm.at(handle->event_posi.x) - handle->event_posi.y)) {
				n1 = n1->succ();
			}
			n2 = n1;
			n1->segm = inter_list.segment_list.at(inter_list.segment_list.size() - 1);
			inter_list.segment_list.pop_back();
			while (inter_list.segment_list.size() > 0) {
				n1 = n1->pre();
				n1->segm = inter_list.segment_list.at(inter_list.segment_list.size() - 1);
				inter_list.segment_list.pop_back();
			}

			if (detection_pre(n1) && (cal_number = cal_intersection(n1, n1->pre()))) {
				if (tem_cal.x>handle->event_posi.x) {
					event_to_add = new event(intersection, n1->pre()->segm, tem_cal);
					eq.insert(event_to_add);
					event_to_add = new event(intersection, n1->segm, tem_cal);
					eq.insert(event_to_add);
				}
				if (cal_number == 2 && tem_cal2.x>handle->event_posi.x) {
					event_to_add = new event(intersection, n1->pre()->segm, tem_cal2);
					eq.insert(event_to_add);
					event_to_add = new event(intersection, n1->segm, tem_cal2);
					eq.insert(event_to_add);
				}
			}
			if (detection_succ(n2) && (cal_number = cal_intersection(n2, n2->succ()))) {
				if (tem_cal.x > handle->event_posi.x) {
					event_to_add = new event(intersection, n2->segm, tem_cal);
					eq.insert(event_to_add);
					event_to_add = new event(intersection, n2->succ()->segm, tem_cal);
					eq.insert(event_to_add);
				}
				if (cal_number == 2 && tem_cal2.x>handle->event_posi.x) {
					event_to_add = new event(intersection, n2->segm, tem_cal2);
					eq.insert(event_to_add);
					event_to_add = new event(intersection, n2->succ()->segm, tem_cal2);
					eq.insert(event_to_add);
				}
			}
			inter_list.segment_list.clear();
			break;
		default:
			break;
		}
		cout << "This is event: " << ++event_count << " operation type: " << handle->type << " line type: " << handle->s1.type << " posi:" << handle->event_posi << endl;
		status_tree.traverse(status_tree.root);
		for (auto re : result) {
			cout << *re;
		}
		cout << endl;
		delete handle;
	}
	sort(result.begin(), result.end(), left_comp);
	result.erase(unique(result.begin(), result.end(), left_unique), result.end());
	intersection_in_left = result.size();
	cout << intersection_in_left;
	write(result);
	for (auto re : result) {
		delete re;
	}
	return 0;
}

