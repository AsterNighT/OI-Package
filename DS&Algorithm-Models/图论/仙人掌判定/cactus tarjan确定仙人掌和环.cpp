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
#define MOD 998244353
#define rep0(j,n) for(int j=0;j<n;++j)
#define rep1(j,n) for(int j=1;j<=n;++j)
#define pb push_back
#define set0(n) memset(n,0,sizeof(n))
#define ll long long
#define iter(i,v) for(edge* i = head[v]; i; i=i->next)
//#define OJ UOJ
using namespace std;
int read() {
	char c = getchar(); int f = 1, x = 0;
	while (!isdigit(c)) { if (c == '-') f = -1; c = getchar(); }
	while (isdigit(c)) { x = x * 10 + c - '0'; c = getchar(); }
	return f*x;
}
const int MAXINT = 500010;
int dfn[MAXINT], low[MAXINT], bl[MAXINT], cnt_b, cnt_dfs, m, n, t, cnt, stk[MAXINT], top, is_cactus, ds[MAXINT];
ll pr[MAXINT];
struct edge {
	int u, v;
	edge *next;
	edge(int _u, int _v, edge *_next) :u(_u), v(_v), next(_next) {}
	edge() {}
}*head[MAXINT], e[MAXINT * 2];
void add_edge(int u, int v) {
	e[cnt] = edge(u, v, head[u]);
	head[u] = &e[cnt++];
	e[cnt] = edge(v, u, head[v]);
	head[v] = &e[cnt++];
}
void pre() {
	pr[0] = 1; pr[1] = 1;
	for (int i = 2; i < 500001; i++) {
		pr[i] = (pr[i - 1] + (pr[i - 2] * (i - 1)) % MOD) % MOD;
	}
}
void init() {
	cnt = cnt_dfs = cnt_b = top =  0;
	is_cactus = 1;
	memset(head, NULL, (n+10)*sizeof(edge*));
	memset(dfn, 0, (n+10)*sizeof(int));
	memset(low, 0, (n+10)*sizeof(int));
	memset(bl, 0xff, (n+10)*sizeof(int));
	memset(ds, 0,(n+10)*sizeof(int));
}
void get_input() {
	n = read(); m = read();
	int u, v;
	rep0(i, m) {
		u = read();
		v = read();
		add_edge(u, v);
	}
}
int tarjan(int p, int fa) {
	dfn[p] = low[p] = ++cnt_dfs;
	stk[top++] = p;
	int flag= 0;
	iter(i, p) {
		if (i->v == fa) continue;
		if (!dfn[i->v]){
			//printf("%d %d\n",i->v,p);
			tarjan(i->v, p);
			low[p] = min(low[p], low[i->v]);
			if (low[i->v] < dfn[p]) {
				if (flag) is_cactus = 0;
				flag = 1;
			}
		}else{
			low[p] = min(low[p],dfn[i->v]);
			if(dfn[i->v]<dfn[p]){
				if (flag) is_cactus = 0;
				flag = 1;
			}
		}
	}
	if (dfn[p] == low[p]) {
		while (1) {
			top--;
			bl[stk[top]] = p;
			if(stk[top]==p) break;
		}
	}
	return 0;
}
int work() {
	ll ans = 1;
	tarjan(1, 0);
	if (!is_cactus) return printf("0\n"), 0;
	rep0(i, cnt) if (bl[e[i].u] != bl[e[i].v]) ds[e[i].u]++;
	rep1(i, n) ans = ans*pr[ds[i]] % MOD;
	printf("%lld\n", ans);
	return 0;
}
int main() {
	t = read();
	pre();
	while (t--) {
		init();
		get_input();
		work();
	}
	return 0;
}


