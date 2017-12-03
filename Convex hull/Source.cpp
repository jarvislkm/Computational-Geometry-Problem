#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;
struct Point
{
	long long x;
	long long y;
	long long index;
};

bool isShorter(Point a, Point b) {
	if (a.x == b.x) return a.y < b.y;
	else return a.x < b.x;
}
void read(long long& number, vector<Point> &s) {
	ifstream in;
	in.open("data.txt");
	in >> number;
	long long itr = number;
	Point tem;
	long long index = 1;
	while (itr-- > 0) {
		in >> tem.x >> tem.y;
		tem.index = index++;
		s.push_back(tem);
	}
	sort(s.begin(), s.end(), isShorter);
}

long long to_left(Point a, Point b, Point c) {
	long long tem1 = a.x*b.y + b.x*c.y + c.x*a.y - b.y*c.x - c.y*a.x - a.y*b.x;
	return tem1;
}

int main() {
	long long number;
	vector<Point> data;
	read(number, data);
	vector<Point> upper_hull;
	vector<Point> lower_hull;
	vector<long long> hull_index;
	upper_hull.push_back(*data.begin());
	upper_hull.push_back(*(data.begin()+1));

	auto itr = data.begin()+1;
	while (itr != (data.end() - 1)) {
		++itr;
		long long res = 1;
		while (res > 0) {
			if (upper_hull.size() == 1) { res = -1; }
			else res = to_left(*(upper_hull.end() - 2), *(upper_hull.end() - 1), *itr);
			if (res >0) {
				upper_hull.pop_back();
			}
		}
		upper_hull.push_back(*itr);
	}


	lower_hull.push_back(*data.begin());
	lower_hull.push_back(*(data.begin()+1));
	auto itr2 = data.begin()+1;
	while (itr2 != (data.end() - 1)) {
		++itr2;
		long long res = 1;
		while (res > 0) {
			if (lower_hull.size() == 1) { res = -1; }
			else res = -to_left(*(lower_hull.end() - 2), *(lower_hull.end() - 1), *itr2);
			if (res >0) {
				lower_hull.pop_back();
			}
		}
		lower_hull.push_back(*itr2);
	}
	for (auto s = lower_hull.rbegin()+1; s != lower_hull.rend()-1;s++) {
		cout <<(*s).index << " ";
		hull_index.push_back((*s).index);
	}
	for (auto s : upper_hull) {
		cout << s.index << " ";
		hull_index.push_back(s.index);
	}
	cout << endl;

   ofstream out;
   out.open("result.txt");
	long long sum = 1;
	for (long long s : hull_index) {
		sum *= s;
		sum = sum % (number + 1);
		out << s-1 << endl;
	}
	out.close();
/* 	long long size = hull_index.size();
	long long result = (size*sum);
	long long resultf = result % (number + 1);
	cout << "sum :" << sum << endl;
	cout << "size :" << size << endl;
	cout <<resultf; */
	return 0;
}