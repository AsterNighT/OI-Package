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
const int MAXINT = 1000;
ll calc(ll ub){
	if(ub<=1) return ub;
	ll ans=0,lb=1,rb;
	while(lb<=ub){
		rb=ub/(ub/lb);
		ans+=(ub/lb)*(lb+rb)*(rb-lb+1)/2; //�ж�����������ub/left��Ԫ���г��� 
		lb=rb+1;
	}
	return ans;
}
int main() {
	ll l,r;
	scanf("%lld%lld",&l,&r);
	printf("%lld",calc(r)-calc(l-1));
    return 0;
}