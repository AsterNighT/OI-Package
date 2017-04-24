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
//#define OJ
using namespace std;
const int MAXINT = 1000;
const int MAXNODE = 100010;
const int MAXEDGE = 200010;
int n, m, cnt, pa[MAXNODE][20], pa_d[MAXNODE], v[MAXNODE], sz[MAXNODE], sz_tot, mn, c, q, cnt_lt, lt[MAXNODE], dep[MAXNODE];
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
struct pq {
	priority_queue<int> q, del;
	void push(int x) { q.push(x); }
	void erase(int x) { del.push(x); }
	int top() {
		while (del.size() && del.top() == q.top()) { q.pop(); del.pop(); }
		return q.top();
	}
	void pop() {
		while (del.size() && del.top() == q.top()) { q.pop(); del.pop(); }
		q.pop();
	}
	int sec_top() {
		int tmp = top(); pop();
		int tmp2 = top(); push(tmp);
		return tmp2;
	}
	int size() { return q.size() - del.size(); }
} ds[MAXNODE], down[MAXNODE], ans;
struct edge {
	int u, v;
	edge *nxt;
	edge() {};
	edge(int _u, int _v, edge *_nxt) : u(_u), v(_v), nxt(_nxt) {};
} mp[MAXEDGE], *head[MAXNODE];
void add_edge(int u, int v) {
	mp[cnt] = edge(u, v, head[u]);
	head[u] = &mp[cnt++];
	mp[cnt] = edge(v, u, head[v]);
	head[v] = &mp[cnt++];
}
void get_input();
void work();
void dfs(int, int);//
void get_sz(int, int);//
void get_ct(int, int);//
int divide(int, int);//
void light(int);//
void extinguish(int);//
int lca(int, int);//
int dis(int, int);//
void insert(pq&);//
void erase(pq&);//
void get_info(int, int, int);//
int main() {
	get_input();
	work();
	return 0;
}
void work() {
	cnt_lt = n;
	dfs(1, 0);
	divide(1, 0);
	while (q--) {
		char op = get_ch();
		if (op == 'G') {
			if (cnt_lt <= 1) printf("%d\n", cnt_lt - 1); else printf("%d\n", ans.top());
		}
		else {
			int p = read();
			if (lt[p]) {
				extinguish(p); cnt_lt++;
				lt[p] = 0;
			}
			else {
				light(p); cnt_lt--;
				lt[p] = 1;
			}
		}
	}
}
void get_input() {
	n = read();
	int u, v;
	rep0(i, n - 1) {
		u = read(); v = read();
		add_edge(u, v);
	}
	q = read();
}
void insert(pq &q) {
	if (q.size() > 1) ans.push(q.top() + q.sec_top());
}
void erase(pq &q) {
	if (q.size() > 1) ans.erase(q.top() + q.sec_top());
}
void dfs(int p, int fa) {
	dep[p] = dep[fa] + 1;
	pa[p][0] = fa;
	rep1(i, 18) pa[p][i] = pa[pa[p][i - 1]][i - 1];
	iter(i, p) {
		if (i->v == fa) continue;
		dfs(i->v, p);
	}
}
int lca(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	for (int i = 18; i >= 0; i--) if (dep[pa[u][i]] >= dep[v]) u = pa[u][i];
	if (u == v) return v;
	for (int i = 18; i >= 0; i--) if (pa[u][i] != pa[v][i]) u = pa[u][i], v = pa[v][i];
	return pa[u][0];
}
int dis(int u, int v) {
	return dep[u] + dep[v] - dep[lca(u, v)] * 2;
}
void get_info(int p, int fa, int ct) {
	ds[ct].push(dis(p, pa_d[ct]));
	iter(i, p) {
		if (v[i->v] || i->v == fa) continue;
		get_info(i->v, p, ct);
	}
}
void get_sz(int p, int fa) {
	sz[p] = 1;
	iter(i, p) {
		if (v[i->v] || i->v == fa) continue;
		get_sz(i->v, p);
		sz[p] += sz[i->v];
	}
}
void get_ct(int p, int fa) {
	if (max(sz[p], sz_tot - sz[p]) < mn) {
		mn = max(sz[p], sz_tot - sz[p]);
		c = p;
	}
	iter(i, p) {
		if (v[i->v] || i->v == fa)continue;
		get_ct(i->v, p);
	}
}
int divide(int p, int fa) {
	get_sz(p, fa);
	sz_tot = sz[p];
	mn = INF;
	get_ct(p, fa);
	int G = c;
	pa_d[G] = fa;
	v[G] = 1;
	get_info(G, 0, G);
	down[G].push(0);
	iter(i, G) {
		if (v[i->v] || i->v == fa) continue;
		int sG = divide(i->v, G);
		down[G].push(ds[sG].top());
	}
	insert(down[G]);
	return G;
}
void light(int p) {
	erase(down[p]);
	down[p].erase(0);
	insert(down[p]);
	for (int i = p; pa_d[i]; i = pa_d[i]) {
		erase(down[pa_d[i]]);
		if (ds[i].size()) down[pa_d[i]].erase(ds[i].top());
		ds[i].erase(dis(p, pa_d[i]));
		if (ds[i].size()) down[pa_d[i]].push(ds[i].top());
		insert(down[pa_d[i]]);
	}
}
void extinguish(int p) {
	erase(down[p]);
	down[p].push(0);
	insert(down[p]);
	for (int i = p; pa_d[i]; i = pa_d[i]) {
		erase(down[pa_d[i]]);
		if (ds[i].size()) down[pa_d[i]].erase(ds[i].top());
		ds[i].push(dis(p, pa_d[i]));
		if (ds[i].size()) down[pa_d[i]].push(ds[i].top());
		insert(down[pa_d[i]]);
	}
}