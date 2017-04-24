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
#define TO(j) printf("j: %d\n",j);
//#define OJ
using namespace std;
const int MAXINT = 200010;
const int MAXNODE = 200010;
const int MAXEDGE = 2 * MAXNODE;
const int BLOCK_S = 400;
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
int cnt_bl[MAXINT], cnt[MAXINT], cnt_num[MAXINT], sz_b, lb, rb, n, q, a[MAXINT], ans[MAXINT], bl[MAXINT], b[MAXINT], cnt_b;
struct query {
	int l, r, k, no;
	query(int _l, int _r, int _k, int _no): l(_l), r(_r), k(_k), no(_no) {}
	query() {}
} qr[MAXINT];
bool operator < (const query &a, const query &b) {
	return bl[a.l] == bl[b.l] ? (bl[a.l] & 1 ? a.r<b.r: a.r>b.r) : bl[a.l] < bl[b.l];
}
void get_input();
void work();
void del(int);
void add(int);
int calc(int);
int main() {
	//freopen("mo.in", "r", stdin);
	//freopen("mo.out", "w", stdout);
	get_input();
	work();
	return 0;
}
void work() {
	lb = 0, rb = -1;
	rep0(i, q) {
		for (int j = lb; j < qr[i].l; j++) del(j);
		for (int j = lb - 1; j >= qr[i].l; j--) add(j);
		for (int j = rb + 1; j <= qr[i].r; j++) add(j);
		for (int j = rb; j > qr[i].r; j--) del(j);
		lb = qr[i].l;
		rb = qr[i].r;
		ans[qr[i].no] = calc(qr[i].k);
	}
	rep0(i, q) printf("%d\n", ans[i]);
}
void get_input() {
	n = read();
	q = read();
	sz_b = ceil(sqrt(n));
	rep0(i, n) b[i] = a[i] = read(), bl[i] = i / sz_b;
	sort(b, b + n);
	cnt_b = unique(b, b + n) - b;
	rep0(i, n) a[i] = lower_bound(b, b + cnt_b, a[i]) - b;
	rep0(i, q) {
		qr[i].l = read() - 1;
		qr[i].r = read() - 1;
		qr[i].k = read();
		qr[i].no = i;
	}
	sort(qr, qr + q);
	//cnt_bl[0] = cnt[0] = cnt_b;
}
void add(int p) {
	if (cnt_num[a[p]]) {
		cnt[cnt_num[a[p]]]--;
		cnt_bl[bl[cnt_num[a[p]]]]--;
	}
	cnt_num[a[p]]++;
	cnt[cnt_num[a[p]]]++;
	cnt_bl[bl[cnt_num[a[p]]]]++;
}
void del(int p) {
	cnt[cnt_num[a[p]]]--;
	cnt_bl[bl[cnt_num[a[p]]]]--;
	cnt_num[a[p]]--;
	if (cnt_num[a[p]]) {
		cnt[cnt_num[a[p]]]++;
		cnt_bl[bl[cnt_num[a[p]]]]++;
	}
}
int calc(int k) {
	int p = INF;
	rep0(i, BLOCK_S) if (cnt_bl[i] >= k) {
		p = i;
		break;
	} else k -= cnt_bl[i];
	if (p == INF) return -1;
	rep0(i, BLOCK_S) if (cnt[sz_b * p + i] >= k) return sz_b * p + i;
	else k -= cnt[sz_b * p + i];
}
