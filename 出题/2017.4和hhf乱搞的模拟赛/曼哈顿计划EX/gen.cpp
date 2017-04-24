#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>
#include <cmath>
#include <sstream>
#include <map>
#include <stack>
#include <set>
#include <vector>
#include <queue>
#include <time.h>
#include <windows.h>
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
const int MAXINT = 100010;
const int MAXNODE = 100010;
const int MAXEDGE = 2 * MAXNODE;
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


int main() {
	for(int i=1; i<=3; i++) {
		stringstream cvt;
		cvt<<i;
		string t;
		cvt>>t;
		string s = "flow"+t+".in";
		freopen(s.c_str(), "w", stdout);
		srand(time(0));
		int n = 20,m=100,q=30;
		printf("%d %d %d\n",n,m,q);
		rep0(i,n) printf("%d ",rand()%3000+1);
		putchar('\n');
		for (int i = 2; i <= n; i++) printf("%d %d\n", rand() % (i - 1) + 1, i);
		for(int i=n; i<=m; i++) printf("%d %d\n",rand()%n+1,rand()%n+1);
		rep0(i, q) printf("%d\n", (rand()+(rand()<<15))%60000);
		Sleep(2000);
	}
	return 0;
}


