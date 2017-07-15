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
#define max(a,b) (((a)>(b))?(a):(b))
#define min(a,b) (((a)<(b))?(a):(b))
#define print_runtime printf("Running time:%.3lfs\n",double(clock())/1000.0)
#define TO(j) printf(#j": %d\n",j);
//#define OJ
using namespace std;
const int MAXINT = 401000;
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
int cnt_qr, sa[MAXINT], rk[MAXINT], trk[MAXINT], height[MAXINT], tsa[MAXINT], tstr[MAXINT], cnt[MAXINT], len, s[MAXINT], n, m, color[MAXINT];
int st[18][MAXINT], maxp[MAXINT*2], ans=0, cnt_c[50010], cnt_miao[20010], rp;
pair<int, int> qr[50010];
struct query {
	int l, r, id;
	query() {}
	query(int _l, int _r, int _id) : l(_l), r(_r), id(_id) {}
} mo[MAXINT];
bool operator < (const query &a, const query &b) {
	return (a.l / 447 == b.l / 447) ? a.r < b.r : (a.l / 447 < b.l / 447);
}
int cmp(int *a, int p1, int p2, int l) {
	return a[p1] == a[p2] && a[p1 + l] == a[p2 + l];
}
void get_st() {
	rep0(i, 18) {
		for (int j = (1 << i); j < (1 << (i + 1)); j++) maxp[j] = i;
	}
	rep0(i, len) st[0][i] = height[i];
	rep1(i, 17) rep0(j, len - (1 << i) + 1) st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
}
int gt(int l, int r) { //[l,r]
	int pw = maxp[r - l + 1];
	return min(st[pw][l], st[pw][r - (1 << pw) + 1]);
}
void get_sa() {
	int i, j, k, sz = MAXINT;
	for (i = 0; i < sz; i++) cnt[i] = 0;
	for (i = 0; i < len; i++) cnt[trk[i] = s[i]]++;
	for (i = 1; i < sz; i++) cnt[i] += cnt[i - 1];
	for (i = len - 1; i >= 0; i--) sa[--cnt[s[i]]] = i;
	for (j = 1, k = 1; k < len; j <<= 1, sz = k) {
		for (k = 0, i = len - j; i < len; i++) tsa[k++] = i;
		for (i = 0; i < len; i++) if (sa[i] >= j) tsa[k++] = sa[i] - j;
		for (i = 0; i < len; i++) tstr[i] = trk[tsa[i]];

		for (i = 0; i < sz; i++) cnt[i] = 0;
		for (i = 0; i < len; i++) cnt[tstr[i]]++;
		for (i = 1; i < sz; i++) cnt[i] += cnt[i - 1];
		for (i = len - 1; i >= 0; i--) sa[--cnt[tstr[i]]] = tsa[i];
		for (swap(tsa, trk), k = 1, trk[sa[0]] = 0, i = 1; i < len; i++) {
			trk[sa[i]] = cmp(tsa, sa[i], sa[i - 1], j) ? k - 1 : k++;
		}
	}
}
void get_height() {
	int i, j, k;
	for (i = 0; i < len; i++) rk[sa[i]] = i;
	for (i = 0, k = 0; i < len - 1; height[rk[i++]] = k) {
		for (k ? k-- : 0, j = sa[rk[i] - 1]; s[i + k] == s[j + k]; k++);
	}
}
query get_query(int id) {
	int pos = rk[qr[id].first], l = qr[id].second;
	query ret; ret.id = id;
	if (pos == len - 1) pos = pos + 1;
	else {
		if (height[pos] < l) pos = pos + 1;
	}
	if (height[pos] < l) return query(-1, -1, -1);
	int mid, lb = pos, rb = len;
	while (rb - lb > 1) {
		mid = (lb + rb) / 2;
		if (gt(pos, mid) < l) rb = mid; else lb = mid;
	}
	ret.r = lb;
	lb = 0; rb = pos;
	while (rb - lb > 1) {
		mid = (lb + rb) / 2;
		if (gt(mid, pos) < l) lb = mid; else rb = mid;
	}
	ret.l = rb - 1;
	return ret;
}
void get_input();
void work();
void append() {
	int l = read();
	rep0(i, l) {
		int w = read();
		s[len++] = w + 1;
	}
	s[len++] = 0;
}
void add(int v) {
	cnt[v]++;
	if (v != 0 && cnt[v] == 1) {
		ans++;
		cnt_miao[v] += cnt_qr - rp;
	}
}
void del(int v) {
	cnt[v]--;
	if (v!=0 && cnt[v] == 0) {
		ans--;
		cnt_miao[v] -= cnt_qr - rp;
	};
}
int main() {
	get_input();
	work();
	return 0;
}
void work() {
	get_sa();
	get_height();
	get_st();
	rep0(i, m) {
		mo[cnt_qr] = get_query(i);
		if (mo[cnt_qr].id != -1) cnt_qr++;
	}
	sort(mo, mo + cnt_qr);
	memset(cnt, 0, sizeof(cnt));
	int l = 0, r = -1;
	for (rp = 0; rp < cnt_qr; rp++) {
		for (; l < mo[rp].l; del(color[sa[l]]), l++);
		for (; l > mo[rp].l; l--, add(color[sa[l]]));
		for (; r > mo[rp].r; del(color[sa[r]]), r--);
		for (; r < mo[rp].r; r++, add(color[sa[r]]));
		cnt_c[mo[rp].id] = ans; l = mo[rp].l; r = mo[rp].r;
	}
	rep0(i, m) printf("%d\n", cnt_c[i]);
	rep1(i, n) printf("%d ", cnt_miao[i]);
	putchar('\n');
}
void get_input() {
	n = read(); m = read();
	int l;
	rep1(i, n) {
		int p = len;
		append(); append();
		for (int j = p; j < len; j++) color[j] = i;
	}
	rep0(i, m) {
		int p = len;
		append();
		for (int j = p; j < len; j++) color[j] = 0;
		qr[i] = make_pair(p, len - p - 1);
	}
}
/*
2 1
2 2 1 1 1
2 2 1 1 1
2 2 1
*/