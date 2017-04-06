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

using namespace std;
int read(){
    char c=getchar();int f=1,x=0;
    while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
    while(isdigit(c)){x=x*10+c-'0';c=getchar();}
    return f*x;
}
const int MAXINT = 50010;
ll mu[MAXINT],sum[MAXINT],prime[MAXINT],cnt=0,t,a,c,b,d,k;
bool not_prime[MAXINT];
void get_mu(){
	mu[1]=1;
	for(ll i=2;i<MAXINT;i++){
		if(!not_prime[i]){
			mu[i]=-1;
			prime[cnt++]=i;
		}
		for(ll j=0;j<cnt&&i*prime[j]<MAXINT;j++){
			not_prime[prime[j]*i]=1;
			if(i%prime[j]==0){
				mu[i*prime[j]]=0;
				break;
			}else{
				mu[i*prime[j]]=-mu[i];
			}
		}
	}
	rep1(i,MAXINT-1) mu[i]+=mu[i-1];
}
ll calc(int n,int m){
	ll pos=0,ans=0;
	if(n>m) swap(n,m);
	for(int i=1;i<=n;i=pos+1){
		pos=min(n/(n/i),m/(m/i));
		ans+=(mu[pos]-mu[i-1])*(n/i)*(m/i);
	}
	return ans;
}
int main() {
	get_mu();
	t=read();
	while(t--){
		a=read();b=read();c=read();d=read();k=read();
		printf("%lld\n",calc(b/k,d/k)-calc((a-1)/k,d/k)-calc((b/k),(c-1)/k)+calc((a-1)/k,(c-1)/k));
	}
    return 0;
}


