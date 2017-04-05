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
double v[MAXINT],w[MAXINT]; //选k个,最大化sigma(v)/sigma(w) 
struct node{
	double v;
	int no;
	bool operator < (node b){
		return v>b.v;
	}
}cond[MAXINT];
int main() {
	int n,k;
	scanf("%d%d",&n,&k);
	rep0(i,n){
		scanf("%lf%lf",&v[i],&w[i]);
	} 
	double p=0.0,ans,sumv,sumw;
	while(true){
		ans=p;
		rep0(i,n){
			cond[i].v=v[i]-ans*w[i];
			cond[i].no=i;	
		}
		sumw=sumv=0.0;
		sort(cond,cond+n);
		rep0(i,k){
			sumw+=w[cond[i].no];
			sumv+=v[cond[i].no];
		}
		p=sumv/sumw;
		if(fabs(p-ans)<eps) break;
	}
	printf("%.2lf\n",ans);
    return 0;
}


