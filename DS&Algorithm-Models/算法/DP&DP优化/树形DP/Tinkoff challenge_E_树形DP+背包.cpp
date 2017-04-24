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
const int MAXNODE = 5010;
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

int sz[MAXNODE], cnt, n, a[4], ct[MAXNODE][4], item[MAXNODE], cnt_item, tot, nd;
int dp[2][MAXNODE * 2], cnt_s[MAXNODE];
struct edge {
	int u, v;
	edge *nxt;
	edge(int _u, int _v, edge* _nxt) : u(_u), v(_v), nxt(_nxt) {}
	edge() {}
} mp[MAXEDGE], *head[MAXNODE];
void add_edge(int u, int v) {
	mp[cnt] = edge(u, v, head[u]);
	head[u] = &mp[cnt++];
	mp[cnt] = edge(v, u, head[v]);
	head[v] = &mp[cnt++];
}
void dfs(int p, int fa) {
	if (!cnt_s[p]) {
		sz[p] = 1;
		rep0(i, 4) if (p == a[i]) ct[p][i] = 1;
	}
	iter(i, p) {
		if (i->v == fa) continue;
		dfs(i->v, p);
		sz[p] += sz[i->v];
		rep0(j, 4) ct[p][j] |= ct[i->v][j];
	}
}
void get_item(int p, int fa, int it) {
	if (!ct[p][0 ^ it] && !ct[p][1 ^ it]) {
		item[cnt_item++] = sz[p];
		return;
	}
	iter(i, p) {
		if (i->v == fa) continue;
		get_item(i->v, p, it);
	}
}
int bp() {
	int p = 0;
	memset(dp, 0, sizeof(dp));
	dp[p][0] = 1;
	dp[p ^ 1][0] = 1;
	rep0(i, cnt_item) {
		rep0(j, n) {
			dp[p ^ 1][j] |= dp[p][j];
			dp[p ^ 1][j + item[i]] |= dp[p][j];
		}
		p ^= 1;
	}
	return dp[p][nd];
}
void get_input();
void work();
int main() {
	get_input();
	work();
	return 0;
}
void work() {
	dfs(1, 0);
	if (sz[1] & 1) {
		printf("NO\n");
		return;
	}
	tot = sz[1] / 2 - 1, nd;
	for (int it = 0; it <= 2; it += 2) {
		cnt_item = 0;
		iter(i, 1) {
			if (ct[i->v][2 ^ it]) {
				nd = tot - sz[i->v];
				continue;
			}
			if (ct[i->v][3 ^ it]) continue;
			if (ct[i->v][0 ^ it] || ct[i->v][1 ^ it]) {
				get_item(i->v, 1, it);
				continue;
			}
			item[cnt_item++] = sz[i->v];
		}
		if (nd < 0 || !bp()) {
			printf("NO\n");
			return;
		}
	}
	printf("YES\n");
}
void get_input() {
	n = read();
	rep0(i, 4) a[i] = read();
	rep1(i, n - 1) {
		int v = read();
		cnt_s[v]++;
		add_edge(v, i + 1);
	}
}
/*
好题，这一套题的质量都很好。
没想出来，只会做一对点的情况，看了题解。
先考虑一对点的情况，显然这个就是个安排DFS序的问题，而且显然如果叶子节点数是奇数那答案一定是NO，否则设叶子节点数量是k，最终a,b之间的叶子节点数量就是k/2-1。然后问题就变成安排一个DFS顺序使得a,b之间有k/2-1个叶子，很显然的想法是把以每个节点为根的子树里叶子节点的数量统计出来（定义为这个节点的size）。然后考虑1号点的两种子树：
1、不包含a或者b
2、包含a或者b
显然对于第一种子树，要么在a,b之间不包含它，要么整个包含它，因为是DFS序，不能把它拆成两部分
对于第二种子树，把子树的子树分成两种，包含a or b与不包含a or b的，不包含a or b其实是和前面的第一种子树等价的，然后这样递归下去直到最后只剩a or b一个节点
然后就得到了一些互不影响的子树，只要从这些子树里选出一些使得它们的size和是k/2-1，就是简单的背包问题。
然后考虑有两对点的情况，显然这四个点被dfs到的顺序应该是a,c,b,d,a,c,b,d.....或者a,d,b,c,a,d,b,c....这样的形式，因为如果cd在ab同一侧，他们之间的叶子数量一定不到k/2-1，事实上这两种情况是等价的，只需考虑a,c,b,d这种情况即可
这样的话，c所在的子树必然要选，d所在的子树必然不能选，重新做一遍刚才的背包，这次的问题是能否选择一些子树（c和d所在的子树不能选），使得它们的size和是k/2-1-size[c所在的子树]
然后再对cd做一遍，顺序是c,a,d,b，即可，事实上，只要这两个背包分别成立，总可以构造出一个合法的顺序，使得两个背包同时成立，具体方法是，把属于ab不属于cd的放在ac之间，两个都属于的放在cb之间，属于cd不属于ab的放在bd之间即可
考虑一下三对点的情况，ab,cd,ef这个就不好搞了，比如说dfs的顺序是a,c,e,b,d,f，事实上无法构造出一个合理的安排方式是的一个子树属于ab，但是不属于cd,fe，所以好像只能做到两对点
*/