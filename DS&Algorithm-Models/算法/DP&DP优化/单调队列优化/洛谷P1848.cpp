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
#define mp make_pair
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
#include<functional>
#define print_rumtime printf("Running time:%.3lfs\n",double(clock())/1000.0);
#define TO(j) printf(#j": %d\n",j);
//#define OJ
using namespace std;
const int MAXINT = 100010;
const int MAXNODE = 100010;
const int MAXEDGE = 2 * MAXNODE;
char BUF, *buf;
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
//------------------- Head Files ----------------------//
pair<int, int> q[MAXINT];
struct pq {
	priority_queue<ll,vector<ll>,greater<ll> > q, d;
	void del(ll p) {
		d.push(p);
	}
	void push(ll p) {
		q.push(p);
	}
	ll top() {
		while (!d.empty() && d.top() == q.top()) q.pop(), d.pop();
		return q.top();
	}
	void pop() {
		while (!d.empty() && d.top() == q.top()) q.pop(), d.pop();
		q.pop();
	}
}ans;
ll f[MAXINT], l,n;
int w[MAXINT], H[MAXINT];
ll sum[MAXINT];
void get_input();
void work();
int main() {
	get_input();
	work();
	return 0;
}
void work() {
	pair<int, int> *h, *t;
	h = t = q;
	*t++ = mp(0, INF);//哨兵元素！
	rep1(i, n) {
		int p = i;
		while ((t - 1)->second<H[i]) {
			ans.del((t - 1)->second + f[(t - 1)->first - 1]);
			p = (t - 1)->first;
			t--;
		}
		*t++ = mp(p, H[i]);
		ans.push(f[p - 1] + H[i]);
		h++;
		while ( (h + 1<t) && sum[i] - sum[(h + 1)->first - 1]>l) ans.del(h->second + f[h->first - 1]), h++; //delete the whole segment
		ans.del(h->second + f[h->first - 1]);
		for (; sum[i] - sum[h->first-1]>l; h->first++);//delete some element
		if ((h+1<t)&&h->first == (h + 1)->first) h++;
		else ans.push(h->second + f[h->first - 1]);
		h--;
		*h = mp(0, INF);
		f[i] = ans.top();
	}
	printf("%lld\n", f[n]);
}
void get_input() {
	n = read(); l = read();
	rep1(i, n) H[i] = read(), w[i] = read(), sum[i] = sum[i - 1] + w[i];
}

/*
终于过了这个破题
第一次WA因为没判边界条件
第二次WA因为答案爆了int
第三次T了？没关系，进大牛开O2稳过
题解：f[i] 分完i这个数然后pia叽断开的最小高度和
f[i] = min{f[j]+max{h[j+1]..h[i]}} (sum[i]-sum[j]<=L)
我们发现对于一个固定的i，max{h[j+1]..h[i]}随j增大单调不增，f[j]随j增大单调不减
而且对于某一些区间，它们中的 max{h[j+1]..h[i]}是一样的，那么这段区间中的最优决策一定是把这一段区间要么全分到后面，要么全分到前面（暂时不考虑长度太长的情况）
那我们可以对所有的区间维护一下以它们的左边界-1位决策点的答案，最终的最优解一定在这些答案之中
然后考虑后面新增了一个数h[i]，如果h[i]>h[j-1]，那么j-1所在的那一段区间就没用了（它的最大h被迫上升了），把这一段区间和i这个位置合并，重复向前找区间，直到最大值比h[i]大位置，这是一个典型的单调队列从队尾踢元素的操作
然后考虑从队首踢元素，显然如果一个区间太靠左了，那么这个区间可能会因为sum[i]-sum[j]太大而无法取到
然后按照这个思路从队首删除元素就好了，有的时候是把一整个区间都删掉，有的时候是右移一个区间的左端点，注释应该写得挺清楚了
然后我们怎么维护答案呢？网上有的题解说用一颗平衡树实现，其实没那么烦，因为我们只要支持插入，删除，取最小值，维护一个双堆就行了
然而pq真是慢啊，要是不开O2会T两个点，开了O2是洛谷第2（毕竟堆比平衡树常数小多了），第1是个骗了数据的baka
*/