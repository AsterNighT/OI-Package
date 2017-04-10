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
#define INF 1e15
#define MOD 1000000007
#define rep0(j,n) for(int j=0;j<n;++j)
#define rep1(j,n) for(int j=1;j<=n;++j)
#define pb push_back
#define set0(n) memset(n,0,sizeof(n))
#define ll long long
#define OJ UOJ
using namespace std;
int read() {
	char c = getchar(); int f = 1, x = 0;
	while (!isdigit(c)) { if (c == '-') f = -1; c = getchar(); }
	while (isdigit(c)) { x = x * 10 + c - '0'; c = getchar(); }
	return f*x;
}
char get_ch() {
	char c = getchar();
	while (!isalpha(c)) c = getchar();
	return c;
}
const int MAXINT = 3010;
int n, m,sum[MAXINT],ans;
int dp[2][MAXINT],h,t,p=0, q[MAXINT];

double slope(int a, int b) {
	return double(sum[a]*sum[a]+dp[p^1][a] - sum[b] * sum[b] - dp[p ^ 1][b]) / double(sum[a] - sum[b]);
}
int main() {
	n = read(); m = read();
	rep1(i, n) sum[i] = read();
	for (int i = 2; i <= n; i++) sum[i] += sum[i - 1];
	ans = -sum[n] * sum[n];
	rep1(i, n) dp[p][i] = sum[i] * sum[i];
	p ^= 1;
	for (int i = 2; i <= m; i++) {
		h = t = 0;
		q[t++] = 0;
		for (int j = 1; j <= n; j++) {
			while (t - h > 1 && 2*sum[j] > slope(q[h], q[h + 1])) h++;
			dp[p][j] = dp[p ^ 1][q[h]] + (sum[j] - sum[q[h]])*(sum[j] - sum[q[h]]);
			while (t - h > 1 && slope(q[t - 1], q[t - 2]) > slope(q[t - 1], j)) t--;
			q[t++] = j;
		}
		p ^= 1;
	}
	ans += dp[p ^ 1][n] * m;
	printf("%d\n", ans);
}

