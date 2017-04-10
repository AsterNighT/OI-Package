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
#include <time.h>
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
ll read(){
    char c=getchar();ll f=1,x=0;
    while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
    while(isdigit(c)){x=x*10+c-'0';c=getchar();}
    return f*x;
}
const ll MAXll = 1000;
ll gcd(ll a,ll b){
	ll t;
	while(b!=0){
		t=a%b;
		a=b;
		b=t;
	}
	return a;
}
ll f(ll x,ll a,ll m){
	return (x*x+a)%m;
}
ll pow(ll b,ll u,ll m){
	ll ans;
	for(ans=1;u;u>>=1,b=(b*b)%m) if(u&1) ans=(ans*b)%m;
	return ans;
}
ll pollard_rho(ll n,ll a){
	if((n&1)==0) return 2;
	ll x=rand()%n,y=x,p=1;
	while(p==1){
		x=f(x,a,n);
		y=f(f(y,a,n),a,n);
		p=gcd(n,abs(y-x));
	}
	return p;
}
ll miller_rabin(ll n,ll s){
	ll a,k,u,pre;
	if(n==2||n==3||n==5||n==7||n==11) return 1;
	if(n==1||!(n%2)||!(n%3)||!(n%5)||!(n%7)||!(n%11)) return 0; 
	u=n-1;
	while(!(u&1)){
		k++;u>>=1;
	}
	rep0(i,s){
		a=rand()%(n-2)+2;
		pre=a=pow(a,u,n);
		rep0(j,k){
			a=a*a%n;
			if(a==1&&pre!=1&&pre!=n-1) return 0;
			pre=a;
		}
	}
	return 1;
}
ll ans=0;
void decry(ll n){
	ll q;
	ans++;
	while((q=pollard_rho(n,rand()))==n);
	if(!miller_rabin(q,11)) decry(q); //else printf("%lld ",q);
	if(!miller_rabin(n/q,11)) decry(n/q); //else printf("%lld ",n/q);
}
ll n,q,t=1;
int main() {
	srand(time(0));
	t=read();
	while(t--){
		n=read();
		if(n==1){
			printf("0\n");
			continue;
		}
		if(miller_rabin(n,11)){
			printf("%d\n",1);
			continue;
		}
		ans=1;
		decry(n);
		printf("%lld\n",ans);
	}
	
	//decry(n);
    return 0;
}
