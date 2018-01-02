#include "range_tree_node.h"
using namespace std;
long node::ylist_find(double top, double bottom) {
	long left = 0;
	long right = ylist.size();
	long count = 0;
	do
	{
		long middle = (left+right)/2;
		if (ylist.at(middle).y > top) { right = middle; }
		else left = middle+1;
	} while (left<right);
	long find_top = right;

	left = 0;
	right = ylist.size();
	do
	{
		long middle = (left + right)/2;
		if (bottom < ylist.at(middle).y) { right = middle; }
		else left = middle+1;
	} while (left < right);
	long find_bottom = left;

	count = find_top - find_bottom;
	return count>0?count:0;
}

long node::find_top(double top) {
	long left = 0;
	long right = ylist.size();
	long count = 0;
	do
	{
		long middle = (left + right) / 2;
		if (ylist.at(middle).y > top) { right = middle; }
		else left = middle + 1;
	} while (left<right);
	return right;
}

long node::find_bottom(double bottom) {
	long left = 0;
	long right = ylist.size();
	do
	{
		long middle = (left + right) / 2;
		if (bottom < ylist.at(middle).y) { right = middle; }
		else left = middle + 1;
	} while (left < right);
	return left;
}