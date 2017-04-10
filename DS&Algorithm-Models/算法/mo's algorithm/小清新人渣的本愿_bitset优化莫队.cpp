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
#include <bitset>
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
#define OJ luogu
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
const int MAXINT = 100010;
struct query{
    int opt,l,r,x,id,block;
}q[MAXINT];
bitset<MAXINT*2> apr,apr2;
int tm[MAXINT],n,m,a[MAXINT],sz,st[MAXINT],ed[MAXINT],ans[MAXINT],cnt;
bool cmp_mo(const query &a,const query &b){
    return a.block==b.block?a.r<b.r:a.block<b.block;
}
bool cmp_id(const query &a,const query &b){
    return a.id<b.id;
}
void get_info(){
    cnt=0;
    st[0]=0;
    rep1(i,m){
        if(q[i].block!=q[i-1].block){
            ed[cnt++]=i;
            st[cnt]=i;
        }
    }
}
void add(int p){
    tm[a[p]]++;
    if(tm[a[p]]==1) {
        //printf("%d +1\n",a[p]);
        apr[a[p]]=1,apr2[MAXINT-a[p]]=1;
    }
}
void remove(int p){
    --tm[a[p]];
    if(tm[a[p]]==0){
        //printf("%d -1\n",a[p]);
        apr[a[p]]=0,apr2[MAXINT-a[p]]=0;
    }
}
void extend(int &l,int &r,int nl,int nr){
    if(l<nl) for(int i=l;i<nl;i++) remove(i);
    if(l>nl) for(int i=nl;i<l;i++) add(i);
    if(nr>r) for(int i=r+1;i<=nr;i++) add(i);
    if(nr<r) for(int i=nr+1;i<=r;i++) remove(i);
    l=nl;r=nr;
}
void solve(){
    int l=1,r=0;
    rep0(i,cnt){
        for(int j=st[i];j<ed[i];j++){
            //printf("%d %d %d %d \n",l,r,q[j].r,q[j].r);
            extend(l,r,q[j].l,q[j].r);
            if(q[j].opt==1){
                ans[q[j].id]=(apr&(apr<<q[j].x)).any();
            }
            if(q[j].opt==2){
                ans[q[j].id]=((apr<<MAXINT)&(apr2<<(q[j].x))).any();
            }
            if(q[j].opt==3){
                ans[q[j].id]=0;
                rep1(k,ceil(sqrt(q[j].x))){
                    if(q[j].x%k==0&&apr[k]&&apr[q[j].x/k]){ans[q[j].id]=1;break;}
                }
            }
        }
    }
}
int main() {
    #ifndef OJ
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
    #endif // OJ
    n=read();m=read();
    rep1(i,n) a[i]=read();
    sz=ceil(sqrt(n));
    rep0(i,m){
        q[i].opt=read();
        q[i].l=read();
        q[i].r=read();
        q[i].x=read();
        q[i].id=i;
        q[i].block=(q[i].l-1)/sz;
    }
    q[m].block=INF;
    sort(q,q+m,cmp_mo);
    get_info();
    solve();
    rep0(i,m) {
        if(ans[i]) printf("hana\n"); else printf("bi\n");
    }
    return 0;
}
/*
1 1
1
2 1 1 2

*/
