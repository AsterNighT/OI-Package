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
#define iter(i,v) for(edge *i=head[v];i;i=i->next)
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
//#define OJ
using namespace std;
const int MAXINT = 10010;
int k, s[MAXINT], m;
int sg[MAXINT], v[MAXINT];
int read() {
	char c = getchar(); int f = 1, x = 0;
	while (!isdigit(c)) {if (c == '-') f = -1; c = getchar();}
	while (isdigit(c)) {x = x * 10 + c - '0'; c = getchar();}
	return f * x;
}
char get_ch() {
	char c = getchar();
	while (!isalpha(c)) c = getchar();
	return c;
}
void get_sg() {
	memset(sg, 0, sizeof(sg));
	rep1(i, 10000) {
		rep0(j, k) if (i - s[j] >= 0) v[sg[i - s[j]]] = 1;
		rep0(j, 10001) if (!v[j]) {sg[i] = j; break;}
		rep0(j, k) if (i - s[j] >= 0) v[sg[i - s[j]]] = 0;
	}
}
void get_input();
void work();
int main() {
	freopen("in.txt","r",stdin);
	while (1) {
		k = read();
		if (!k)break;
		get_input();
		work();
	}
	return 0;
}
void work() {
	get_sg();
	int t;
	while (m--) {
		int h = read();
		int ans = 0;
		while (h--) {
			t = read();
			ans ^= sg[t];
		}
		putchar(ans?'W':'L');
	}
	putchar('\n');
}
void get_input() {
	rep0(i, k) s[i] = read();
	m = read();
}
