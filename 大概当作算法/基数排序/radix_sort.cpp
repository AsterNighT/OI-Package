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
const int MAXINT = 101000;
unsigned int cnt[65536],a[MAXINT],t[MAXINT],sec,tsa[MAXINT];
void radix_sort(unsigned int *a,unsigned int l){
	memset(cnt,0,sizeof(cnt));
	for(int i=0;i<l;i++) cnt[a[i]<<16>>16]++;
	for(int i=1;i<65536;i++) cnt[i]+=cnt[i-1];
	for(int i=l-1;i>=0;i--) t[--cnt[a[i]<<16>>16]] = a[i];
	memset(cnt,0,sizeof(cnt));
	for(int i=0;i<l;i++) cnt[t[i]>>16]++;
	for(int i=1;i<65536;i++) cnt[i]+=cnt[i-1];
	for(int i=l-1;i>=0;i--) a[--cnt[t[i]>>16]]=t[i];
}
int n;
int main() {
    n=read();
    rep0(i,n) a[i]=read();
    radix_sort(a,n);
	rep0(i,n) printf("%d ",a[i]);
    return 0;
}


