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
const int MAXINT = 1000010;
ll n,a,c,l,r,b,q[MAXINT],dp[MAXINT],sum[MAXINT],y,x,k,j;
double slope(int q,int p){
    return 1.0*(dp[q]+a*sum[q]*sum[q]-dp[p]-a*sum[p]*sum[p])/(sum[q]-sum[p]);
}
int main() {
    n=read();a=read();b=read(),c=read();
    r=1;
    rep1(i,n){
        sum[i]=read();
        sum[i]+=sum[i-1];
        k=2*a*sum[i]+b;
        while(r-l>1&&slope(q[l],q[l+1])>k) l++;
        j=q[l];
        dp[i]=dp[j]+a*(sum[i]-sum[j])*(sum[i]-sum[j])+b*(sum[i]-sum[j])+c;
        while(r-l>1&&slope(q[r-2],q[r-1])<=slope(q[r-1],i)) r--;
        q[r++]=i;
    }
    printf("%lld\n",dp[n]);
    return 0;
}

