#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "point.h"
#include "window.h"
#include "range_tree.h"
#include "func.h"

using namespace range_tree_project;

void read(int &num, int& num_win, std::vector<point>& p_v, std::vector<window>& w_v) {
	ifstream in;
	in.open("data.txt");
	in >> num >> num_win;
	int count = 0;
	while (count++ < num) {
		int x, y;
		in >> x >> y;
		p_v.push_back(point(x,y));
	}
	count = 0;
	while (count++<num_win) {
		int x1, y1, x2, y2;
		in >> x1 >> y1 >> x2 >> y2;
		w_v.push_back(window(point(x1, y1), point(x2, y2)));
	}
	in.close();
	return;
}

int main() {
	int point_num, window_num;
	std::vector<point> point_vec;
	std::vector<window> window_vec;
	read(point_num, window_num, point_vec, window_vec);
	sort(point_vec.begin(), point_vec.end(), compare_x);

	range_tree tree(point_vec);

	ofstream out;
	out.open("result.txt");
	for (auto w : window_vec) {
		long int res = tree.range(w.ll, w.ru);
		out << res <<endl;
		printf("%ld\r\n", res);
	}
	out.close();

	while (1) {
		int a;
	}
	return 0;
}