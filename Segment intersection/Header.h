#pragma once
enum type_of_line { seg, ray, line, circle_upper, circle_lower };
enum type_of_event { verticle_line_close, insert_seg, intersection, remove_seg, verticle_line_open };

#define from_parent_to(par) (par->is_root() ? root : (par->is_left_child() ? par->parent->lc : par->parent->rc))

#define eventquene_par(i) ((i-1)>>1)
#define Inheap(n,i) (i<n)
#define lchild(i) (1+((i)<<1))
#define rchild(i) ((1+i)<<1)
#define lchildvalid(n,i) Inheap(n,lchild(i)) 
#define rchildvalid(n,i) Inheap(n,rchild(i))
#define smaller(pq,i,j) (*pq[i]<*pq[j]?i:j)
#define smallof3(pq,i,n) rchildvalid(n,i)?smaller(pq, smaller(pq, lchild(i), rchild(i)), i):(lchildvalid(n,i)?smaller(pq,i,lchild(i)):i)
