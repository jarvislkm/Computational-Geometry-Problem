#include <iostream>
#include <algorithm>
#include <vector>
#include "point.h"
#include "window.h"
#include "range_tree.h"
#include "func.h"
#include "segment.h"
#include "interval_tree.h"
using namespace std;

void read(long &num, long& num_win, vector<segment>& s_v_h, vector<point>& p_v_h, vector<segment>& s_v_v, vector<point>& p_v_v, vector<window>& w_v) {
	cin >> num>>num_win;
	long count = 0;
	while (count < num) {
		long x1, y1, x2, y2;
		cin >> x1 >> y1>>x2>>y2;
		if (y1 == y2) {
			if (x1 > x2) { swap(x1, x2); }
			s_v_h.push_back(segment(point(x1, y1, count), point(x2, y2, count), count));
			p_v_h.push_back(point(x1, y1, count));
			p_v_h.push_back(point(x2, y2, count));
		}
		else {
			if (y1 > y2) { swap(y1, y2); }
			s_v_v.push_back(segment(point(y1, x1, count), point(y2, x2, count), count));
			p_v_v.push_back(point(y1, x1, count));
			p_v_v.push_back(point(y2, x2, count));
		}
		count++;
	}

	count = 0;
	while (count++<num_win) {
		long x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		w_v.push_back(window(point(x1, y1), point(x2, y2)));
	}
	return;
}

int main() {
	long seg_num, window_num;
	vector<segment> seg_vec_h;
	vector<segment> seg_vec_v;
	vector<point> point_vec_h;
	vector<point> point_vec_v;
	vector<window> window_vec;

	read(seg_num, window_num, seg_vec_h, point_vec_h, seg_vec_v, point_vec_v, window_vec);

	sort(point_vec_h.begin(), point_vec_h.end(), compare_x);
	sort(point_vec_v.begin(), point_vec_v.end(), compare_x);

	range_tree rt_h(point_vec_h);
	range_tree rt_v(point_vec_v);

	interval_tree it_h(seg_vec_h);
	interval_tree it_v(seg_vec_v);

	for (auto w : window_vec) {
		rt_h.range(w.ll, w.ru);
		auto id_vec = rt_h.point_id;
		sort(id_vec.begin(), id_vec.end()); // id is in point_id
		auto end_unique = unique(id_vec.begin(), id_vec.end());
		id_vec.erase(end_unique, id_vec.end());
		int type_a = id_vec.size();

		auto type_b = it_h.line_number(w.ll.x, w.ru.y, w.ll.y);

		id_vec.insert(id_vec.end(), type_b.begin(), type_b.end());
		sort(id_vec.begin(), id_vec.end()); // id is in point_id
		end_unique = unique(id_vec.begin(), id_vec.end());
		id_vec.erase(end_unique, id_vec.end());
		long total_h = id_vec.size();

		//Then handle the vertical one

		point ll_v(w.ll.y, w.ll.x);
		point ru_v(w.ru.y, w.ru.x);

		rt_v.range(ll_v, ru_v);
		auto id_vec_v = rt_v.point_id;

		sort(id_vec_v.begin(), id_vec_v.end()); // id is in point_id
		auto end_unique_v = unique(id_vec_v.begin(), id_vec_v.end());
		id_vec_v.erase(end_unique_v, id_vec_v.end());
		int type_a_v = id_vec_v.size();

		auto type_b_v = it_v.line_number(w.ru.y, w.ru.x, w.ll.x);

		id_vec_v.insert(id_vec_v.end(), type_b_v.begin(), type_b_v.end());
		sort(id_vec_v.begin(), id_vec_v.end()); // id is in point_id
		end_unique_v = unique(id_vec_v.begin(), id_vec_v.end());
		id_vec_v.erase(end_unique_v, id_vec_v.end());
		long total_v = id_vec_v.size();
		long type_b_r_v = id_vec_v.size() - type_a_v;

		long total = total_h + total_v;
		printf("%ld\r\n", total);
		
	}
	return 0;
}