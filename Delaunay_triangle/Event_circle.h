#pragma once
#include "Event.h"
#include <iostream>
class coast_node;
class Event_circle :
	public Event
{
public:
	Event_circle(double x, double y) :Event(x, y) { node = NULL; };
	int circle[3];
	point center;
	coast_node* node;
};

