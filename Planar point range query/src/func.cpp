#include "func.h"
namespace range_tree_project {
bool compare_y(const point& a, const point& b) {
	return a.y < b.y ? true : (a.y == b.y ? a.x < b.x : false);
}

bool compare_x(const point& a, const point& b) {
	return a.x < b.x ? true : (a.x == b.x ? a.y < b.y : false);
}

void merge_ylist(std::vector<point>& ylist_l, std::vector<point>& ylist_r, std::vector<point>& ylist) {
	long int count_l = 0;
	long int count_r = 0;
	long int rec = 0;
	long int count = 0;
	bool change = false;
	bool is_left = true;
	while (count_l < ylist_l.size() || count_r < ylist_r.size()) {
		bool left_time;
		if (count_l < ylist_l.size() && count_r < ylist_r.size()) {
			left_time = compare_y(ylist_l.at(count_l), ylist_r.at(count_r));
		}
		else if (count_l >= ylist_l.size()) {
			left_time = false;
		}
		else { left_time = true; }

		if (left_time) {
			point p(ylist_l.at(count_l).x, ylist_l.at(count_l).y);
			p.ref_left = count_l;
			ylist.push_back(p);
			count_l++;
			if (is_left) change = false;
			else change = true;
			is_left = true;
		}
		else {
			point p(ylist_r.at(count_r).x, ylist_r.at(count_r).y);
			p.ref_right = count_r;
			ylist.push_back(p);
			count_r++;
			if (is_left) change = true;
			else change = false;
			is_left = false;
		}
		if (change) {
			if (is_left) {
				for (long int i = rec; i < count; i++) {
					ylist.at(i).ref_left = count_l - 1;
				}
			}
			else {
				for (long int i = rec; i < count; i++) {
					ylist.at(i).ref_right = count_r - 1;
				}
			}
			rec = count;
		}
		count++;
	}
	if (!is_left) {
		for (long int i = rec; i < count; i++) {
			ylist.at(i).ref_left = count_l; // size of left ylist
		}
	}
	else {
		for (long int i = rec; i < count; i++) {
			ylist.at(i).ref_right = count_r;// size of right ylist
		}
	}
}
}