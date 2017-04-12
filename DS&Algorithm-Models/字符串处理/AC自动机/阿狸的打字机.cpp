
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
#define lowbit(x) (x&-x)
//#define OJ
using namespace std;

const int MAXINT = 100010;
const int MAXNODE = 100010;
const int MAXEDGE = 100010;
int cnt_dfn, ans[MAXINT], m;
char op[MAXINT];
struct query {
	int x, y, id;
	query() {}
	query(int _x, int _y, int _id) :x(_x), y(_y), id(_id) {}
	bool operator < (const query &b) {
		return y < b.y;
	}
} qr[MAXINT];
struct fwt {
	int sum[MAXNODE], ub;
	void add(int p, int v) {
		while (p <= ub) {
			sum[p] += v;
			p += lowbit(p);
		}
	}
	int query(int p) {
		int ans = 0;
		while (p) {
			ans += sum[p];
			p -= lowbit(p);
		}
		return ans;
	}
} fw;
struct node {
	node *c[26], *fail, *pre;
	int dfn, max_dfn;
	vector<node*> eg;
}*ed[MAXINT];
struct ac_automaton {
	node mp[MAXNODE];
	node *q[MAXNODE];
	node *present, *root;
	int cnt;
	ac_automaton() {
		cnt = 0;
		present = root = new_node();
	}
	node *new_node() {
		return &mp[cnt++];
	}
	void back() {
		present = present->pre;
	}
	void add(char c) {
		int w = c - 'a';
		if (!present->c[w]) {
			present->c[w] = new_node();
			present->c[w]->pre = present;
		}
		present = present->c[w];
		//present->cnt++;
	}
	void get_fail() {
		int h = 0, t = 0;
		node *p, *tp;
		root->fail = NULL;
		q[t++] = root;
		while (h != t) {
			p = q[h++];
			rep0(i, 26) {
				if (p->c[i]) {
					if (p == root) p->c[i]->fail = root;
					else {
						tp = p->fail;
						while (tp) {
							if (tp->c[i]) {
								p->c[i]->fail = tp->c[i];
								break;
							}
							tp = tp->fail;
						}
						if (!tp) p->c[i]->fail = root;
					}
					q[t++] = p->c[i];
				}
			}
		}
	}
	void link_edge() {
		rep0(i, cnt) {
			if (mp[i].fail) {
				mp[i].fail->eg.push_back(&mp[i]);
			}
		}
	}
	void dfs(node* p) {
		p->dfn = ++cnt_dfn;
		for (vector<node*>::iterator i = p->eg.begin(); i != p->eg.end(); ++i) {
			dfs(*i);
		}
		p->max_dfn = cnt_dfn;
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
	get_input();
	work();
	return 0;
}
void work() {
	int s_cnt = 0, j = 0;
	sort(qr, qr + m);
	fw.ub = MAXINT;
	int l = strlen(op);
	rep0(i, l) {
		if (op[i] == 'B') {
			acm.back();
			continue;
		}
		if (op[i] == 'P') {
			s_cnt++;
			ed[s_cnt] = acm.present;
			continue;
		}
		acm.add(op[i]);
	}
	s_cnt = 0;
	acm.get_fail();
	acm.link_edge();
	acm.dfs(acm.root);
	acm.present = acm.root;
	rep0(i, l) {
		if (op[i] == 'B') {
			fw.add(acm.present->dfn, -1);
			acm.back();
			continue;
		}
		if (op[i] == 'P') {
			s_cnt++;
			for (; s_cnt == qr[j].y; j++) {
				ans[qr[j].id] = fw.query(ed[qr[j].x]->max_dfn) - fw.query(ed[qr[j].x]->dfn - 1);
			}
			continue;
		}
		acm.add(op[i]);
		fw.add(acm.present->dfn, 1);
	}
	rep0(i, m) printf("%d\n", ans[i]);
}
void get_input() {
	scanf("%s", op);
	m = read();
	rep0(i, m) {
		qr[i].x = read();
		qr[i].y = read();
		qr[i].id = i;
	}
}