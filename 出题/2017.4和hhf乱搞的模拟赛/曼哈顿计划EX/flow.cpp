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
#include <sstream>
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
#define TO(j) printf("j: %d\n",j);
//#define OJ
using namespace std;
const int MAXINT = 100010;
const int MAXNODE = 100010;
const int MAXEDGE = 2 * MAXNODE;
char BUF, *buf;
int read() {
	char c = getchar();
	int f = 1, x = 0;
	while (!isdigit(c)) {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (isdigit(c)) {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return f * x;
}
char get_ch() {
	char c = getchar();
	while (!isalpha(c)) c = getchar();
	return c;
}
//------------------- Head Files ----------------------//
struct edge {
	int u, v, c;
	edge* nxt;
	edge() {}
	edge(int _u, int _v, edge *_nxt, int _c = 1): u(_u), v(_v), nxt(_nxt), c(_c) {}
	edge(int _u, int _v, int _c): u(_u), v(_v), c(_c) {}
}*head[MAXNODE], mp[MAXEDGE], mp_t[MAXEDGE];
bool operator < (const edge &a,const edge &b) {
	return a.c>b.c;
}
struct query {
	int v, id;
	query() {};
	query(int _v, int _id): v(_v), id(_id) {}
} qr[MAXINT];
bool operator < (const query &a, const query &b) {
	return a.v < b.v;
}
int qu[MAXNODE], dis[MAXNODE], n, m, q, w[MAXNODE], ans[MAXINT], fa_t[MAXINT], cnt_t, cnt, fa[MAXNODE], v_fa[MAXNODE];
void add_edge(int, int);
void add_edge_t(int, int, int);
int dinic(int, int);
int dfs(int, int, int);
int bfs(int, int);
void get_input();
void work();
void init();
int find_fa(int);
edge* rev(edge*);
int main() {
	cnt=0;cnt_t=0;memset(head,0,sizeof(head));
	get_input();
	work();
	return 0;
}
void work() {
	memset(ans,-1,sizeof(ans));
	for (int i = 2; i <= n; i++) fa_t[i] = 1;
	for (int i = 2; i <= n; i++) {
		init();
		add_edge_t(i, fa_t[i], dinic(i, fa_t[i]));
		for (int j = i + 1; j <= n; j++) if (dis[j] != -1 && fa_t[j] == fa_t[i]) fa_t[j] = i;
	}
	sort(mp_t,mp_t+cnt_t);
	int ans_p = 0, k = 0, cut_p = INF;
	rep1(i, n) fa[i] = i, v_fa[i] = w[i], ans_p = max(ans_p, w[i]);
	rep0(i, q) {
		for (; ans_p < qr[i].v && k < cnt_t; k++) {
			int u = find_fa(mp_t[k].u), v = find_fa(mp_t[k].v);
			cut_p = min(cut_p, mp_t[k].c);
			ans_p = max(ans_p, v_fa[u] + v_fa[v]);
			fa[u] = v;
			v_fa[v]+=v_fa[u];
		}
		if(ans_p >= qr[i].v) ans[qr[i].id] = cut_p;
	}
	rep0(i, q) if (ans[i] == INF) printf("nan\n");
	else if(ans[i]==-1) printf("Nuclear launch detected\n");
	else printf("%d\n", ans[i]);
}
int find_fa(int p) {
	return p == fa[p] ? p : fa[p] = find_fa(fa[p]);
}
void get_input() {
	n = read();
	m = read();
	q = read();
	rep1(i, n) w[i] = read();
	rep1(i, m) {
		int u = read(), v = read();
		if(u==v) continue;
		add_edge(u, v);
	}
	rep0(i, q) {
		qr[i].v = read();
		qr[i].id = i;
	}
	sort(qr, qr + q);
}
edge* rev(edge* e) {
	return &mp[(e - mp) ^ 1];
}
void init() {
	rep0(i, cnt) mp[i].c = 1;
}
void add_edge(int u, int v) {
	mp[cnt] = edge(u, v, head[u]);
	head[u] = &mp[cnt++];
	mp[cnt] = edge(v, u, head[v]);
	head[v] = &mp[cnt++];
}
void add_edge_t(int u, int v, int c) {
	mp_t[cnt_t++] = edge(u, v, c);
}
int bfs(int u, int v) {
	int p;
	memset(dis, -1, sizeof(dis));
	dis[u] = 1;
	int *h, *t;
	h = t = qu;
	*t++ = u;
	while (h != t) {
		p = *h++;
		iter(i, p) {
			if (i->c && dis[i->v] == -1) {
				dis[i->v] = dis[p] + 1;
				*t++ = i->v;
			}
		}
	}
	return dis[v] != -1;
}
int dfs(int p, int v, int flow) {
	if (p == v) return flow;
	int flow_p = 0, t;
	iter(i, p) {
		if (dis[i->v] == dis[p] + 1 && i->c && (t = dfs(i->v, v, min(flow - flow_p, i->c)))) {
			i->c -= t;
			rev(i)->c += t;
			flow_p += t;
		}
	}
	if(!flow_p) dis[p]=-1;
	return flow_p;
}
int dinic(int u, int v) {
	int ans = 0, t = 0;
	while (bfs(u, v)) while ((t = dfs(u, v, INF))) ans += t;
	return ans;
}
