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
#define eps 10e-7
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define rep0(j,n) for(int j=0;j<n;++j)
#define rep1(j,n) for(int j=1;j<=n;++j)
#define pb push_back
#define set0(n) memset(n,0,sizeof(n))
#define ll long long
#define iter(i,v) for(edge *i = head[v];i;i = i->nxt)
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
//#define OJ
using namespace std;
char BUF[10000000], *buf;
int read() {
	int x = 0;
	while (!isdigit(*buf)) { buf++; }
	while (isdigit(*buf)) { x = x * 10 + *buf++ - '0'; }
	return x;
}
char get_ch() {
	char c = getchar();
	while (!isalpha(c)) c = getchar();
	return c;
}
const int MAXINT = 100010;
const int MAXNODE = 100010;
ll ans, w[MAXNODE], ps_w[MAXINT], qa[MAXINT];
int st[18][MAXNODE*4]={},seq[MAXNODE*4]={},cnt_seq=0,fst[MAXNODE]={},max_p2[262145]={},no[MAXNODE],stk[MAXNODE],top=0,cnt_bl=1;
int dfn[MAXNODE]={}, cnt_dfn=0, bl[MAXNODE]={}, n=0, m=0, v[MAXINT]={}, c[MAXNODE]={}, dep[MAXNODE]={}, in_ans[MAXNODE]={}, fa[MAXNODE]={}, cnt_eg, sz_b, q, cnt_cd[MAXINT]={}, cnt_mdf = -1, cnt_qr;
struct edge {
	int u, v;
	edge *nxt;
	edge(int _u, int _v, edge *_nxt) {
		u = _u; v = _v; nxt = _nxt;
	}
	edge() {}
}*head[MAXNODE], mp[MAXNODE * 2];
struct op {
	int tp, x, y, lstc, no;
	op(int _x, int _y) {
		tp = 1;
		x = _x;
		y = _y;
	}
	op(int lst, int _x, int _y, int _no) {
		lstc = lst;
		tp = 0;
		if (dfn[_x] > dfn[_y]) swap(_x, _y);
		x = _x;
		y = _y;
		no = _no;
	}
	op() {}
}mdf[MAXINT], qr[MAXINT];
int cmp(const op &a, const op &b) {
	if(bl[a.x]==bl[b.x]&&bl[a.y]==bl[b.y]) {if(bl[a.x]&1)return a.lstc<b.lstc; else return a.lstc>b.lstc;}
	if(bl[a.x]==bl[b.x])  {if(bl[a.x]&1) return bl[a.y]<bl[b.y]; else return bl[a.y]>bl[b.y];}
	return bl[a.x] < bl[b.x];
}
inline void rev(int);
inline void add(int);
inline void remove(int);
inline void add(op&);
inline void remove(op&);
inline void add_edge(int, int);
inline void get_st();
inline void get_input();
inline void work();
inline void solve(int,int);
inline int get_lca(int, int);
//void dfs(int, int);
inline int dfs(int, int);
int main() {
	freopen("in.txt", "r", stdin);
	freopen("out.tle", "w", stdout);
	for(int i=0;i<=17;i++){
		for (int j=(1<<i);j<(1<<(i+1));j++){
			max_p2[j]=i;
		}
	}
	get_input();
	get_st();
	work();
	printf("%d\n",clock());
	return 0;
}
inline void rev(int p) {
	if (in_ans[p]) {
		in_ans[p] = 0;
		ans -= w[cnt_cd[c[p]]] * v[c[p]];
		cnt_cd[c[p]]--;
	}
	else {
		in_ans[p] = 1;
		cnt_cd[c[p]]++;
		ans += w[cnt_cd[c[p]]] * v[c[p]];
	}
}
inline void solve(int p1,int p2){
	while(p1!=p2){
		dep[p1]>dep[p2]?(rev(p1),p1=fa[p1]):(rev(p2),p2=fa[p2]);
	}
}
inline void work() {
	sort(qr, qr + cnt_qr, cmp);
	int l, r, pl, pr, lca, lca2, pq = -1;
	for (int i = pq; i > qr[0].lstc; i--) {
		remove(mdf[i]);
	}
	for (int i = pq + 1; i <= qr[0].lstc; i++) {
		add(mdf[i]);
	}
	pl = l = qr[0].x;
	pr = r = qr[0].y;
	lca = get_lca(l, r);
	solve(pl,pr);
	rev(lca);
	qa[qr[0].no] = ans;
	pq = qr[0].lstc;
	rep1(i, cnt_qr - 1) {
		for (int j = pq; j > qr[i].lstc; j--) {
			remove(mdf[j]);
		}
		for (int j = pq + 1; j <= qr[i].lstc; j++) {
			add(mdf[j]);
		}
		lca = get_lca(l, r);
		lca2 = get_lca(qr[i].x, qr[i].y);
		solve(l,qr[i].x);
		solve(r,qr[i].y);
		rev(lca);
		rev(lca2);
		l = qr[i].x; r = qr[i].y;
		pq = qr[i].lstc;
		qa[qr[i].no] = ans;
	}
	rep0(i, cnt_qr) {
		printf("%lld\n", qa[i]);
	}
}
inline void add_edge(int u, int v) {
	mp[cnt_eg] = edge(u, v, head[u]);
	head[u] = &mp[cnt_eg++];
	mp[cnt_eg] = edge(v, u, head[v]);
	head[v] = &mp[cnt_eg++];
}
inline void get_input() {
	int tp, _u, _v;
	BUF[fread(BUF, 1, 10000000, stdin)]=0;
	buf = BUF;
	n = read(); m = read(); q = read();
	sz_b = ceil(pow(n, 2.0 / 3.0))/2+1;
	rep1(i, m) v[i] = read();
	rep1(i, n) w[i] = read();
	rep1(i, n) ps_w[i] += ps_w[i - 1] + w[i];
	rep1(i, n - 1) {
		_u = read(); _v = read();
		add_edge(_u, _v);
	}
	dfs(1, 0);
	while(top) bl[stk[--top]]=cnt_bl-1;
	rep1(i, n) c[i] = read();
	rep0(i, q) {
		tp = read(); _u = read(); _v = read();
		if (tp == 1) qr[cnt_qr] = op(cnt_mdf, _u, _v, cnt_qr), cnt_qr++;
		else mdf[++cnt_mdf] = op(_u, _v);
	}
}
/*void dfs(int p, int f) {
	fa[p] = f;
	dep[p] = dep[f] + 1;
	no[cnt_dfn]=p;
	dfn[p] = ++cnt_dfn;
	bl[p] = dfn[p] / sz_b;
	fst[p] = cnt_seq;
	seq[cnt_seq++]=dfn[p];
	iter(i, p) {
		if (i->v == f) continue;
		dfs(i->v, p);
		seq[cnt_seq++]=dfn[p];
	}
}*/
inline int dfs(int p, int f) {
	int sz=0;
	fa[p] = f;
	dep[p] = dep[f] + 1;
	no[cnt_dfn]=p;
	dfn[p] = ++cnt_dfn;
	//bl[p] = dfn[p] / sz_b;
	fst[p] = cnt_seq;
	seq[cnt_seq++]=dfn[p];
	iter(i, p) {
		if (i->v == f) continue;
		sz+=dfs(i->v, p);
		seq[cnt_seq++]=dfn[p];
		if (sz>=sz_b){
			while(top) bl[stk[--top]]=cnt_bl;
			cnt_bl++,sz=0;
		}
	}
	stk[top++]=p;
	return sz+1;
}
inline void get_st() {
	rep0(i,cnt_seq) st[0][i]=seq[i];
	for (int i = 1; i <= 17; i++)
		for (int j = 0; j < cnt_seq-(1<<i)+1; j++)
			st[i][j] = min(st[i-1][j],st[i-1][j+(1<<(i-1))]);
}
inline int get_lca(int x, int y) {
	x=fst[x];y=fst[y];
	if(x>y) swap(x,y);
	int l = y-x+1;
	return no[min(st[max_p2[l]][x],st[max_p2[l]][y-(1<<max_p2[l])+1])-1];
}
inline void remove(int p) {
	ans -= w[cnt_cd[p]] * v[p];
	cnt_cd[p]--;
}
inline void add(int p) {
	cnt_cd[p]++;
	ans += w[cnt_cd[p]] * v[p];
}
inline void add(op& cg) {
	//int f = get_lca(l, r), f1 = get_lca(l, cg.x), f2 = get_lca(r, cg.x);
	cg.lstc = c[cg.x];
	c[cg.x] = cg.y;
	if(in_ans[cg.x]){
	//if ((f == f1&&f2 == cg.x) || (f == f2&&f1 == cg.x)) {
		ans -= w[cnt_cd[cg.lstc]] * v[cg.lstc];
		cnt_cd[cg.lstc]--;
		cnt_cd[cg.y]++;
		ans += w[cnt_cd[cg.y]] * v[cg.y];
	}
}
inline void remove(op& cg) {
	//int f = get_lca(l, r), f1 = get_lca(l, cg.x), f2 = get_lca(r, cg.x);
	c[cg.x] = cg.lstc;
	//if ((f == f1&&f2 == cg.x) || (f == f2&&f1 == cg.x)) {
	if(in_ans[cg.x]){
		ans -= w[cnt_cd[cg.y]] * v[cg.y];
		cnt_cd[cg.y]--;
		cnt_cd[cg.lstc]++;
		ans += w[cnt_cd[cg.lstc]] * v[cg.lstc];
	}
}
