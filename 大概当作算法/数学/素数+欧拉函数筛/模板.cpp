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
//#define OJ
using namespace std;
int read(){
    char c=getchar();int f=1,x=0;
    while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
    while(isdigit(c)){x=x*10+c-'0';c=getchar();}
    return f*x;
}
char get_ch(){
    char c=getchar();
    while(!isalpha(c)) c=getchar();
    return c;
}
const int MAXINT = 1000;
int prime[MAXINT]={},n,cnt,not_prime[MAXINT]={},phi[MAXINT];
int main() {
    n=read();
    not_prime[0]=not_prime[1]=1;phi[1]=1;
    for(int i=2;i<=n;i++){
        if(!not_prime[i]) prime[cnt++]=i,phi[i]=i-1;
        for(int j=0;j<cnt && i*prime[j]<=n;j++){
            not_prime[i*prime[j]]=1;
            if(i%prime[j]==0){
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}else phi[i*prime[j]]=phi[i]*(prime[j]-1);
        }
    }
    rep1(i,n) printf("%d\n",phi[i]); 
    return 0;
}

