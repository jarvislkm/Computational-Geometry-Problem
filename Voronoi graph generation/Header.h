#pragma once

#define eventquene_par(i) ((i-1)>>1)
#define Inheap(n,i) (i<n)
#define lchild(i) (1+((i)<<1))
#define rchild(i) ((1+i)<<1)
#define lchildvalid(n,i) Inheap(n,lchild(i)) 
#define rchildvalid(n,i) Inheap(n,rchild(i))
#define smaller(pq,i,j) (*pq[i]<*pq[j]?i:j)
#define larger(pq,i,j) (*pq[i]<*pq[j]?j:i)
#define smallof3(pq,i,n) rchildvalid(n,i)?smaller(pq, smaller(pq, lchild(i), rchild(i)), i):(lchildvalid(n,i)?smaller(pq,i,lchild(i)):i)
#define largeof3(pq,i,n) rchildvalid(n,i)?larger(pq, larger(pq, lchild(i), rchild(i)), i):(lchildvalid(n,i)?larger(pq,i,lchild(i)):i)