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
#include <time.h>
#define eps 1e-7
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define rep0(j,n) for(int j=0;j<n;++j)
#define rep1(j,n) for(int j=1;j<=n;++j)
#define pb push_back
#define mp make_pair
#define set0(n) memset(n,0,sizeof(n))
#define ll long long
#define ull unsigned long long
#define iter(i,v) for(edge *i=head[v];i;i=i->nxt)
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
#define print_runtime printf("Running time:%.3lfs\n",double(clock())/1000.0)
#define TO(j) printf(#j": %d\n",j);
//#define OJ
using namespace std;
const int MAXINT = 100010;
const int MAXNODE = 100010;
const int MAXEDGE = 2 * MAXNODE;
char BUF, *buf;
int read() {
	char c = getchar(); int f = 1, x = 0;
	while (!isdigit(c)) { if (c == '-') f = -1; c = getchar(); }
	while (isdigit(c)) { x = x * 10 + c - '0'; c = getchar(); }
	return f * x;
}
char get_ch() {
	char c = getchar();
	while (!isalpha(c)) c = getchar();
	return c;
}
//------------------- Head Files ----------------------//
int b[MAXINT], lp[1000100], st[18][MAXINT], min_b, n, k, q;
int st_query(int l, int r) {
	int d = lp[r - l + 1];
	return min(st[d][l], st[d][r - (1 << d) + 1]);
}
struct node {
	node* lc, *rc;
	int mn, tag, l, r, mid;
	int check(int lb, int rb) {
		if (lb <= l && rb >= r) return 1;
		if (lb >= r || rb <= l) return -1;
		return 0;
	}
	void addtag(int v) {
		tag = mn = v;
	}
	void pushdown() {
		if (tag) {
			lc->addtag(tag);
			rc->addtag(tag);
			tag = 0;
		}
	}
	void pushup() {
		mn = min(lc->mn, rc->mn);
	}
};
struct segtree {
	node *root;
	node mp[5000000];
	int cnt;
	node *new_node(int l, int r) {
		node *p = &mp[cnt++];
		p->l = l; p->r = r; p->mid = (l + r) >> 1;
		if (r - l >= n) p->mn = min_b;
		else {
			l = l % n; r = (r - 1) % n;
			if (r >= l) p->mn = st_query(l, r);
			else {
				p->mn = min(st_query(0, r), st_query(l, n - 1));
			}
		}
		return p;
	}
	segtree() {
		cnt = 0;
	}
	void init(int l, int r) {
		root = new_node(l, r);
	}
	int query(int l, int r) {
		return query(root, l, r);
	}
	void extend(node *p) {
		if (p->lc) return;
		p->lc = new_node(p->l, p->mid);
		p->rc = new_node(p->mid, p->r);
	}
	int query(node *p, int l, int r) {
		if (p->check(l, r) == 1) return p->mn;
		if (p->check(l, r) == -1) return INF;
		extend(p);
		p->pushdown();
		int la = query(p->lc, l, r), ra = query(p->rc, l, r);
		return min(la, ra);
	}
	void cover(int l, int r, int v) {
		cover(root, l, r, v);
	}
	void cover(node *p, int l, int r, int v) {
		if (p->check(l, r) == 1) {
			p->addtag(v);
			return;
		}
		if (p->check(l, r) == -1) return;
		extend(p);
		p->pushdown();
		cover(p->lc, l, r, v);
		cover(p->rc, l, r, v);
		p->pushup();
	}
}sg;
void pre_calc();
void get_input();
void work();
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.tle", "w", stdout);
	get_input();
	pre_calc();
	work();
	return 0;
}
void work() {
	int op, l, r, v;
	sg.init(0, n*k);
	while (q--) {
		op = read();
		if (op == 1) {
			l = read(); r = read(); v = read();
			sg.cover(l - 1, r, v);
		}
		if (op == 2) {
			l = read(); r = read();
			printf("%d\n", sg.query(l - 1, r));
			fflush(stdout);
		}
	}
}
void get_input() {
	n = read(); k = read();
	min_b = INF;
	rep0(i, n) b[i] = read(), min_b = min(min_b, b[i]);
	q = read();
}
void pre_calc() {
	for (int i = 0; i < 17; i++) {
		for (int j = (1 << i); j < (1 << (i + 1)); j++) lp[j] = i;
	}
	rep0(i, n) st[0][i] = b[i];
	for (int j = 1; j < 17; j++) {
		rep0(i, n - (1 << j) + 1) st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
	}
}


