#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>
#include <cmath>
#include <map>
#include <unordered_set>
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
const int MAXNODE = 50010;
const int MAXEDGE = 100010;
int cnt, n, sz[MAXNODE], v[MAXNODE], s, ct, mn, sz_tot, ok = 0, w[MAXNODE], k, T, t[11] = {};
set<int> hs;
struct edge {
	int u, v;
	edge *nxt;
	edge() {}
	edge(int _u, int _v, edge *_nxt) : u(_u), v(_v), nxt(_nxt) {}
} mp[MAXEDGE], *head[MAXNODE];
int read() {
	char c = getchar(); int f = 1, x = 0;
	while (!isdigit(c)) { if (c == '-') f = -1; c = getchar(); }
	while (isdigit(c)) { x = x * 10 + c - '0'; c = getchar(); }
	return f * x;
}
int calc_sg(int a) {
	if (k == 1) return a;
	if (k == 2) {
		if (s & 1) return (a & 1);
		int m = a % (s + 1);
		if (m == s) return 2;
		else return (m & 1);
	}
	if (k == 3) return (a / s);
	if (k == 4) {
		if (a == 0) return 0;
		if (a % 4 == 1 || a % 4 == 2) return a;
		if (a % 4 == 0) return a - 1;
		if (a % 4 == 3) return a + 1;
	}
}
char get_ch() {
	char c = getchar();
	while (!isalpha(c)) c = getchar();
	return c;
}
void add_edge(int u, int v) {
	mp[cnt] = edge(u, v, head[u]);
	head[u] = &mp[cnt++];
	mp[cnt] = edge(v, u, head[v]);
	head[v] = &mp[cnt++];
}
void get_ct(int p, int fa) {
	if (max(sz[p], sz_tot - sz[p]) < mn) {
		mn = max(sz[p], sz_tot - sz[p]);
		ct = p;
	}
	iter(i, p) {
		if (v[i->v] || i->v == fa) continue;
		get_ct(i->v, p);
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
void get_ans(int p, int fa, int xorv) {
	if (hs.count(xorv ^ w[ct])) ok = 1;
	iter(i, p) {
		if (v[i->v] || i->v == fa) continue;
		get_ans(i->v, p, xorv ^ w[i->v]);
	}
}
void del_info(int p, int fa, int xorv) {
	hs.erase(xorv);
	iter(i, p) {
		if (v[i->v] || i->v == fa) continue;
		del_info(i->v, p, xorv ^ w[i->v]);
	}
}
void get_info(int p, int fa, int xorv) {
	hs.insert(xorv);
	iter(i, p) {
		if (v[i->v] || i->v == fa) continue;
		get_info(i->v, p, xorv ^ w[i->v]);
	}
}
void divide(int p) {
	hs.clear();
	get_sz(p, 0);
	sz_tot = sz[p];
	mn = INF;
	get_ct(p, 0);
	p = ct;
	v[p] = 1;
	if(w[p]==0) ok=1;
	iter(i, p) {
		if (v[i->v])continue;
		get_ans(i->v, p, w[i->v]);
		get_info(i->v, p, w[i->v]);
	}
	iter(i, p) {
		if (v[i->v])continue;
		divide(i->v);
	}
}
void get_input();
void work();
int main() {
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	T = read();
	while (T--) {
		ok=0;cnt=0;
		memset(v,0,sizeof(v));
		memset(head,0,sizeof(head));
		get_input();
		work();
	}
	return 0; 
}
void work() {
	divide(1);
	printf("%s\n", ok ? "Mutalisk ride face how to lose?" : "The commentary cannot go on!");
}
void get_input() {
	n = read();
	rep0(i, n - 1) {
		int u = read(), v = read();
		add_edge(u, v);
	}
	rep1(i, n) w[i] = read();
	//rep1(i,n) printf("%d\n",w[i]);
	k = read();
	if (k == 2 || k == 3) s = read();
	rep1(i, n) w[i] = calc_sg(w[i]);
}
