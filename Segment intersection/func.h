#pragma once
#ifndef _FUNC
#define _FUNC

class segment;
class avl_node;
class point;

bool inter_compare(segment s1, segment s2);
void swap_seg(avl_node &a, avl_node &b);
double dis(point& a, point &b);
double to_left(point a, point b, point c);
bool left_comp(point* a, point*b);
bool left_unique(point* a, point*b);
bool is_intersection(avl_node* a, avl_node*b);
int cal_intersection(avl_node* a, avl_node*b);
bool detection_pre(avl_node* just_insert);
bool detection_succ(avl_node* just_insert);
int max(int a, int b);
bool is_zero(double s);

#endif