#pragma once
#include "Header.h"
#include "Segment.h"
class event{
public:
	event(type_of_event _type, segment &_s1) : type(_type), s1(_s1) { cal_point(); };
	event(type_of_event _type, segment &_s1, point _p) : type(_type), s1(_s1), event_posi(_p) {};
	bool operator <(event& a) {
		if ((event_posi.x - a.event_posi.x)<-1e-8) return true;          // smaller x first
		else if ((event_posi.x - a.event_posi.x)>1e-8) return false;          // smaller x first

		if ((event_posi.y - a.event_posi.y)>1e-8) return true;   // large y first
		else if ((event_posi.y - a.event_posi.y)<-1e-8) return false;

		if (type > a.type) return true;
		else return false;
	}
	void cal_point() {
		if (type == insert_seg) event_posi = s1.left_end;
		if (type == remove_seg) event_posi = s1.right_end;
		if (type == verticle_line_open) event_posi = s1.left_end;
		if (type == verticle_line_close) event_posi = s1.right_end;
	}
	type_of_event type;
	point event_posi;
	segment s1;
};