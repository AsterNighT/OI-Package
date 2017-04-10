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
#define eps 10e-7
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define rep0(j,n) for(int j=0;j<n;++j)
#define rep1(j,n) for(int j=1;j<=n;++j)
#define pb push_back
#define set0(n) memset(n,0,sizeof(n))
#define ll long long
#define ull unsigned long long
#define lowbit(x) (x&-x)
using namespace std;
int read() {
	char c = getchar(); int f = 1, x = 0;
	while (!isdigit(c)) { if (c == '-') f = -1; c = getchar(); }
	while (isdigit(c)) { x = x * 10 + c - '0'; c = getchar(); }
	return f*x;
}
const int MAXINT = 100010;
const ull n16_1 = (1 << 16) - 1;
const ull n16_2 = n16_1 << 16;
const ull n16_3 = n16_2 << 16;
const ull n16_4 = n16_3 << 16;
const ull n64 = n16_1 | n16_2 | n16_3 | n16_4;

int pop_cnt[1 << 16];
void pre_calc() {
	for (int i = 1; i < (1 << 16); i++) pop_cnt[i] = pop_cnt[i - lowbit(i)] + 1;
}
struct bitset {
	ull s[MAXINT >> 6];
	int l;
	int get(int p) {
		return (s[p >> 6] & (1ull << (p & 63))) == 0 ? 0 : 1;
	}
	void set(int p) {
		s[p >> 6] |= (1ull << (p & 63));
	}
	void del(int p) {
		s[p >> 6] &= ~(1ull << (p & 63));
	}
	int count(ull p) {
		return pop_cnt[(p&n16_1)] + pop_cnt[((p >> 16)&n16_1)] + pop_cnt[((p >> 32)&n16_1)] + pop_cnt[((p >> 48)&n16_1)];
	}
	int count(int l, int r) {
		int ans = 0;
		if ((l >> 6) == (r >> 6)) return count(s[l >> 6] >> (l & 63) << (l & 63) << (63 - (r & 63)) >> (63 - (r & 63)));
		for (int i = (l >> 6) + 1; i < (r >> 6); i++) ans += count(s[i]);
		ans += count(s[(l >> 6)] >> (l & 63));
		ans += count(s[r & 63] << (63 - (r & 63)) >> (63 - (r & 63)));
		return ans;
	}
	void print() {
		rep0(i, l) printf("%d ", get(i));
		putchar('\n');
	}
}bs;
int seg_and(bitset &a, bitset &b, int bg_a, int bg_b, int l) {
	if (bg_a > bg_b) {
		swap(a, b);
		swap(bg_a, bg_b);
	}
	int py = bg_b - bg_a;
}
int op;
int main() {
	bs.l = 10;
	pre_calc();
	while (cin >> op) {
		if (op >= 0)bs.set(op); else bs.del(-op);
		bs.print();
		printf("%d\n", bs.count(0, 9));
	}
	return 0;
}