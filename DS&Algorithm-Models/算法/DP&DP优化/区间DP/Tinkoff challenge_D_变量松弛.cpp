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
//#define OJ
using namespace std;
const int MAXINT = 100010;
const int MAXNODE = 100;
const int MAXEDGE = 2 * 2000;
char BUF, *buf;
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
//------------------- Head Files ----------------------//
int dis[MAXNODE][MAXNODE], n, K, m, cnt;
int dp[MAXNODE][MAXNODE][MAXNODE];
//now Oleg is at pos i,and have already given out k-1 presents in bank office 1..i-1, 1 in office i, minimum difficulty
//and Oleg can go no further than j
void get_input();
void work();
int main() {
	get_input();
	work();
	return 0;
}
void work() {
	memset(dp, INF, sizeof(dp));
	int ans = INF;
	rep1(i, n)rep1(j, n) dp[i][j][1] = 0; //Oleg can start anywhere,and the first step should always be gifting a present
	for (int k = 2; k <= K; k++) { //k in dp
		for (int i = 1; i <= n ; i++) { //i in dp
			for (int j = i + k - 1; j <= n; j++) { //j in dp
				for (int prv = i + 1; prv <= j; prv++) {  //go right
					dp[i][j][k] = min(dp[i][j][k], min(dp[prv][j][k - 1], dp[prv][i + 1][k - 1]) + dis[i][prv]);
				}
			}
			for (int j = i - k + 1; j > 0 ; j--) { //j in dp
				for (int prv = i - 1; prv >= j; prv--) { //go left
					dp[i][j][k] = min(dp[i][j][k], min(dp[prv][j][k - 1], dp[prv][i - 1][k - 1]) + dis[i][prv]);
				}
			}
		}
	}
	rep1(i, n) rep1(j, n) ans = min(ans, dp[i][j][K]);
	printf("%d\n", (ans == INF) ? -1 : ans);
}
void get_input() {
	memset(dis, INF, sizeof(dis));
	n = read(); K = read();
	m = read();
	rep0(i, m) {
		int u = read(), v = read(), c = read();
		dis[u][v] = min(dis[u][v], c);
	}
}

/*
http://codeforces.com/contest/793/problem/D
区间dp。
考虑最naive的dp[i][lb][rb][k]表示在现在位置在i，能走的范围是[lb,rb]，要在范围内选k个站送礼物的最小难度
那么可以枚举下一次走到哪里，显然一步只经过一条有向边，因为其他方案都可以用这个方案替代，并且答案不会更劣
如果下一步往右走，走到to，那么下一次的状态是dp[to][i+1][rb][k-1]，同理向左走是dp[to][lb][i-1][k-1]，这样需要枚举i,lb,rb,to,k，复杂度是kn^4+m
然后可以发现，在其中有一维是没用的——向右走不需要左边界，向左走不需要右边界
则dp[i][b][k]表示走到i，某个方向的边界是b，送了k个礼物
如果b>i，则是向右走，转移到dp[to][i+1][k-1]与dp[to][b][k-1]，向左走同理
这样需要枚举i,b,to,k复杂度是kn^3+m可过
*/