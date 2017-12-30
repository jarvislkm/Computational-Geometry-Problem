#pragma once
#include "point.h"
class Event
{
public:
	Event(double x, double y) :eventpoint(x, y) {};
	bool operator <(Event& s) {
		return eventpoint < s.eventpoint;
	}
	point eventpoint;
};

