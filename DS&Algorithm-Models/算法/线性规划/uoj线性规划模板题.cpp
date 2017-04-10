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
	double a[MAXINT][MAXINT]; //m*n的矩阵，[1,1]到[m,n]是系数矩阵，[0,1]到[0,n]是c，[1,0]到[m,0]是b，[0,0]是目标函数值
	int id[MAXINT * 2];
	double ans[MAXINT];//1~n是非基变量，n+1~n+m是基变量
	void pivot(int out, int in) {
		swap(id[n + out], id[in]);//把非基变量丢进去，基变量丢出来
		double tmp = a[out][in];
		a[out][in] = 1;//把基变量那一列换出来
		for (int i = 0; i <= n; i++) a[out][i] /= tmp;//把需要换进去的变量系数消成1
		for (int i = 0; i <= m; i++) if (i != out && fabs(a[i][in]) > eps) {//处理系数矩阵，消元，事实上把c和目标函数一起处理了
			tmp = a[i][in]; a[i][in] = 0;
			for (int j = 0; j <= n; j++) a[i][j] -= tmp*a[out][j];
		}
	}
	bool init_solution() {
		rep1(i, n) id[i] = i;
		while (1) {
			int in = 0, out = 0;
			for (int i = 1; i <= m; i++) if (a[i][0] < -eps && (!out || (rand() & 1)))out = i; //初始解不合法，随机选一个不合法的基变量换出来
			if (!out) break; //合法
			for (int i = 1; i <= n; i++) if (a[out][i] < -eps && (!in || (rand() & 1))) in = i;//把一个负系数的变量换进去来尝试使初始解合法
			if (!in) {//没有办法使初始解合法了
				printf("Infeasible\n");
				return false;
			}
			pivot(out, in);
		}
		return true;
	}
	bool simplex() {//求解单纯形
		while (1) {
			int in = 0, out = 0;
			double mn = INF;
			for (int i = 1; i <= n; i++) if (a[0][i] > eps) { in = i; break; }//选一个系数大于0的丢进去
			if (!in) break;//没有系数大于0的，已经达到最优解
			for (int i = 1; i <= m; i++) 
				if (a[i][in] > eps && a[i][0] / a[i][in] < mn) {
					mn = a[i][0] / a[i][in]; out = i;
				}
			if (!out) {//没有任何限制，无界解
				printf("Unbounded\n");
				return false;
			}
			pivot(out, in);
		}
		return true;
	}
	void work() {
		if (init_solution() && simplex()) {
			printf("%.8lf\n", -a[0][0]);//注意一下算出来的解是真正答案的相反数
			if (t == 1) {
				rep1(i, m) ans[id[n + i]] = a[i][0];
				rep1(i, n) printf("%.8lf ", ans[i]);
				putchar('\n');
			}
		}
	}
}lp;
int main() {
	srand(559320414);
	n = read(); m = read(); t = read();
	rep1(i, n) lp.a[0][i] = read();
	rep1(i, m) {
		rep1(j, n) {
			lp.a[i][j] = read();
		}
		lp.a[i][0] = read();
	}
	lp.work();
	return 0;
}
//事实上只需要记录非基变量，反正编号为i的基变量的系数向量除了i这个位置是1其他都是0，c[i]肯定为0，根本不用记录
//求解的时候要统一成sigma axi <= b的形式，而且是最大化目标函数，可以用取反或者对偶原理解决
//对偶原理：把c向量和b向量互换，a矩阵转置（如果像本程序用一个大矩阵记录的话就是把这整个矩阵转置），最大化变成最小化（最小化变成最大化），最终的答案不变

