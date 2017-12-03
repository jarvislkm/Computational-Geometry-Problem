#pragma once

#include "func.h"
#include "Segment.h"
#include "Avlnode.h"
#include "Point.h"

int max(int a, int b) { return (a > b ? a : b); }

bool is_zero(double s) {
	if (s<1e-8 && s>-1e-8) {
		return true;
	}
	else return false;
}

bool inter_compare(segment s1, segment s2) {
	return s1.temp < s2.temp;
}

void swap_seg(avl_node &a, avl_node &b) {
	segment t(a.segm);
	a.segm = b.segm;
	b.segm = t;
};

double dis(point& a, point &b) {
	double dx = a.x - b.x;
	double dy = a.y - b.y;
	return sqrt(dx*dx + dy*dy);
}

double to_left(point a, point b, point c) {
	double tem1 = a.x*b.y + b.x*c.y + c.x*a.y - b.y*c.x - c.y*a.x - a.y*b.x;
	if (is_zero(tem1)) {
		tem1 = 0;
	}
	return tem1;
}

bool left_comp(point* a, point*b) {
	if ((*a) < (*b)) return true;
	else return false;
};

bool left_unique(point* a, point*b) {
	if ((*a) == (*b)) return true;
	else return false;
}

bool is_intersection(avl_node* a, avl_node*b) {
	if (a->segm.type == ray && b->segm.type == ray) {
		if (is_zero(to_left(a->segm.left_end, a->segm.right_end, b->segm.left_end) - to_left(a->segm.left_end, a->segm.right_end, b->segm.right_end))) {
			return false;
		}
		else return true;
	}//if both ray;
	if (a->segm.type >= circle_upper && b->segm.type >= circle_upper) {
		double tempp1 = (a->segm.center - b->segm.center);
		double tempp2 = (a->segm.left_end.y - b->segm.right_end.y);
		if ((tempp1 || tempp2) && sqrt(tempp1*tempp1 + tempp2*tempp2) < (a->segm.r + b->segm.r + 1e-8)) { return true; }
		else return false;
	}// no intersection if share same center;
	else if (a->segm.type >= circle_upper) {
		point tem_po(a->segm.center, a->segm.left_end.y);
		double area = to_left(b->segm.left_end, b->segm.right_end, tem_po);
		if (area < 0) area = -area;
		double length = dis(b->segm.left_end, b->segm.right_end);
		if (a->segm.r > area / length - 1e-8) { return true; }
		else return false;
	}
	else if (b->segm.type >= circle_upper) {
		point tem_po(b->segm.center, b->segm.left_end.y);
		double area = to_left(a->segm.left_end, a->segm.right_end, tem_po);
		if (area < 0) area = -area;
		double length = dis(a->segm.left_end, a->segm.right_end);
		if (b->segm.r > area / length - 1e-8) { return true; }
		else return false;
	}
	double t1 = to_left(a->segm.left_end, a->segm.right_end, b->segm.left_end)*to_left(a->segm.left_end, a->segm.right_end, b->segm.right_end);
	double t2 = to_left(b->segm.left_end, b->segm.right_end, a->segm.left_end)*to_left(b->segm.left_end, b->segm.right_end, a->segm.right_end);
	//if (t1 == 0 && t2 == 0) return false;   //remove at same point
	if (t1 <= 0 &&  // if one end is on the nother segment, still front as intersection
		t2 <= 0) {
		return true;
	}
	else return false;
}
int cal_intersection(avl_node* a, avl_node*b) {
	bool swap_sig = false;
	if (a->segm.type >= circle_upper && b->segm.type >= circle_upper) {
		if (a->segm.center > b->segm.center) {
			swap_seg(*a, *b);
			swap_sig = true;
		}
		point tp1(a->segm.center, a->segm.left_end.y);
		point tp2(b->segm.center, b->segm.left_end.y);
		double d = dis(tp1, tp2);
		double s = (a->segm.r*a->segm.r - b->segm.r*b->segm.r + d*d) / (2 * d);
		double l = sqrt(a->segm.r*a->segm.r - s*s);
		double angle = atan((b->segm.left_end.y - a->segm.left_end.y) / (b->segm.center - a->segm.center));
		double dx1 = a->segm.center + (s*cos(angle) + l*sin(angle));
		double dx2 = a->segm.center + (s*cos(angle) - l*sin(angle));
		double dy1 = a->segm.left_end.y - l*cos(angle) + s*sin(angle);
		double dy2 = a->segm.left_end.y + l*cos(angle) + s*sin(angle);
		int num = 0;
		if ((a->segm.type == circle_upper && dy1 >= a->segm.left_end.y) || (a->segm.type == circle_lower && dy1 <= a->segm.left_end.y)) {
			if ((b->segm.type == circle_upper && dy1 >= b->segm.left_end.y) || (b->segm.type == circle_lower && dy1 <= b->segm.left_end.y)) {
				tem_cal.x = dx1;
				tem_cal.y = dy1;
				num++;
				if (is_zero(dx1 - dx2) && is_zero(dy1 - dy2)) { if (swap_sig) { swap_seg(*a, *b); } return num; }
			}
		}
		if ((a->segm.type == circle_upper && dy2 >= a->segm.left_end.y) || (a->segm.type == circle_lower && dy2 <= a->segm.left_end.y)) {
			if ((b->segm.type == circle_upper && dy2 >= b->segm.left_end.y) || (b->segm.type == circle_lower && dy2 <= b->segm.left_end.y)) {
				if (num == 1) {
					tem_cal2.x = dx2;
					tem_cal2.y = dy2;
				}
				else {
					tem_cal.x = dx2;
					tem_cal.y = dy2;
				}
				num++;
			}
		}
		if (swap_sig) { swap_seg(*a, *b); }
		return num;
	}
	if (b->segm.type >= circle_upper) {
		swap_seg(*a, *b);
		swap_sig = true;
	}
	if (a->segm.type >= circle_upper) {
		double distance = dis(b->segm.left_end, b->segm.right_end);
		point tp(a->segm.center, a->segm.left_end.y);
		double area = to_left(b->segm.left_end, b->segm.right_end, tp);
		double s = -area / distance;
		double angle = atan((b->segm.right_end.y - b->segm.left_end.y) / (b->segm.right_end.x - b->segm.left_end.x));
		double l = sqrt(a->segm.r*a->segm.r - s*s);
		double dx2 = a->segm.center - s*sin(angle) + l*cos(angle);   // dx1<=dx2
		double dx1 = a->segm.center - s*sin(angle) - l*cos(angle);
		double dy2 = a->segm.left_end.y + s*cos(angle) + l*sin(angle);
		double dy1 = a->segm.left_end.y + s*cos(angle) - l*sin(angle);
		int num = 0;
		if ((a->segm.type == circle_upper && dy1 >= a->segm.left_end.y) || (a->segm.type == circle_lower && dy1 <= a->segm.left_end.y)) {
			if (dx1 <= b->segm.right_end.x && dx1 >= b->segm.left_end.x) {
				tem_cal.x = dx1;
				tem_cal.y = dy1;
				num++;
				if (is_zero(dx1 - dx2) && is_zero(dy1 - dy2)) { if (swap_sig) { swap_seg(*a, *b); } return num; }
			}
		}
		if ((a->segm.type == circle_upper && dy2 >= a->segm.left_end.y) || (a->segm.type == circle_lower && dy2 <= a->segm.left_end.y)) {
			if (dx2 <= b->segm.right_end.x && dx2 >= b->segm.left_end.x) {
				if (num == 1) {
					tem_cal2.x = dx2;
					tem_cal2.y = dy2;
				}
				else {
					tem_cal.x = dx2;
					tem_cal.y = dy2;
				}
				num++;
			}
		}
		if (swap_sig) { swap_seg(*a, *b); }
		return num;
	}
	else {
		double denominator = (b->segm.left_end.x - b->segm.right_end.x)*(a->segm.left_end.y - a->segm.right_end.y) -
			(a->segm.left_end.x - a->segm.right_end.x)*(b->segm.left_end.y - b->segm.right_end.y);
		double numerator = (a->segm.left_end.x - a->segm.right_end.x)*(b->segm.right_end.y - a->segm.right_end.y) -
			(a->segm.left_end.y - a->segm.right_end.y)*(b->segm.right_end.x - a->segm.right_end.x);
		double x = (b->segm.left_end.x - b->segm.right_end.x)*numerator / denominator + b->segm.right_end.x;
		double y = (b->segm.left_end.y - b->segm.right_end.y)*numerator / denominator + b->segm.right_end.y;
		tem_cal.x = x;
		tem_cal.y = y;
		return 1;
	}
}
bool detection_pre(avl_node* just_insert) {
	avl_node* pre = just_insert->pre();
	if (pre&&is_intersection(just_insert, pre)) {
		return true;
	}
	else return false;
}
bool detection_succ(avl_node* just_insert) {
	avl_node* succ = just_insert->succ();
	if (succ&&is_intersection(just_insert, succ)) {
		return true;
	}
	else return false;
}