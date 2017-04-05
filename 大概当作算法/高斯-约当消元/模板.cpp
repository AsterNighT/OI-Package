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
#define MOD 1234567891
#define rep0(j,n) for(int j=0;j<n;++j)
#define rep1(j,n) for(int j=1;j<=n;++j)
#define pb push_back
#define set0(n) memset(n,0,sizeof(n))
#define ll long long

using namespace std;
const int MAXINT = 1000;
int n,k;
ll qm(ll b,ll u){
	ll ans=1;
	for(;u;b=b*b%MOD,u>>=1) if(u&1) ans=ans*b%MOD;
	return ans;
}
struct matrix{
	ll mat[113][113];
	ll a[113];
	int solve(int n){ //0~n-1 未知数系数 n 常数项 
		int t,mul;
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				if(mat[i][j]!=0){
					t=j;
					break;
				}
			}
			for(int j=0;j<n;j++){
				if(j==i) continue;
				mul=mat[j][t];
				for(int k=0;k<=n;k++){
					mat[j][k]=mat[j][k]*mat[i][t]%MOD;
				}
				for(int k=0;k<=n;k++){
					mat[j][k]=(mat[j][k]-mat[i][k]*mul)%MOD;
				}
			}
		}
		rep0(i,n){
			rep0(j,n){
				if(mat[i][j]!=0) a[j]=(mat[i][n]*qm(mat[i][j],MOD-2))%MOD;
			}
		}
	}
	
}gs;

int calc(){ //求sigma i^k i∈[1,n] 
	ll w=k+1,presum[103]={};
	ll ans=0;
	presum[0]=0;
	rep1(i,w){
		presum[i]=(presum[i-1]+qm(i,k))%MOD;
	}
	rep0(i,w){
		rep0(j,w){
			gs.mat[i][j]=qm(i+1,j+1);
		}
		gs.mat[i][w]=presum[i+1];
	}
	gs.solve(w);
	rep0(i,w){
		ans=ans+qm(n,i+1)*gs.a[i]%MOD;
	}
	cout<<(ans%MOD+MOD)%MOD<<endl;
}
int main() {
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	scanf("%d%d",&n,&k);
	calc();
    return 0;
}


