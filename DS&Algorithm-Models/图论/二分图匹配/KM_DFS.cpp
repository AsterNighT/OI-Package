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
//#define OJ
using namespace std;
char BUF[200000000], *buf;
int read() {
	int x = 0;
	while (!isdigit(*buf)) { buf++; }
	while (isdigit(*buf)) { x = x * 10 + *buf++ - '0';}
	return x;
}
char get_ch() {
	char c = getchar();
	while (!isalpha(c)) c = getchar();
	return c;
}
const int MAXINT = 1000;
const int MAXNODE = 410;
int w[MAXNODE][MAXNODE], rw[MAXNODE][MAXNODE], nl, nr, m, l, r,tm=0;
int match_r[MAXNODE], match_l[MAXNODE];
int vis_l[MAXNODE], vis_r[MAXNODE];
int slack[MAXNODE];
int ex_l[MAXNODE], ex_r[MAXNODE];
int dfs(int p) {
	int d;
	vis_l[p] = tm;
	for(int i=r;i>=1;i--) {
		if (vis_r[i]==tm) continue;
		d = ex_l[p] + ex_r[i] - w[p][i];
		if (d == 0) {
			vis_r[i] = tm;
			if (!match_r[i] || dfs(match_r[i])) {
				match_r[i] = p;
				match_l[p] = i;
				return 1;
			}
		}
		else slack[i] = min(slack[i], d);
	}
	return 0;
}
void km() {
	ll ans;
	memset(match_r, 0, sizeof(match_r));
	memset(match_l, 0, sizeof(match_l));
	memset(ex_r, 0, sizeof(ex_r));
	memset(ex_l, 0, sizeof(ex_l));
	rep1(i, l) rep1(j, r) ex_l[i] = max(ex_l[i], w[i][j]);
	rep1(i, l) {
		memset(slack, INF, sizeof(slack));
		while (1) {
			int d = INF;
			tm++;
			if (dfs(i)) break;
			rep1(i, r) d = (vis_r[i]!=tm) ? min(slack[i], d):d;
			rep1(i, l) ex_l[i] = (vis_l[i]==tm)? ex_l[i] - d:ex_l[i];
			rep1(i, r) if (vis_r[i]==tm) ex_r[i] += d; else slack[i] -= d;
		}
	}
	ans = 0;
	rep1(i, l) {
		ans += ex_l[i];
	}
	rep1(i, r) {
		ans += ex_r[i];
	}
	cout << ans << endl;
	if (nl > nr) {
		rep1(i, nl) if (!match_r[i] || !rw[match_r[i]][i]) printf("0 "); else printf("%d ", match_r[i]);
	}
	else {
		rep1(i, nl) if (!rw[i][match_l[i]]) printf("0 "); else printf("%d ", match_l[i]);
	}
	putchar('\n');
}
int main() {
	freopen("in.txt","r",stdin);
	fread(BUF, 1, 200000000, stdin);
	buf = BUF;
	nl = read(); nr = read(); m = read();
	int u, v, c;
	l = min(nl, nr);  r = max(nl, nr);
	rep1(i, m) {
		u = read(); v = read(); c = read();
		if (nl > nr) w[v][u] = c, rw[v][u] = 1; else w[u][v] = c, rw[u][v] = 1;
	}
	km();
	return 0;
}


