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
	double a[MAXINT][MAXINT]; //m*n�ľ���[1,1]��[m,n]��ϵ������[0,1]��[0,n]��c��[1,0]��[m,0]��b��[0,0]��Ŀ�꺯��ֵ
	int id[MAXINT * 2];
	double ans[MAXINT];//1~n�Ƿǻ�������n+1~n+m�ǻ�����
	void pivot(int out, int in) {
		swap(id[n + out], id[in]);//�ѷǻ���������ȥ��������������
		double tmp = a[out][in];
		a[out][in] = 1;//�ѻ�������һ�л�����
		for (int i = 0; i <= n; i++) a[out][i] /= tmp;//����Ҫ����ȥ�ı���ϵ������1
		for (int i = 0; i <= m; i++) if (i != out && fabs(a[i][in]) > eps) {//����ϵ��������Ԫ����ʵ�ϰ�c��Ŀ�꺯��һ������
			tmp = a[i][in]; a[i][in] = 0;
			for (int j = 0; j <= n; j++) a[i][j] -= tmp*a[out][j];
		}
	}
	bool init_solution() {
		rep1(i, n) id[i] = i;
		while (1) {
			int in = 0, out = 0;
			for (int i = 1; i <= m; i++) if (a[i][0] < -eps && (!out || (rand() & 1)))out = i; //��ʼ�ⲻ�Ϸ������ѡһ�����Ϸ��Ļ�����������
			if (!out) break; //�Ϸ�
			for (int i = 1; i <= n; i++) if (a[out][i] < -eps && (!in || (rand() & 1))) in = i;//��һ����ϵ���ı�������ȥ������ʹ��ʼ��Ϸ�
			if (!in) {//û�а취ʹ��ʼ��Ϸ���
				printf("Infeasible\n");
				return false;
			}
			pivot(out, in);
		}
		return true;
	}
	bool simplex() {//��ⵥ����
		while (1) {
			int in = 0, out = 0;
			double mn = INF;
			for (int i = 1; i <= n; i++) if (a[0][i] > eps) { in = i; break; }//ѡһ��ϵ������0�Ķ���ȥ
			if (!in) break;//û��ϵ������0�ģ��Ѿ��ﵽ���Ž�
			for (int i = 1; i <= m; i++) 
				if (a[i][in] > eps && a[i][0] / a[i][in] < mn) {
					mn = a[i][0] / a[i][in]; out = i;
				}
			if (!out) {//û���κ����ƣ��޽��
				printf("Unbounded\n");
				return false;
			}
			pivot(out, in);
		}
		return true;
	}
	void work() {
		if (init_solution() && simplex()) {
			printf("%.8lf\n", -a[0][0]);//ע��һ��������Ľ��������𰸵��෴��
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
//��ʵ��ֻ��Ҫ��¼�ǻ��������������Ϊi�Ļ�������ϵ����������i���λ����1��������0��c[i]�϶�Ϊ0���������ü�¼
//����ʱ��Ҫͳһ��sigma axi <= b����ʽ�����������Ŀ�꺯����������ȡ�����߶�żԭ����
//��żԭ����c������b����������a����ת�ã�����񱾳�����һ��������¼�Ļ����ǰ�����������ת�ã�����󻯱����С������С�������󻯣������յĴ𰸲���

