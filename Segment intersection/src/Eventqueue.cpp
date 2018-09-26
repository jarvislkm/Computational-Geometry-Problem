#include "Eventqueue.h"

int eventqueue::percolate_Up(int rank) {
	while (rank != 0) {
		int rankp = eventquene_par(rank);
		if (!(*queue.at(rank) < *(queue.at(rankp)))) break;
		std::swap(queue.at(rank), queue.at(rankp));
		rank = rankp;
	}
	return rank;
}

int eventqueue::precolate_Down(int rank) {
	int size = queue.size();
	int small = 0;
	while (rank != (small = smallof3(queue, rank, size))) {
		std::swap(queue.at(rank), queue.at(small));
		rank = small;
	}
	return rank;
}

event* eventqueue::delMax() {
	event* max = queue[0];
	int size = queue.size();
	queue[0] = queue[size - 1];
	queue.pop_back();
	precolate_Down(0);
	return max;
}

void eventqueue::insert(event* to_insert) {
	queue.push_back(to_insert);
	percolate_Up(queue.size() - 1);
}