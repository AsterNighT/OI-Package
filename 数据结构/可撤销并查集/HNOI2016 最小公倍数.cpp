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
const int MAXINT = 100010;
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
struct edge{
    int x,y,a,b,id;
    edge(int _x,int _y,int _a,int _b,int _id):x(_x),y(_y),a(_a),b(_b),id(_id){}
    edge(){}
}e[MAXINT],qu[MAXINT];
struct op{
    int x,y,f,ma,mb,sz;
    op(){}
    op(int _x,int _y,int _f,int _ma,int _mb,int _sz):x(_x),y(_y),f(_f),ma(_ma),mb(_mb),sz(_sz){}
};
bool cmpa(const edge &a,const edge &b){
    return a.a==b.a?a.b<b.b:a.a<b.a;
}
bool cmpb(const edge &a,const edge &b){
    return a.b==b.b?a.a<b.a:a.b<b.b;
}
int fa[MAXINT],maxa[MAXINT],maxb[MAXINT],cnt,sz[MAXINT],n,m,q,bsz,qbf[MAXINT],ans[MAXINT];
stack<op> ops;
int find(int p){return fa[p]==p?p:find(fa[p]);}
void merge(int x,int y,int a,int b,bool mem){
    int X=find(x),Y=find(y);
    if(sz[X]>sz[Y]) swap(X,Y);
    if(mem) ops.push(op(X,Y,fa[X],maxa[Y],maxb[Y],sz[Y]));
    if(X==Y) {
        maxa[Y]=max(maxa[Y],a);
        maxb[Y]=max(maxb[Y],b);
        return;
    }
    fa[X]=Y;
    if(sz[X]==sz[Y]) sz[Y]++;
    maxa[Y]=max(maxa[Y],max(maxa[X],a));
    maxb[Y]=max(maxb[Y],max(maxb[X],b));
}
void merge(edge &t,bool mem){
    merge(t.x,t.y,t.a,t.b,mem);
}
void split(){
    while(!ops.empty()){
        op &t=ops.top();
        fa[t.x]=t.f;
        sz[t.y]=t.sz;
        maxa[t.y]=t.ma;
        maxb[t.y]=t.mb;
        ops.pop();
    }
}


int main() {
    n=read();m=read();
    rep0(i,m){
        e[i].x=read();
        e[i].y=read();
        e[i].a=read();
        e[i].b=read();
    }
    q=read();
    rep0(i,q){
        qu[i].x=read();
        qu[i].y=read();
        qu[i].a=read();
        qu[i].b=read();
        qu[i].id=i;
    }
    bsz=ceil(sqrt(m));
    sort(qu,qu+q,cmpb);
    sort(e,e+m,cmpa);
    for(int i=0;i<m;i+=bsz){
        int tot=0;
        rep0(j,q){
            if(qu[j].a>=e[i].a&&(i+bsz>=m||qu[j].a<e[i+bsz].a)) qbf[tot++]=j;
        }
        sort(e,e+i,cmpb);
        rep1(j,n) fa[j]=j,sz[j]=1,maxa[j]=maxb[j]=-1;
        int r=0;
        rep0(j,tot){
            for(;r<i&&qu[qbf[j]].b>=e[r].b;r++){
                merge(e[r],0);
            }
            for(int p=i;p<i+bsz&&p<m;p++){
                if(e[p].a<=qu[qbf[j]].a&&e[p].b<=qu[qbf[j]].b){
                    merge(e[p],1);
                }
            }
            int x=find(qu[qbf[j]].x),y=find(qu[qbf[j]].y);
            if(x==y&&maxa[x]==qu[qbf[j]].a&&maxb[x]==qu[qbf[j]].b) ans[qu[qbf[j]].id]=1; else ans[qu[qbf[j]].id]=0;
            split();
        }
    }
    rep0(i,q){
        if(ans[i]) printf("Yes\n"); else printf("No\n");
    }
    return 0;
}

