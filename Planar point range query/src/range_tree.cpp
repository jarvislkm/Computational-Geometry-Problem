#include "range_tree.h"
#include "func.h"
#include <algorithm>

node* range_tree::construct(std::vector<point>& p_v) {
	std::vector<node*> work;
	std::vector<node*> next;
	for (auto p : p_v) {
		node* n = new node(p);
		n->ylist.push_back(p);
		work.push_back(n);
	}
	while (work.size() > 1) {
		for (int i = 0; i < work.size(); i += 2) {
			if (i != work.size() - 1) {
				node* find = work.at(i);
				while (find->rc) {
					find = find->rc;
				}
				node* n = new node(find->p);
				n->lc = work.at(i);
				n->rc = work.at(i + 1);
				work.at(i)->parent = n;
				work.at(i + 1)->parent = n;
				auto list1 = work.at(i)->ylist;
				auto list2 = work.at(i + 1)->ylist;
				std::vector<point> res(list1.size() + list2.size());
//				merge(list1.begin(), list1.end(), list2.begin(), list2.end(), res.begin(), compare_y);
				range_tree_project::merge_ylist(list1, list2, n->ylist);
//				n->ylist = res;
				next.push_back(n);
			}
			else { next.push_back(work.at(i)); }
		}
		work = next;
		next.clear();
	}
	return work.at(0);
}

long int range_tree::range(point left_point, point right_point) {
	double left = left_point.x-0.5;
	double right = right_point.x+0.5;
	double bottom = left_point.y-0.5;
	double top = right_point.y+0.5;
	node* start_left = root;
	node* start_right = root;
	long int root_top = root->find_top(top);
	long int root_bottom = root->find_bottom(bottom);
	long int now_bottom_l = root_bottom;
	long int now_bottom_r = root_bottom;
	long int now_top_l = root_top;
	long int now_top_r = root_top;
	long int count_top;
	long int count_bottom;
	
	while (start_left == start_right && !start_left->is_leaf()) {
		if (left > start_left->p.x) {
			if (now_bottom_l >= 0 && start_left->ylist.size() > now_bottom_l) {
				now_bottom_l = start_left->ylist.at(now_bottom_l).ref_right;
			}
			else now_bottom_l = -1;
			if (now_top_l>=0 && start_left->ylist.size() > now_top_l) {
				now_top_l = start_left->ylist.at(now_top_l).ref_right;
			}
			else now_top_l = -1;
			start_left = start_left->rc;
		} 
		else {
			if (now_bottom_l >= 0 && start_left->ylist.size() > now_bottom_l) {
				now_bottom_l = start_left->ylist.at(now_bottom_l).ref_left;
			}
			else now_bottom_l = -1;
			if (now_top_l >= 0 && start_left->ylist.size() > now_top_l) {
				now_top_l = start_left->ylist.at(now_top_l).ref_left;
			}
			else now_top_l = -1;
			start_left = start_left->lc;
		}
		if (right > start_right->p.x) {
			if (now_bottom_r >= 0 && start_right->ylist.size() > now_bottom_r) {
				now_bottom_r = start_right->ylist.at(now_bottom_r).ref_right;
			}
			else now_bottom_r = -1;
			if (now_top_r >= 0 && start_right->ylist.size() > now_top_r) {
				now_top_r = start_right->ylist.at(now_top_r).ref_right;
			}
			else now_top_r = -1;
			start_right = start_right->rc;
		} 
		else {
			if (now_bottom_r >= 0 && start_right->ylist.size() > now_bottom_r) {
				now_bottom_r = start_right->ylist.at(now_bottom_r).ref_left;
			}
			else now_bottom_r = -1;
			if (now_top_r >= 0 && start_right->ylist.size() > now_top_r) {
				now_top_r = start_right->ylist.at(now_top_r).ref_left;
			}
			else now_top_r = -1;
			start_right = start_right->lc;
		} 
	}

	long int count = 0;

	while (!start_left->is_leaf()) {
		if (left > start_left->p.x) {
			if (now_bottom_l >= 0 && start_left->ylist.size() > now_bottom_l) {
				now_bottom_l = start_left->ylist.at(now_bottom_l).ref_right;
			}
			else now_bottom_l = -1;
			if (now_top_l >= 0 && start_left->ylist.size() > now_top_l) {
				now_top_l = start_left->ylist.at(now_top_l).ref_right;
			}
			else now_top_l = -1;
			start_left = start_left->rc;
		}
		else {
//			count += start_left->rc->ylist_find(top, bottom);
			if (now_bottom_l >= 0 && start_left->ylist.size() > now_bottom_l) {
				count_bottom = start_left->ylist.at(now_bottom_l).ref_right;
			}
			else count_bottom = -1;
			if (now_top_l >= 0 && start_left->ylist.size() > now_top_l) {
				count_top = start_left->ylist.at(now_top_l).ref_right;
			}
			else count_top = -1;

			if (count_top == -1 && count_bottom>=0) { count += start_left->rc->ylist.size() - count_bottom; }
			else if (count_top == -1 && count_bottom == -1) {}
			else count += count_top - count_bottom;

			if (now_bottom_l >= 0 && start_left->ylist.size() > now_bottom_l) {
				now_bottom_l = start_left->ylist.at(now_bottom_l).ref_left;
			}
			else now_bottom_l = -1;
			if (now_top_l >= 0 && start_left->ylist.size() > now_top_l) {
				now_top_l = start_left->ylist.at(now_top_l).ref_left;
			}
			else now_top_l = -1;
			start_left = start_left->lc;
		}
	}
	if (start_left->p.x > left && start_left->p.x < right &&bottom <= start_left->p.y && start_left->p.y <= top) {
		count++;
	}

	while (!start_right->is_leaf()) {
		if (start_right->p.x > right) {
			if (now_bottom_r >= 0 && start_right->ylist.size() > now_bottom_r) {
				now_bottom_r = start_right->ylist.at(now_bottom_r).ref_left;
			}
			else now_bottom_r = -1;
			if (now_top_r >= 0 && start_right->ylist.size() > now_top_r) {
				now_top_r = start_right->ylist.at(now_top_r).ref_left;
			}
			else now_top_r = -1;
			start_right = start_right->lc;
		}
		else {
//			count += start_right->lc->ylist_find(top, bottom);
			if (now_bottom_r >= 0 && start_right->ylist.size() > now_bottom_r) {
				count_bottom = start_right->ylist.at(now_bottom_r).ref_left;
			}
			else count_bottom = -1;
			if (now_top_r >= 0 && start_right->ylist.size() > now_top_r) {
				count_top = start_right->ylist.at(now_top_r).ref_left;
			}
			else count_top = -1;
			if (count_top == -1 && count_bottom>=0) { count += start_right->lc->ylist.size() - count_bottom; }
			else if (count_top == -1 && count_bottom == -1) {}
			else count += count_top - count_bottom;

			if (now_bottom_r >= 0 && start_right->ylist.size() > now_bottom_r) {
				now_bottom_r = start_right->ylist.at(now_bottom_r).ref_right;
			}
			else now_bottom_r = -1;
			if (now_top_r >= 0 && start_right->ylist.size() > now_top_r) {
				now_top_r = start_right->ylist.at(now_top_r).ref_right;
			}
			else now_top_r = -1;
			start_right = start_right->rc;
		}
	}
	if (start_right != start_left && start_right->p.x < right && start_right->p.x > left &&bottom <= start_right->p.y && start_right->p.y <= top) {
		count++;
	}
	return count;
};