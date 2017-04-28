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
#define gt(i) (1ull<<(63-i))
//#define OJ
using namespace std;
const int MAXINT = 1010;
const int MAXNODE = 100010;
const int MAXEDGE = 2 * MAXNODE;
char BUF, *buf;
ull read() {
	char c = getchar(); ull x = 0;
	while (!isdigit(c)) { c = getchar(); }
	while (isdigit(c)) { x = x * 10 + c - '0'; c = getchar(); }
	return x;
}
char get_ch() {
	char c = getchar();
	while (!isalpha(c)) c = getchar();
	return c;
}
//------------------- Head Files ----------------------//

ull lb[65];
int tp[65], cnt, n;
struct ore {
	ull w, no;
}a[MAXINT];
bool operator < (const ore &a, const ore &b) {
	return a.w>b.w;
}
void get_input();
void work();
int main() {
	get_input();
	work();
	return 0;
}
void work() {
	memset(tp, -1, sizeof(tp));
	ull ans = 0;
	rep0(i, n) {
		for(int j=63;j>=0;j--) {
			if (a[i].no>>j) {
				if (lb[j]) a[i].no ^= lb[j]; else {
					lb[j] = a[i].no;
					break;
				}
			}
		}
		if (!a[i].no) continue;
		else ans += a[i].w;
	}
	printf("%llu\n", ans);
}
void get_input() {
	n = read();
	rep0(i, n) {
		a[i].no = read();
		a[i].w = read();
	}
	sort(a, a + n);
}

/*
按w排序后贪心尝试加入线性基
*/