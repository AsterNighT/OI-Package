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
int w[MAXNODE][MAXNODE], rw[MAXNODE][MAXNODE], nl, nr,n, m, l, r,tm=0;
int match_r[MAXNODE], match_l[MAXNODE];
int vis_l[MAXNODE], vis_r[MAXNODE];
int slack[MAXNODE],q[MAXINT],h,t,pre[MAXNODE];
int ex_l[MAXNODE], ex_r[MAXNODE];
void aug(int v){
	while(v){match_r[v]=pre[v]; swap(v,match_l[pre[v]]);}
}
int bfs() {
	int p;
	ll d;
	while(h!=t){
		p=q[h++];
		rep1(i,n) if(vis_r[i]!=tm){
			d=ex_l[p]+ex_r[i]-w[p][i];
			if(!d){
				pre[i]=p;vis_r[i]=tm;
				if(!match_r[i]){aug(i);return 1;}
				else{vis_l[match_r[i]]=tm;q[t++]=match_r[i];}
			}else{
				if(slack[i]>d){slack[i]=d;pre[i]=p;}
			}
		}
	}
	return 0;
}
void km() {
	ll ans;
	memset(match_r, 0, sizeof(match_r));
	memset(match_l, 0, sizeof(match_l));
	memset(ex_r, 0, sizeof(ex_r));
	memset(ex_l, 0, sizeof(ex_l));
	rep1(i, n) rep1(j, n) ex_l[i] = max(ex_l[i], w[i][j]);
	rep1(i, n) {
		memset(slack, INF, sizeof(slack));
		tm++;
		h=t=0;
		q[t++]=i;
		vis_l[i]=tm;
		while (1) {
			int d = INF,ok=0;
			if (bfs()) break;
			rep1(j, n) d = (vis_r[j]!=tm) ? min(slack[j], d):d;
			rep1(j, n) ex_l[j] = (vis_l[j]==tm)? ex_l[j] - d:ex_l[j];
			rep1(j, n) if (vis_r[j]==tm) ex_r[j] += d; else slack[j] -= d;
			rep1(j, n) if (vis_r[j]!=tm&&!slack[j]){
				if(!match_r[j]) {aug(j);ok=1;break;}
				vis_r[j]=vis_l[match_r[j]]=tm;q[t++]=match_r[j];
			}
			if(ok) break;
		}
	}
	ans = 0;
	rep1(i, n) {
		ans += ex_l[i];
	}
	rep1(i, n) {
		ans += ex_r[i];
	}
	cout << ans << endl;
	rep1(i, nl) if (!match_l[i] || !rw[i][match_l[i]]) printf("0 "); else printf("%d ", match_l[i]);
	putchar('\n');
}
int main() {
	freopen("in.txt","r",stdin);
	BUF[fread(BUF, 1, 200000000, stdin)]=0;
	buf = BUF;
	nl = read(); nr = read(); m = read();
	int u, v, c;
	n = max(nl, nr);
	rep1(i, m) {
		u = read(); v = read(); c = read();
		w[u][v] = c, rw[u][v] = 1;
	}
	km();
	return 0;
}


