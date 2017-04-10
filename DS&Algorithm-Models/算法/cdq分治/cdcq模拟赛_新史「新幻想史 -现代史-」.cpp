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
const int MAXINT = 50010;
ll ans[MAXINT];
int n, m, cnt = 0, cnt_q = 0;
struct node {
	int lb, rb;
	ll sum, tag;
	node *c[2];
	node(int _lb, int _rb) :lb(_lb), rb(_rb),tag(0),sum(0) {}
	node() :tag(0), sum(0) {
	}
	int check(int l, int r) {
		if (l <= lb&&r >= rb) return 1;
		if (l >= rb || r <= lb) return 0;
		return -1;
	}
	void add_tag(ll v) {
		sum += v*(rb - lb);
		tag += v;
	}
	void pushdown() {
		c[0]->add_tag(tag);
		c[1]->add_tag(tag);
		tag = 0;
	}
	void pushup() {
		sum = c[0]->sum + c[1]->sum;
	}
};
struct seg_tree {
	node mp[MAXINT * 4];
	int cnt;
	node *rt;
	seg_tree() {
		cnt = 0;
	}
	node* new_node(int l, int r) {
		mp[cnt] = node(l, r);
		return &mp[cnt++];
	}
	void make_tree(int l, int r) {
		rt = new_node(l, r);
		_make_tree(rt, l, r);
	}
	void _make_tree(node *p, int l, int r) {
		if (r - l == 1) {
			p->sum = 0;
			return;
		}
		p->c[0] = new_node(l, (l + r) / 2);
		p->c[1] = new_node((l + r) / 2, r);
		_make_tree(p->c[0], l, (l + r) / 2);
		_make_tree(p->c[1], (l + r) / 2, r);
		p->pushup();
	}
	ll seg_query(int l, int r) {
		return _seg_query(rt, l, r);
	}
	ll _seg_query(node *p, int l, int r) {
		int tp = p->check(l, r);
		if (tp == 1) return p->sum;
		if (tp == 0) return 0;
		p->pushdown();
		return _seg_query(p->c[0], l, r) + _seg_query(p->c[1], l, r);
	}
	void seg_add(int l, int r, int v) {
		_seg_add(rt, l, r, v);
	}
	void _seg_add(node *p, int l, int r, int v) {
		int tp = p->check(l, r);
		if (tp == 1) { p->add_tag(v); return; }
		if (tp == 0) return;
		_seg_add(p->c[0], l, r, v); _seg_add(p->c[1], l, r, v);
		p->pushdown();
		p->pushup();
	}
}seg;
struct op {
	int tp, t, no, q_no, l, r, v;
	op(int _t, int _no, int _l, int _r, int _v) {
		tp = 1;
		t = _t;
		no = _no;
		l = _l;
		r = _r;
		v = _v;
	}
	op() {}
	op(int _t, int _no, int _l, int _r) {
		tp = 0;
		t = _t;
		q_no = cnt_q;
		no = _no;
		l = _l;
		r = _r;
	}
}ops[200010];
bool cmpt(const op &a, const op &b) {
	return a.t == b.t ? a.tp > b.tp:a.t < b.t;
}
bool cmpno(const op &a, const op &b) {
	return a.no == b.no ? a.tp > b.tp : a.no < b.no;
}
void cdq(int l, int r) {
	if (r - l == 1) {
		return;
	}
	cdq(l, (l + r) / 2);
	cdq((l + r) / 2, r);
	sort(ops + l, ops + (l + r) / 2, cmpt);
	sort(ops + (l + r) / 2, ops + r, cmpt);
	int i = l;
	int j = (l + r) / 2;
	for (; j < r; j++) {
		if (ops[j].tp == 1) continue;
		for (; i < (l + r) / 2 && ops[i].t <= ops[j].t; i++) {
			if (ops[i].tp == 0) continue;
			seg.seg_add(ops[i].l, ops[i].r, ops[i].v);
		}
		ans[ops[j].q_no] += seg.seg_query(ops[j].l, ops[j].r);
	}
	i = l;
	j = (l + r) / 2;
	for (; j < r; j++) {
		if (ops[j].tp == 1) continue;
		for (; i < (l + r) / 2 && ops[i].t <= ops[j].t; i++) {
			if (ops[i].tp == 0) continue;
			seg.seg_add(ops[i].l, ops[i].r, -ops[i].v);
		}
	}
	sort(ops + l, ops + r, cmpt);
}
void get_input() {
	n = read(); m = read();
	seg.make_tree(0, n);
	char tp;
	int t, l, r, v, l1, r1, v1;
	rep0(i, n) {
		t = read();
		ops[cnt++] = op(-1, -1, i, i + 1, t);
	}
	rep0(i, m) {
		tp = get_ch();
		if (tp == 'Q') {
			l = read(); r = read(); t = read();
			ops[cnt++] = op(t, i, l - 1, r);
			cnt_q++;
		}
		else {
			l = read(); r = read(); v = read(); l1 = read(); r1 = read(); v1 = read(); t = read();
			ops[cnt++] = op(t, i, l - 1, r, -v);
			ops[cnt++] = op(t, i, l1 - 1, r1, v1);
		}
	}
}
void work() {
	cdq(0, cnt);
	rep0(i, cnt_q) {
		printf("%lld\n", ans[i]);
	}
}
int main() {
	freopen("cdcq_a.in", "r", stdin);
	freopen("cdcq_a.out", "w", stdout);
	get_input();
	work();
	return 0;
}
/*
【题目描述】


慧音也想要退治妖怪！
在某次异变中，慧音要退治排成一列的n个妖怪，作为"吞食历史的半兽"，慧音会使用符卡"新史「新幻想史 -现代史-」"修改过去的历史来让一段区间内的妖怪力量减少，同时因为历史被改变了，所以会有另一段区间的妖怪力量增强（一个妖怪的力量改变后，这个效果会一直持续到后面的时刻）。为了让修改历史的效果最稳定，慧音还想知道在过去的某个时刻一段区间中所有妖怪的妖力和是多少，每个时刻慧音只会发出一条指令。
战斗持续了m个时刻，由于慧音还要集中精力发射头槌弹幕，所以她请你来帮忙解决她的询问。
（没有进行任何操作的时刻为0时刻
关于时间线的说明：
如果有以下操作：询问1->修改->询问2，询问的目标时刻相等，修改的目标时刻小于等于询问的目标时刻，则询问1不会受到修改的影响，而询问2会
如果有以下操作：询问1->修改->询问2，询问的目标时刻相等，修改的目标时刻大于询问的目标时刻，则两个询问都不会受到修改的影响
特别提醒：
比赛进行中请尽量不要进行有关时间线或世界线的伦理思考

【输入格式】


第一行两个整数n,m，意义如上
接下来一行n个整数，第i个整数ai表示第i个妖怪的妖力
接下来m行，第i行表示第i个时刻的指令，首先一个字符c，如果c为'Q'，接下来三个用空格隔开的整数x,y,z，表示询问第z个时刻区间[x,y]中所有妖怪的妖力和，如果c为'M'，接下来七个整数x,y,z,l,r,v,t，表示在第t个时刻，区间[x,y]中所有妖怪的妖力减少了z，区间[l,r]中所有妖怪妖力增加了v
输入数据中一行中的所有整数和字符用空格隔开

【输出格式】


对于每个M操作，输出一行一个值表示查询的结果

【样例输入1】


5 4
1 2 3 4 5
Q 1 3 0
M 1 2 1 2 3 2 1
Q 1 3 0
Q 1 3 1

【样例输出1】


6
6
8

【样例输入2】


12 12
20755 32646 15599 16925 29509 29411 31544 19290 25477 30085 4973 21417
M 8 11 32373 4 7 2615 1
Q 7 7 0
M 8 10 32317 12 12 1710 3
M 4 5 28846 2 7 6548 4
Q 9 11 4
Q 12 12 4
Q 5 11 2
M 6 10 32331 6 7 1272 8
M 2 11 17117 4 9 19679 9
M 4 5 21667 4 5 13394 5
M 8 10 11508 9 11 30783 11
Q 8 9 6

【样例输出2】


31544
-101218
23127
48642
-84613

【样例解释】


第1个时刻，慧音询问第0个时刻[1,3]这个区间的妖力和，显然答案为6
第2个时刻，慧音使第1个时刻[1,2]的妖力减少1，[2,3]的妖力增加2
现在第1个时刻和第2个时刻的妖力序列都是0 3 5 4 5，而第0个时刻的妖力序列依旧是1 2 3 4 5
之后的两次询问就是在第0个时刻[1,3]的妖力和和第1个时刻[1,3]的妖力和，显然答案分别为6和8

【数据范围】



数据标号	n,m	ai,v,z	ex
1	<=50	<=10^5	
2	<=500
3
4
5
6
7	<=5000	只有Q操作
8
9	
10
11
12
13
14
15	<=50000	只有Q操作
16
17	
18
19
20
对于所有数据，保证查询和修改的目标时刻在进行操作的时刻或进行操作的时刻之前；数据有梯度
*/

