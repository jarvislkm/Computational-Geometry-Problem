#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "point.h"
#include "window.h"
#include "range_tree.h"
#include "func.h"
#include "segment.h"
#include "interval_tree.h"

#define _CRTDBG_MAP_ALLOC  
//#include <stdlib.h>
//#include <crtdbg.h>

void read(long &num, long& num_win,std::vector<Segment>& s_v_h,std::vector<Point>& p_v_h,std::vector<Segment>& s_v_v,std::vector<Point>& p_v_v,std::vector<Window>& w_v) {
	std::ifstream in;
	in.open("data.txt");
	in >> num>>num_win;
	long count = 0;
	while (count < num) {
		long x1, y1, x2, y2;
		in >> x1 >> y1>>x2>>y2;
		if (y1 == y2) {
			if (x1 > x2) { std::swap(x1, x2); }
			s_v_h.push_back(Segment(Point(x1, y1, count), Point(x2, y2, count), count));
			p_v_h.push_back(Point(x1, y1, count));
			p_v_h.push_back(Point(x2, y2, count));
		}
		else {
			if (y1 > y2) { std::swap(y1, y2); }
			s_v_v.push_back(Segment(Point(y1, x1, count), Point(y2, x2, count), count));
			p_v_v.push_back(Point(y1, x1, count));
			p_v_v.push_back(Point(y2, x2, count));
		}
		count++;
	}

	count = 0;
	while (count++<num_win) {
		long x1, y1, x2, y2;
		in >> x1 >> y1 >> x2 >> y2;
		w_v.push_back(Window(Point(x1, y1), Point(x2, y2)));
	}
	in.close();
	return;
}

int main() {
	{
		long seg_num, window_num;
		std::vector<Segment> seg_vec_h;
		std::vector<Segment> seg_vec_v;
		std::vector<Point> point_vec_h;
		std::vector<Point> point_vec_v;
		std::vector<Window> window_vec;

		read(seg_num, window_num, seg_vec_h, point_vec_h, seg_vec_v, point_vec_v, window_vec);

		sort(point_vec_h.begin(), point_vec_h.end(), CompareX);
		sort(point_vec_v.begin(), point_vec_v.end(), CompareX);

		RangeTree rt_h(point_vec_h);
		RangeTree rt_v(point_vec_v);

		IntervalTree it_h(seg_vec_h);
		IntervalTree it_v(seg_vec_v);

		std::ofstream out;
		out.open("result.txt");

		for (auto w : window_vec) {
			rt_h.QueryRange(w.ll, w.ru);
			auto id_vec = rt_h.point_id;
			sort(id_vec.begin(), id_vec.end()); // id is in point_id
			auto end_unique = unique(id_vec.begin(), id_vec.end());
			id_vec.erase(end_unique, id_vec.end());
			int type_a = id_vec.size();
			std::cout << "type_a_h: " << type_a;

			auto type_b = it_h.QueryStabNum(w.ll.x, w.ru.y, w.ll.y);

			id_vec.insert(id_vec.end(), type_b.begin(), type_b.end());
			sort(id_vec.begin(), id_vec.end()); // id is in point_id
			end_unique = unique(id_vec.begin(), id_vec.end());
			id_vec.erase(end_unique, id_vec.end());
			long total_h = id_vec.size();
			long type_b_r = id_vec.size() - type_a;
			std::cout << "  type_b_h: " << type_b_r << std::endl;
			//out << total_h << std::endl;

			//Then handle the vertical one

			Point ll_v(w.ll.y, w.ll.x);
			Point ru_v(w.ru.y, w.ru.x);

			rt_v.QueryRange(ll_v, ru_v);
			auto id_vec_v = rt_v.point_id;

			sort(id_vec_v.begin(), id_vec_v.end()); // id is in point_id
			auto end_unique_v = unique(id_vec_v.begin(), id_vec_v.end());
			id_vec_v.erase(end_unique_v, id_vec_v.end());
			int type_a_v = id_vec_v.size();
			std::cout << "type_a_v: " << type_a_v;

			auto type_b_v = it_v.QueryStabNum(w.ru.y, w.ru.x, w.ll.x);

			id_vec_v.insert(id_vec_v.end(), type_b_v.begin(), type_b_v.end());
			sort(id_vec_v.begin(), id_vec_v.end()); // id is in point_id
			end_unique_v = unique(id_vec_v.begin(), id_vec_v.end());
			id_vec_v.erase(end_unique_v, id_vec_v.end());
			long total_v = id_vec_v.size();
			long type_b_r_v = id_vec_v.size() - type_a_v;
			std::cout << "  type_b_v: " << type_b_r_v << std::endl;
			//out << total_v << std::endl;

			long total = total_h + total_v;
			out << total << std::endl;

		}
		out.close();
	}
//	_CrtDumpMemoryLeaks();
	return 0;
}
