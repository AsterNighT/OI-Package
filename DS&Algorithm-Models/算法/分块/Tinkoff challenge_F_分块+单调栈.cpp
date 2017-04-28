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
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
#define print_rumtime printf("Running time:%.3lfs\n",double(clock())/1000.0);
#define TO(j) printf(#j": %d\n",j);
//#define OJ
using namespace std;
const int MAXINT = 100010;
const int MAXNODE = 100010;
const int MAXEDGE = 2 * MAXNODE;
const int MAX_BLOCK = 320;
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

vector<int> to[MAXINT];
int prv[MAXINT], f[MAX_BLOCK][MAXINT], ans[MAX_BLOCK][MAXINT], n, m, q, sz_b = 317, cnt_b, p[MAXINT];
pair<int, int> stk[MAXINT];
pair<int, int> *tp;
void get_input();
void work();
void pre_calc();
int main() {
	get_input();
	pre_calc();
	work();
	return 0;
}
void work() {
	rep0(i, q) {
		int lm, pl;
		int l = read() - 1, r = read();
		if (r - l > sz_b) {
			int b_r = r / sz_b;
			lm = ans[b_r][l];
			pl = b_r * sz_b;
		}else lm = pl = l;
		for (int j = pl; j < r; ++j) 
			if (prv[j] <= lm && prv[j] >= l) 
				lm = max(lm, j);
		printf("%d\n", lm + 1);
	}
}
void get_input() {
	memset(prv, INF, sizeof(prv));
	n = read(); m = read();
	rep0(i, m) { //for convenience, label begin with 0
		int u = read() - 1, v = read() - 1;
		prv[v] = u;
		to[u].pb(v);
	}
	q = read();
}
void pre_calc() {
	rep0(i, n) sort(to[i].begin(), to[i].end());
	cnt_b = n / sz_b;
	rep1(i, cnt_b) {
		rep0(j, i * sz_b) {
			for (; p[j] < to[j].size() && to[j][p[j]] < i * sz_b; p[j]++);
			if (p[j]) f[i][j] = to[j][p[j] - 1]; else f[i][j] = j;
		}
	}
	rep1(i, cnt_b) {
		tp = stk;
		for (int j = i * sz_b - 1; j >= 0; j--) {
			ans[i][j] = f[i][j];
			if (tp == stk) ans[i][j] = j;
			else while (tp != stk && f[i][j] >= (tp - 1)->first) 
				ans[i][j] = max(ans[i][j], (tp-1)->second),tp--;
			*tp++ = mp(j, ans[i][j]);
		}
	}
}
/*

分块好题！
首先我们发现，因为以每个高度为终点的绳子只有一个，我们可以对每个点高度记录一个prv，表示以这个高度为终点的绳子起点在哪，这样我们就可以O（区间长度）的处理询问，具体做法是从区间开始到结束扫一遍，维护当前能从左端点走到的最右面的点，每当找到一个绳子，起点>=左边界，并且<=当前能走到的最右边的点，那么就把能走到的最右边的点更新为这个点。
为什么这样是对的呢？因为这样按照终点从左到右扫描，如果一根绳子当前不能用，那么以后也永远用不到——以后能用的绳子都比它更优秀
然后我们就可以有一个O(qn)的做法，但这样不够优秀，我们考虑优化。
容易看出按照刚才那种做法，把一个区间往后延长一段是可做的，那我们不妨考虑这样一种做法。我们把整个树干分成 $ \sqrt{n} $ 块，预处理出每个起点到每个块终点的答案（能走到的最右边的点），然后我们就可以 $ \sqrt{n} $ 的回答询问了
现在问题在于，怎么求这个东西。
吐槽一下毛子写的英文题解，**不通，晦涩难懂
假设一个块的大小是sz_b
假设这个东西叫做ans[i][j]，表示[j,i*sz_b-1]的答案（我是从0开始标号的）
我们需要一个东西来求它，假设叫做f[i][j]，表示所有以j为起点，终点<i*sz_b，的绳子中，终点最大的，可能有点绕，理解一下，原文更坑爹
这个f我们可以直接two pointers求出来，因为对于每一个j，f[i][j] (j固定，i是变量) 都是单调的，对每个位置维护一个指针就好了
然后我们有了f，要求ans了，我们从右往左做，显然ans[i][j] = max(ans[i][k]) j<=k<=f[i][j]，这个式子还是比较好理解的吧
然后看上去就可以用线段树维护了，但这样还是会T，我们还需要进一步优化
考虑一个正在计算ans[i][j]的位置j，我们不妨假设从右往左扫描max，如果ans[i][j]被ans[i][p]和ans[i][q]（p<q）都更新了一次，那说明了什么？
说明ans[i][q]<ans[i][p]
那么p的位置又比q靠前，能延伸到的位置还比q靠后，显然q这个位置没用啊
然后如果用更新了j，ans[i][j]>=ans[i][p]，i又比p靠前，p也没用了
所以我们对每一趟求ans[*][j]维护一个单调栈，栈中元素是一个二元组（i,j），表示i这个位置的ans是j
扫描到一个元素p时，把所有栈中p能够到(p+f[*][p]>=q)的元素吐出来并更新ans[*][p]，然后把(p,ans[*][p])丢进栈里
这样每一趟求ans也可以线性了
然后就搞定啦！总复杂度 $ O((n+q)\sqrt{n}) $
*/