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
#define eps 10e-7
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define rep0(j,n) for(int j=0;j<n;++j)
#define rep1(j,n) for(int j=1;j<=n;++j)
#define pb push_back
#define set0(n) memset(n,0,sizeof(n))
#define ll long long
#define OJ codevs
using namespace std;
ll read(){
    char c=getchar();ll f=1,x=0;
    while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
    while(isdigit(c)){x=x*10+c-'0';c=getchar();}
    return f*x;
}
char get_ch(){
    char c=getchar();
    while(!isalpha(c)) c=getchar();
    return c;
}
const int MAXINT = 50010;
ll n,L,dp[MAXINT],sum[MAXINT],c[MAXINT],m,k,x,y;
ll q[MAXINT],l=0,r=0;
void init(){
    dp[0]=c[0]=0;
    q[r++]=0;
}
double slope(int p,int q){
    return (dp[p]+c[p]*c[p]-dp[q]-c[q]*c[q])/double(c[p]-c[q]);
}
int main() {
    n=read();L=read();
    init();
    rep1(i,n){
        sum[i]=read();
        sum[i]+=sum[i-1];
        c[i]=sum[i]+i;
        k=c[i]-L-1;
        while(r-l>1&&slope(q[l],q[l+1])<=k*2) l++;
        ll j=q[l];
        dp[i]=dp[j]+(k-c[j])*(k-c[j]);
        while(r-l>1&&slope(q[r-2],q[r-1])>=slope(q[r-1],i)) r--;
        q[r++]=i;
    }
    printf("%lld\n",dp[n]);
    return 0;
}

