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
#include <list>
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
const int MAXINT = 1000010;
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
char s[MAXINT];
int n, k;
int stk[26][MAXINT],tp[26];
struct cond {
	cond *c[26];
	int cnt;
	cond() { cnt = 1; }
}a[MAXINT];
void get_input();
void work();
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("tst.out", "w", stdout);
	get_input();
	work();
	return 0;
}
void work() {
	for (int i = n; i; i--) stk[int(s[i])][tp[s[i]]++]=i;
	a[0].cnt = 0;
	rep0(i, n + 1) {
		rep0(j, 26) {
			while (tp[j] && stk[j][tp[j]-1] <= i) tp[j]--;
			if (!tp[j]) a[i].c[j] = NULL;
			else a[i].c[j] = &a[stk[j][tp[j] - 1]];
		}
	}
	for (int i = n; i >= 0; i--)	rep0(j, 26) if (a[i].c[j]) a[i].cnt = min(INF, a[i].cnt+a[i].c[j]->cnt);
	cond* p = &a[0];
	while (1) {
		rep0(i, 26) {
			if (!p->c[i]) continue;
			if (k>p->c[i]->cnt) k -= p->c[i]->cnt;
			else {
				putchar('a' + i);
				p = p->c[i];
				k -= 1;
				break;
			}
		}
		if (!k) break;
	}
	putchar('\n');
}
void get_input() {
	n = read(); k = read();
	scanf("%s", s + 1);
	rep1(i, n) s[i] -= 'a';
}

