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
#define rep0(j,n) for(unsigned int j=0;j<n;++j)
#define rep1(j,n) for(unsigned int j=1;j<=n;++j)
#define pb push_back
#define set0(n) memset(n,0,sizeof(n))
#define ll long long
#define ull unsigned long long
using namespace std;
int read(){
    char c=getchar();int x=0;
    while(!isdigit(c)){c=getchar();}
    while(isdigit(c)){x=x*10+c-'0';c=getchar();}
    return x;
}
const int MAXINT = 100002;
const int MAX_BLOCK=400;
unsigned int sz,bc;
ull pans[MAX_BLOCK][MAX_BLOCK]={};
unsigned int cnt[MAX_BLOCK][MAXINT]={},a[MAXINT]={},b[MAXINT]={},c=0,lb[MAX_BLOCK]={},rb[MAX_BLOCK]={},bl[MAXINT]={},num[MAXINT]={},s[MAXINT]={},top=0;
unsigned int n,m;
ull calc(unsigned int l,unsigned int r){
    ull maxv=0;
    for (unsigned int i=l;i<=r;i++){
        num[a[i]]++;
        ull tmp=(ull)(b[a[i]])*num[a[i]];
        maxv=maxv>=tmp?maxv:tmp;
    }
    for (unsigned int i=l;i<=r;i++){
        num[a[i]]=0;
    }
    return maxv;
}
int main() {
    n=read();m=read();
    rep0(i,n) a[i]=b[i]=read();
    sort(b,b+n);
    c=unique(b,b+n)-b;
    rep0(i,n) a[i]=lower_bound(b,b+c,a[i])-b;
    sz=ceil(sqrt(n));
    bc=(n-1)/sz+1;
    rep0(i,n){
        bl[i]=i/sz;
        if(!lb[bl[i]]) lb[bl[i]]=i;
        rb[bl[i]]=i;
    }
    lb[0]=0;
    rep0(i,n) cnt[bl[i]][a[i]]++;
    rep1(i,bc-1) rep0(j,c) cnt[i][j]+=cnt[i-1][j];
    for(unsigned int i=0;i<bc;i++){
        ull maxv=0;
        memset(num,0,sizeof(num));
        for(unsigned int j=lb[i];j<n;j++){
            num[a[j]]++;
            ull tmp=(ull)(b[a[j]])*num[a[j]];
            maxv=maxv>=tmp?maxv:tmp;
            pans[i][bl[j]]=(j==rb[bl[j]])?maxv:0;
        }
    }
    memset(num,0,sizeof(num));
    while(m--){
        unsigned int l=read()-1,r=read()-1;
        ull maxv=0;
        if(bl[l]+1<bl[r]){
            maxv=pans[bl[l]+1][bl[r]-1];
             
            for(unsigned int i=l;i<=rb[bl[l]];i++){
                if(!num[a[i]]){
                    num[a[i]]=cnt[bl[r]-1][a[i]]-cnt[bl[l]][a[i]];
                    s[top++]=a[i];
                }
                num[a[i]]++;
            }
            for(unsigned int i=lb[bl[r]];i<=r;i++){
                if(!num[a[i]]){
                    num[a[i]]=cnt[bl[r]-1][a[i]]-cnt[bl[l]][a[i]];
                    s[top++]=a[i];
                }
                num[a[i]]++;
            }
             
            ull tmp;
            while(top){
                tmp=s[--top];
                tmp=(ull)(b[tmp])*num[tmp];
                num[s[top]]=0;
                maxv=tmp<=maxv?maxv:tmp;
            }
        }else{
            maxv=calc(l,r);
        }
        printf("%llu\n",maxv);
    }
    return 0;
}