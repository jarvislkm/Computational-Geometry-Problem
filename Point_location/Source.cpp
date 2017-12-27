#include <iostream>
#include <vector>
#include "point.h"
#include "segment.h"
#include "node_t.h"
#include "node.h"
#include "Dag.h"
using namespace std;
const long int bound = 2000000;
void read(long int& number, vector<segment*>&seg_vec, long int& test_num, vector<point*>& point_vec) {
	long int x1,x2;
	double y1,y2;
	cin >> number;
	cin >> test_num;
	long int count = 0;
	while (count<number) {
		cin >> x1 >> y1 >> x2 >> y2;
		point a(x1, y1);
		point b(x2, y2);
		if (b < a) { swap(a, b); }
		segment* s = new segment(a, b, ++count);
		seg_vec.push_back(s);
	}

	count = 0;
	while (count++<test_num){
		cin >> x1 >> y1;
		point*p = new point(x1, y1);
		point_vec.push_back(p);
	}
	return;
}

long int find_point(point p, Dag& dag) {

	node* work = dag.root;
	while (!work->is_terminal()) {
		if (work->compare_x(p)) return work->compare_x(p);
		if (work->compare(p)) {
			work = work->lc;
		}
		else work = work->rc;
	}

	trapezoid* t = work->get_trap();
	if (t->left.x != t->right.x) {
		if (p.x == t->left.x) {
			if (p.y < t->left.y) { return find_point(t->left, dag); }
		}
		else if (p.x == t->right.x) {
			if (p.y < t->right.y) { return find_point(t->right, dag); }
		}
		int long result = work->get_trap()->upper->id;
		return result;
	}

	else {
		double yl = t->left.y - p.y;
		double yr = t->right.y - p.y;
		if (yl > 0 && yr > 0) {
			if (yl > yr) return find_point(t->right, dag);
			else if (yl < yr) return find_point(t->left, dag);
		}
		else if (yl>0) return find_point(t->left, dag);
		else if(yr>0) return find_point(t->right, dag);
		else return -1;
	}
}

int main() {
	long int number;
	long int test_num;
	vector<point*> point_vec;
	vector<segment*> seg_vec;
	read(number, seg_vec, test_num, point_vec);
	point p1(-bound, bound);
	point p2(bound, bound);
	point p3(-bound, -bound);
	point p4(bound, -bound);
	segment* up_bound = new segment(p1,p2,-1);
	segment* low_bound = new segment(p3,p4,-1);
	node_t* init = new node_t(p1, p2, up_bound, low_bound);

	Dag dag(init);
	for (auto s : seg_vec) {
		dag.insert(s);
	}

	for (auto p : point_vec) {
		long int result = find_point(*p, dag);
		if (result>0) cout << result << endl;
		else cout << "N" << endl;
	}
	return 0;
}