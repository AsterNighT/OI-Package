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
//#define max(a,b) (a>b?a:b)
//#define min(a,b) (a<b?a:b)
//#define OJ
using namespace std;
const int MAXINT = 1110;
const int MAXNODE = 1110;
const int MAXEDGE = 1110;
int n, T;
char s[MAXINT];
struct node {
	node *fail;
	node *c[4];
	int bad;
	int nd[MAXINT]; //for a string of length i, least change required to reach this state
};
int toint(char c) {
	switch (c) {
	case 'A': return 0;
	case 'C': return 1;
	case 'G': return 2;
	case 'T': return 3;
	}
	return 0;
}
struct ac_automaton {
	node mp[MAXNODE];
	node *root, *pre;
	node *q[MAXNODE];
	int cnt;
	ac_automaton() {
		memset(mp, 0, sizeof(mp));
		memset(q, 0, sizeof(q));
		cnt = 0;
		root = new_node();
		pre = root;
	}
	void clear() {
		memset(mp, 0, sizeof(mp));
		memset(q, 0, sizeof(q));
		cnt = 0;
		root = new_node();
		pre = root;
	}
	node *new_node() {
		memset(mp[cnt].nd, 0x3f3f, sizeof(mp[cnt].nd));
		return &mp[cnt++];
	}
	void add(int w) {
		if (!pre->c[w]) pre->c[w] = new_node();
		pre = pre->c[w];
	}
	void danger() {
		pre->bad = 1;
	}
	void init() {
		pre = root;
	}
	void get_fail() {
		int h = 0, t = 0;
		node *p, *tmp;
		q[t++] = root;
		root->fail = NULL;
		while (h != t) {
			p = q[h++];
			rep0(i, 4) {
				if (p->c[i]) {
					if (p == root) p->c[i]->fail = root;
					else {
						tmp = p->fail;
						while (tmp) {
							if (tmp->c[i]) {
								p->c[i]->bad |= tmp->c[i]->bad;
								p->c[i]->fail = tmp->c[i];
								break;
							}
							tmp = tmp->fail;
						}
						if (!tmp) p->c[i]->fail = root;
					}
					q[t++] = p->c[i];
				}
				else {
					p->c[i] = p->fail&&p->fail->c[i] ? p->fail->c[i] : root;
				}
			}
		}
	}
	void solve(char *s) {
		int l = strlen(s);
		root->nd[0] = 0;
		rep0(i, l) {
			rep0(j, cnt) {
				if (mp[j].nd[i] != INF) {
					rep0(k, 4) {
						node *p = mp[j].c[k];
						if (!p || p->bad) continue;
						p->nd[i + 1] = min(p->nd[i + 1], mp[j].nd[i] + ((toint(s[i]) == k) ? 0 : 1));
					}
				}
			}
		}
		int ans = INF;
		rep0(i, cnt) {
			if (!mp[i].bad) {
				ans = min(ans, mp[i].nd[l]);
			}
		}
		printf("Case %d: %d\n", T, ans == INF ? -1 : ans);
	}
} acm;
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

void get_input();
void work();
int main() {
	freopen("in.txt", "r", stdin);
	freopen("out.wa", "w", stdout);
	while (++T) {
		scanf("%d", &n);
		if (!n) break;
		acm.clear();
		get_input();
		work();
	}
	return 0;
}
void work() {
	acm.solve(s);
}
void get_input() {
	rep0(i, n) {
		scanf("%s", s);
		int l = strlen(s);
		rep0(j, l) acm.add(toint(s[j]));
		acm.danger();
		acm.init();
	}
	acm.get_fail();
	scanf("%s", s);
}

