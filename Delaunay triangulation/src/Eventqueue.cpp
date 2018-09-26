#include "Eventqueue.h"

int eventqueue::percolate_Up(int rank) {
	while (rank != 0) {
		int rankp = eventquene_par(rank);
		if (*queue.at(rank) < *(queue.at(rankp))) break;
		std::swap(queue.at(rank), queue.at(rankp));
		rank = rankp;
	}
	return rank;
}

int eventqueue::precolate_Down(int rank) {
	int size = queue.size();
	int large = 0;
	while (rank != (large = largeof3(queue, rank, size))) {
		std::swap(queue.at(rank), queue.at(large));
		rank = large;
	}
	return rank;
}

Event_circle* eventqueue::delMax() {
	Event_circle* max = queue[0];
	int size = queue.size();
	queue[0] = queue[size - 1];
	queue.pop_back();
	precolate_Down(0);
	return max;
}

void eventqueue::insert(Event_circle* to_insert) {
	queue.push_back(to_insert);
	percolate_Up(queue.size() - 1);
}

bool eventqueue::delete_element(Event_circle* to_delete) {
	int i = 0;
	if (!to_delete) return false;
	while (i < queue.size()) {
		if (queue[i] == to_delete) { 
			queue[i] = queue[queue.size() - 1];
			delete to_delete;
			queue.pop_back();
			precolate_Down(i);
			if(i<queue.size())	percolate_Up(i);
			return true;
		}
		i++;
	}
	return false;
}