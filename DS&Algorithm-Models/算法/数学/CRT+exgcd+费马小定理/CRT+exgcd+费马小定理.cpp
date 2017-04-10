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
ll read(){
    char c=getchar();ll f=1,x=0;
    while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
    while(isdigit(c)){x=x*10+c-'0';c=getchar();}
    return f*x;
}
const int MAXINT = 1000;
ll a[MAXINT],m[MAXINT],M,n;
ll fp(ll b,ll u,ll mod){
	ll ans=1;
	for(;u;u>>=1,b=(b*b)%mod) if(u&1) ans=(ans*b)%mod;
	return ans;
}
void extend_Euclid(ll a, ll b, ll &x, ll &y)  {  
    if(b == 0){
        x = 1;
        y = 0;
        return;
    }
    extend_Euclid(b, a % b, x, y);
    ll tmp = x;
    x = y;
    y = tmp - (a / b) * y;
}
ll CRT(){  
    M = 1;  
    ll ans = 0;  
    rep0(i,n) M *= m[i];  
    rep0(i,n){  
        ll x, y;  
        ll Mi = M / m[i];  
        extend_Euclid(Mi, m[i], x, y);  
        ans = (ans + Mi * x * a[i]) % M;  
    }  
    if(ans < 0) ans += M;  
    return ans;  
}  
ll crt(){
	M=1;
	ll ans=0;
	rep0(i,n) M*=m[i];
	rep0(i,n) {
		ll Mi=M/m[i];
		ll rev = fp(Mi,m[i]-2,m[i]);
		ans=(ans+Mi*rev*a[i])%M;
	}
	return ans%M;
}
int main() {
	n=read();
	rep0(i,n){
		m[i]=read();
		a[i]=read();
	}
	cout<<CRT()<<endl;
    return 0;
}


