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
#define iter(i,v) for(edge *i = head[v];i;i=i->nxt)
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
//#define OJ
using namespace std;
char BUF[2000000*7*4],*buf;
int read() {
	int x = 0;
	while (!isdigit(*buf)) { buf++; }
	while (isdigit(*buf)) { x = x * 10 + *buf++ - '0'; }
	return x;
}
int read_m() {
	int f = 1, x = 0;
	while (!isdigit(*buf)) { if (*buf++ == '-') f = -1;}
	while (isdigit(*buf)) { x = x * 10 + *buf++ - '0'; }
	return f*x;
}
char get_ch() {
	char c = getchar();
	while (!isalpha(c)) c = getchar();
	return c;
}
const int MAXINT = 1000;
const int MAXNODE = 200010;
const int MAXEDGE = 400010;
struct edge {
	int u, v;
	edge *nxt;
	edge(int _u, int _v, edge *_nxt) {
		u = _u; v = _v; nxt = _nxt;
	}
	edge() {}
}*head[MAXNODE], mp[MAXEDGE];
int n, m, cnt, a[MAXNODE], b[MAXNODE], v[MAXNODE], sz[MAXNODE], mx_sz, ct, pmin, ok;

double c[MAXNODE], mint[MAXNODE] = {};
void add_edge(int, int);
void get_input();
void tree_divide(int p);
void work();
void get_sz(int, int);
void get_ct(int, int);
void add_info(int, int, double, int);
void get_ans(int, int, double, int);
int check(double k) {
	rep1(i, n) c[i] = a[i] - b[i] * k;
	ok = 0;
	memset(v, 0, sizeof(v));
	tree_divide(1);
	if (ok) return 1; else return 0;
}
int main() {
	freopen("cdcq_b.in", "r", stdin);
	freopen("cdcq_b.out", "w", stdout);
	get_input();
	work();
	return 0;
}
void add_edge(int u, int v) {
	mp[cnt] = edge(u, v, head[u]);
	head[u] = &mp[cnt++];
	mp[cnt] = edge(v, u, head[v]);
	head[v] = &mp[cnt++];
}
void get_input() {
	BUF[fread(BUF,1,2000000*28,stdin)]=0;
	buf=BUF;
	n = read(); m = read_m();
	int u, v;
	rep1(i, n) a[i] = read();
	rep1(i, n) b[i] = read();
	rep0(i, n - 1) {
		u = read(); v = read();
		add_edge(u, v);
	}
}
void work() {
	double ans = 1e18;
	rep1(i, m) mint[i] = 1e18;
	if (m == -1) {
		rep1(i, n) ans = min(ans, a[i] / double(b[i]));
		printf("%.2lf\n", ans);
	}
	else {
		double l = 0, r = 200010, mid;
		int t = 50;
		while (t--) {
			mid = (l + r) / 2;
			if (check(mid)) r = mid;
			else l = mid;
		}
		if(l>200000) printf("-1\n"); 
		else printf("%.2lf\n", l);
		//printf("%d\n",clock());
	}

}
void tree_divide(int p) {
	get_sz(p, 0);
	mx_sz = sz[p]; pmin = INF;
	rep1(i, mx_sz) mint[i] = 1e18;
	mint[0] = 0;ct=p;
	get_ct(p, 0);
	p = ct;
	if (m == 1 && c[ct] <= 0) ok = 1;
	iter(i, p) {
		if (v[i->v]) continue;
		get_ans(i->v, p, c[i->v], 1);
		add_info(i->v, p, c[i->v], 1);
	}
	v[p] = 1;
	iter(i, p) {
		if (v[i->v]) continue;
		tree_divide(i->v);
	}
}
void get_ans(int p, int fa, double tmp, int l) {
	if(l+1>m) return ;
	if (tmp + mint[m - l - 1] + c[ct] <= 0) ok = 1;
	iter(i, p) {
		if (v[i->v] || i->v == fa) continue;
		get_ans(i->v, p, tmp + c[i->v], l + 1);
	}
}
void add_info(int p, int fa, double tmp, int l) {
	if(l+1>m) return ;
	mint[l] = min(mint[l], tmp);
	iter(i, p) {
		if (v[i->v] || i->v == fa) continue;
		add_info(i->v, p, tmp + c[i->v], l + 1);
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
	iter(i, p) {
		if (v[i->v] || i->v == fa) continue;
		get_ct(i->v, p);
		if (max(sz[p], mx_sz - sz[p]) < pmin) {
			pmin = max(sz[p], mx_sz - sz[p]);
			ct = p;
		}
	}
}
/*
【题目描述】


永琳需要协助紫解决异变！
在某个满月的夜晚，幻想乡的结界出现了异常，虽然目前还没有找到原因，不过有一点可以肯定的是，这次异变一定和满月有关。间隙妖怪紫在试图修复结界时需要永琳帮她排除满月产生的干扰，为了保护辉夜公主，永琳必须协助紫解决这次异变，所以她打算再次使用符卡"秘术「天文密葬法」"来用虚假的月亮替换真实的满月，但是她在使用符卡的时候出现了一些问题。
"秘术「天文密葬法」"由n个使魔组成，每个使魔都有一个能值和一个波值，同时存在n-1条能量通道将这n个使魔连接起来，并且每个使魔都能通过能量通道和其它所有使魔相连。
完成天文密葬法的关键步骤是在这n个使魔中找到一条用能量通道连接起来的路径，将大部分能量集中于这条路径来展开法术，然而路径上的使魔在法术张开时会产生共振，产生一个干扰值，干扰值等于路径上所有使魔能值的和除以波值的和。
为了确保计划顺利进行，永琳需要选择一条长度为m且干扰值最小的路径，虽然作为月之头脑，但此时永琳需要集中精力展开法术，所以她向你求助。
永琳在知道一个干扰值后就能快速找到这个干扰值对应的路径，你只需要告诉她所有路径中干扰值最小的路径干扰值是多少
答案四舍五入到小数点后两位

【输入格式】


第一行一个整数n,m，意义如上
如果m为-1则表示对长度没有限制
第二行n个整数，第i个整数ai表示第i个使魔的能值
第三行n个整数，第i个整数bi表示第i个使魔的波值
接下来n-1行，每行两个整数l,r，表示有一条能量路径连接第l个使魔和第r个使魔
一行中的所有整数均用空格隔开

【输出格式】


如果不存在长度为m的链，请输出-1
否则一行一个浮点数，表示干扰值最小的路径干扰值是多少

【样例输入1】


3 2
2 3 3
6 6 6
1 2
2 3

【样例输出1】

0.42
【样例输入2】


9 3
9 4 4 1 6 5 1 9 5
8 3 3 1 5 4 1 8 4
1 2
2 3
3 4
3 5
1 6
6 7
7 8
6 9

【样例输出2】

1.15
【数据范围】

数据标号	n	m	ai,bi
1	<=10	=1	<=200000
2
3	<=1000	<=n
4
5
6
7	<=30000
8
9
10
11
12
13
14
15
16
17	<=200000	=-1
18
19
20
*/