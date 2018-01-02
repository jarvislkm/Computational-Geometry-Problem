#pragma once
#include "Event_circle.h"
#include "Header.h"
#include <vector>
using namespace std;

class eventqueue {
public:
	vector<Event_circle*> queue;
	int percolate_Up(int rank);
	int precolate_Down(int rank);
	Event_circle* getMax() { if (queue.size() > 0) return queue[0]; else return NULL; }
	Event_circle* delMax();
	bool delete_element(Event_circle* to_delete);
	void insert(Event_circle* to_insert);
};