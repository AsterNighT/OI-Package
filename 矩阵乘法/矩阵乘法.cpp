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
#define rep0(j,n) for(int j=0;j<n;j++)
#define rep1(j,n) for(int j=1;j<=n;j++)
#define pb push_back
#define set0(n) memset(n,0,sizeof(n))
#define k(n) n->first
#define v(n) n->second
#define ll long long

using namespace std;
const int MAXINT = 1000;
struct matrix {
	int h,l; //h*l的矩阵
	int content[30][30];
	matrix() {
		this->clear();
	}
	matrix operator * (matrix b) {
		matrix ans;
		ans.h=h;
		ans.l=b.l;
		rep0(i,h) {
			rep0(j,b.l) { //l=b.h 是运算有意义的必要条件
				rep0(k,l) {
					ans.content[i][j]=(ans.content[i][j]+content[i][k]*b.content[k][j])%MOD;
				}
			}
		}
		return ans;
	}
	matrix operator + (matrix b) {
		matrix ans;
		ans.h=h;
		ans.l=l;
		rep0(i,h) {
			rep0(j,l) {
				ans.content[i][j]=content[i][j]+b.content[i][j];
			}
		}
		return ans;
	}
	matrix operator - (matrix b) {
		matrix ans;
		ans.h=h;
		ans.l=l;
		rep0(i,h) {
			rep0(j,l) {
				ans.content[i][j]=content[i][j]-b.content[i][j];
			}
		}
		return ans;
	}
	void clear() {
		h=l=0;
		memset(content,0,sizeof(content));
	}
	void display() {
		printf("矩阵大小为%dx%d\n",h,l);
		rep0(i,h) {
			rep0(j,l) {
				printf("%d ",content[i][j]);
			}
			printf("\n");
		}
	}
};
int main() {
	matrix a,b;
	a.h=2;
	a.l=2;
	a.content[0][0]=0;
	a.content[0][1]=1;
	a.content[1][0]=1;
	a.content[1][1]=1;
	a.display();
	b=a;
	rep0(i,10) {
		a=a*b;
		a.display();
	}
	return 0;
}


