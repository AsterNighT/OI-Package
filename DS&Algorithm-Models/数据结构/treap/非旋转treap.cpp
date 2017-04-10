#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>
#include <cmath>
#include <map>
#include <stack>
#include <set>
#include <vector>
#include <queue>
#define eps 10e-7
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define rep0(j,n) for(int j=0;j<n;++j)
#define rep1(j,n) for(int j=1;j<=n;++j)
#define pb push_back
#define set0(n) memset(n,0,sizeof(n))
#define ll long long

using namespace std;
int read() {
	char c = getchar(); int f = 1, x = 0;
	while (!isdigit(c)) {if (c == '-') f = -1; c = getchar();}
	while (isdigit(c)) {x = x * 10 + c - '0'; c = getchar();}
	return f * x;
}
const int MAXINT = 500010;
struct node {
	node* l, *r;
	int fix, key, sz;
	node(int _key): key(_key), fix(rand()), sz(1) {};
	node () {}
	void pushup() {
		sz = 1 + l->sz + r->sz;
	}
};
typedef pair<node*, node*> droot;
struct non_rotate_treap {
	node mempool[MAXINT], nil;
	node *NIL, *root;
	int cnt;
	non_rotate_treap() {
		NIL = &nil;
		NIL->l = NIL->r = NIL;
		NIL->key = NIL->fix = NIL->sz = 0;
		root = NIL;
		cnt = 0;
	}
	node* new_node(int v) {
		mempool[cnt] = node(v);
		mempool[cnt].l = mempool[cnt].r = NIL;
		return &mempool[cnt++];
	}
	node* merge(node *a, node *b) {
		if (a==NIL) return b;
		if (b==NIL) return a;
		if (a->fix < b->fix) {
			a->r = merge(a->r, b);
			a->pushup();
			return a;
		} else {
			b->l = merge(a, b->l);
			b->pushup();
			return b;
		}
	}
	droot split(node *p, int k) {
		if (p==NIL) return droot(NIL, NIL);
		droot r;
		if (p->l->sz >= k) {
			r = split(p->l, k);
			p->l = r.second;
			p->pushup();
			r.second = p;
		} else {
			r = split(p->r, k - p->l->sz - 1);
			p->r = r.first;
			p->pushup();
			r.first = p;
		}
		return r;
	}
	int find_rk(int k) {
		droot x = split(root,k-1);
		droot y = split(x.second ,1);
		node *ans = y.first;
		root = merge(merge(x.first,ans),y.second);
		return ans->key;
	}
	int get_rank(int v,node *p){
		if(p==NIL) return 0;
		return v<p->key?get_rank(v,p->l):get_rank(v,p->r)+p->l->sz+1;
	}
	void insert(int v){
		int k=get_rank(v,root);
		droot x = split(root,k);
		node *p  = new_node(v);
		root = merge(merge(x.first,p),x.second); 
	}
	void remove(int k){
		droot x = split(root,k-1);
		droot y = split(x.second,1);
		root = merge(x.first,y.second);
	}
	int find_v(int v){
		node *p = root;
		while(p!=NIL){
			if(p->key==v) return 1;
			p = v<p->key?p->l:p->r;
		}
		return 0;
	}
} treap;
int n, m, t;
int main() {
	m = read(); n = read();
	rep0(i, m) {
		treap.insert(read());
	}
	rep0(i, n) {
		printf("%d ", treap.find_v(read()));
	}
	return 0;
}

/*
5 5
9999999 4289 894 14 156
4289 894 14 156 9999999

5 5
5 4 3 1 2
4 3 1 2 5

*/

