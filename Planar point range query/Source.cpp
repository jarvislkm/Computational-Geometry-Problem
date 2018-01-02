#include <iostream>
#include <algorithm>
#include <vector>
#include "point.h"
#include "window.h"
#include "range_tree.h"
#include "func.h"

using namespace std;

void read(int &num, int& num_win, vector<point>& p_v, vector<window>& w_v) {
	cin >> num >> num_win;
	int count = 0;
	while (count++ < num) {
		int x, y;
		cin >> x >> y;
		p_v.push_back(point(x,y));
	}
	count = 0;
	while (count++<num_win) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		w_v.push_back(window(point(x1, y1), point(x2, y2)));
	}
	return;
}

int main() {
	int point_num, window_num;
	vector<point> point_vec;
	vector<window> window_vec;
	read(point_num, window_num, point_vec, window_vec);
	sort(point_vec.begin(), point_vec.end(), compare_x);

	range_tree tree(point_vec);

	for (auto w : window_vec) {
		long int res = tree.range(w.ll, w.ru);
		printf("%ld\r\n", res);
	}
	return 0;
}