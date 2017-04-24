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
#define set0(n) memset(n,0,sizeof(n))
#define ll long long
#define ull unsigned long long
#define iter(i,v) for(edge *i=head[v];i;i=i->nxt)
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
#define print_rumtime printf("Running time:%.3lfs\n",double(clock())/1000.0);
#define TO(j) printf(#j": %d\n",j);
//#define OJ
using namespace std;
const int MAXINT = 300010;
const int MAXNODE = 100010;
const int MAXEDGE = 2 * MAXNODE;
char BUF, *buf;
int read() {
	int c = getchar(); int f = 1, x = 0;
	while (!isdigit(c)) { if (c == '-') f = -1; if (c == -1) return -INF; c = getchar(); }
	while (isdigit(c)) { x = x * 10 + c - '0'; c = getchar(); }
	return f * x;
}
char get_ch() {
	char c = getchar();
	while (!isalpha(c)) c = getchar();
	return c;
}
int read_op() {
	int tp = 0, c = getchar();
	while (!isalpha(c))c = getchar();
	if (c == 'U') return 0;
	if (c == 'F') tp += 3;
	c = getchar();
	tp += c - '0';
	return tp;
}
//------------------- Head Files ----------------------//
int cnt, h, t, n, a[MAXINT], m, fa[MAXINT], tag[MAXINT], add_tot = 0, sz[MAXINT];
struct node {
	node *f, *prv, *nxt, *c;
	int v;
}*q[2 * MAXINT], *root[MAXINT], mp[MAXINT * 2];
int find_fa(int p) {
	return fa[p] == p ? p : find_fa(fa[p]);
}
int get_tag(int p) {
	int ans = tag[p];
	while (p != fa[p]) {
		p = fa[p];
		ans += tag[p];
	}
	return ans;
}
node* combine(node *a, node *b) {
	if (a == b) abort();
	if (!a) return b;
	if (!b) return a;
	if (a->v + get_tag(a - mp) < b->v + get_tag(b - mp)) swap(a, b);
	b->nxt = a->c;
	if (a->c) a->c->prv = b;
	a->c = b;
	b->f = a;
	return a;
}

node* pop(node *pt) {
	h = t = 0;
	node *p = pt->c;
	while (p) {
		q[t++] = p;
		p = p->nxt;
	}
	rep0(i, t) q[i]->f = q[i]->prv = q[i]->nxt = NULL;
	while (t - h > 1) q[t++] = combine(q[h], q[h + 1]), h += 2;
	pt->c = NULL;
	return (h != t ? q[h] : NULL);
}
void del(node *p) {
	if (p->prv) p->prv->nxt = p->nxt;
	if (p->nxt) p->nxt->prv = p->prv;
	if (p->f && p == p->f->c) p->f->c = p->nxt;
	p->f = p->prv = p->nxt = NULL;
}
struct pq {
	priority_queue<int> d, v;
	void push(int p) {
		v.push(p);
	}
	void del(int p) {
		d.push(p);
	}
	int top() {
		while (d.size() && v.top() == d.top()) d.pop(), v.pop();
		return v.top();
	}
} ans;
void get_input();
void work();
int main() {
	cnt = 0;
	get_input();
	work();
	return 0;
}
void work() {
	rep1(j, m) {
		int op = read_op();
		if (op == 0) {
			int u = read(), v = read();
			u = find_fa(u); v = find_fa(v);
			node* x = root[u], *y = root[v];
			if (x == y) continue;
			ans.del(x->v + get_tag(x - mp)); ans.del(y->v + get_tag(y - mp));
			if (sz[u] > sz[v]) swap(u, v);
			fa[u] = v;
			tag[u] -= tag[v];
			sz[v] += sz[u];
			x = combine(x, y);
			root[v] = x;
			ans.push(x->v + get_tag(x - mp));
		}
		if (op == 1) {
			int u = read(), v = read();
			int rt = find_fa(u);
			ans.del(root[rt]->v + get_tag(root[rt] - mp));
			if (&mp[u] != root[rt]) del(&mp[u]);
			node *p = pop(&mp[u]);
			mp[u].v += v;
			p = combine(p, &mp[u]);
			if (&mp[u] != root[rt]) p = combine(p, root[rt]);
			root[rt] = p;
			ans.push(p->v + get_tag(p - mp));
		}
		if (op == 2) {
			int u = read(), v = read();
			u = find_fa(u);
			node *p = root[u];
			ans.del(p->v + get_tag(p - mp));
			tag[u] += v;
			ans.push(p->v + get_tag(p - mp));
		}
		if (op == 3) add_tot += read();
		if (op == 4) {
			int u = read();
			printf("%d\n", mp[u].v + get_tag(u) + add_tot);
		}
		if (op == 5) {
			int u = read(); u = find_fa(u);
			node *p = root[u];
			printf("%d\n", p->v + get_tag(p - mp) + add_tot);
		}
		if (op == 6) printf("%d\n", ans.top() + add_tot);
	}
}
void get_input() {
	n = read();
	rep1(i, n) {
		mp[i].v = read();
		ans.push(mp[i].v);
		mp[i].f = mp[i].nxt = mp[i].c = NULL;
		sz[i] = 1, fa[i] = i, root[i] = &mp[i];
	}
	m = read();
}
