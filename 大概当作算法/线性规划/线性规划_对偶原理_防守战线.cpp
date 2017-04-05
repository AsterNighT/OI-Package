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
#define eps 1e-10
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
const int MAXINT = 25;
int n, m, t;
struct Linear_Programming {
	int n,m;
	double a[1010][10010]; 
	void pivot(int out, int in) {
		double tmp = a[out][in];
		a[out][in] = 1;
		for (int i = 0; i <= n; i++) a[out][i] /= tmp;
		for (int i = 0; i <= m; i++) if (i != out && fabs(a[i][in]) > eps) {
			tmp = a[i][in]; a[i][in] = 0;
			for (int j = 0; j <= n; j++) a[i][j] -= tmp*a[out][j];
		}
	}
	bool init_solution() {
		while (1) {
			int in = 0, out = 0;
			for (int i = 1; i <= m; i++) if (a[i][0] < -eps && (!out || (rand() & 1)))out = i;
			if (!out) break; 
			for (int i = 1; i <= n; i++) if (a[out][i] < -eps && (!in || (rand() & 1))) in = i;
			if (!in) {
				printf("Infeasible\n");
				return false;
			}
			pivot(out, in);
		}
		return true;
	}
	bool simplex() {
		while (1) {
			int in = 0, out = 0;
			double mn = INF;
			for (int i = 1; i <= n; i++) if (a[0][i] > eps) { in = i; break; }
			if (!in) break;
			for (int i = 1; i <= m; i++) 
				if (a[i][in] > eps && a[i][0] / a[i][in] < mn) {
					mn = a[i][0] / a[i][in]; out = i;
				}
			if (!out) {
				printf("Unbounded\n");
				return false;
			}
			pivot(out, in);
		}
		return true;
	}
	void print(){
		rep0(i,n+1){
			rep0(j,m+1){
				printf("%lf ",a[i][j]);
			}
			putchar('\n');
		}
	}
	void work() {
		if (init_solution() && simplex()) {
			printf("%d\n", int(-a[0][0]+0.5));
		}
	}
}lp;
int main() {
	srand(559320414);
	n = read(); m = read(); 
	int l,r;
	rep1(i, n) lp.a[i][0] = read();
	rep1(i, m) {
		l=read();r=read();
		for(int j=l;j<=r;j++) lp.a[j][i]=1;
		lp.a[0][i] = read();
	}
	lp.n=m;lp.m=n;
	//lp.print();
	lp.work();
	return 0;
}

