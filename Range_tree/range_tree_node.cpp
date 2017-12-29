#include "range_tree_node.h"

long int node::ylist_find(double top, double bottom) {
	long int left = 0;
	long int right = ylist.size();
	long int count = 0;
	do
	{
		long int middle = (left+right)/2;
		if (ylist.at(middle).y > top) { right = middle; }
		else left = middle+1;
	} while (left<right);
	long int find_top = right;

	left = 0;
	right = ylist.size();
	do
	{
		long int middle = (left + right)/2;
		if (bottom < ylist.at(middle).y) { right = middle; }
		else left = middle+1;
	} while (left < right);
	long int find_bottom = left;

	count = find_top - find_bottom;
	return count>0?count:0;
}

long int node::find_top(double top) {
	long int left = 0;
	long int right = ylist.size();
	long int count = 0;
	do
	{
		long int middle = (left + right) / 2;
		if (ylist.at(middle).y > top) { right = middle; }
		else left = middle + 1;
	} while (left<right);
	return right;
}

long int node::find_bottom(double bottom) {
	long int left = 0;
	long int right = ylist.size();
	do
	{
		long int middle = (left + right) / 2;
		if (bottom < ylist.at(middle).y) { right = middle; }
		else left = middle + 1;
	} while (left < right);
	return left;
}