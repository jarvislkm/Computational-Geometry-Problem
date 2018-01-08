#pragma once
#include "Event.h"
#include <vector>
class eventqueue {
public:
	std::vector<event*> queue;
	int percolate_Up(int rank);
	int precolate_Down(int rank);
	event* getMax() { if (queue.size() > 0)return queue[0]; else return NULL; }
	event* delMax();
	void insert(event* to_insert);
};