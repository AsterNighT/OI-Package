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
const int MAXINT = 100010;
int n,w[MAXINT]={},cnt_e;
ll ans[MAXINT][2],sum;
bool vis[MAXINT];
struct edge{
    int v;
    edge* next;
}*head[MAXINT],e[MAXINT*2],*e1,*e2;
void add_edge(int u,int v){
    e[cnt_e].v=u;
    e[cnt_e].next=head[v];
    head[v]=&e[cnt_e++];
    e[cnt_e].v=v;
    e[cnt_e].next=head[u];
    head[u]=&e[cnt_e++];
}
edge *rev (edge *a){
    return e+((a-e)^1);
}
void dfs(int p,edge *from){
    if(vis[p]){
        e1=from;
        e2=rev(from);
        return ;
    }
    vis[p]=1;
    for(edge *i=head[p];i;i=i->next){
        if(i==from) continue;
        dfs(i->v,rev(i));
    }
}
void dp(int p,edge* from){
    ans[p][0]=0;ans[p][1]=w[p];
    for(edge *i=head[p];i;i=i->next){
        if(i==from||i==e1||i==e2) continue;
        dp(i->v,rev(i));
        ans[p][0]+=max(ans[i->v][0],ans[i->v][1]);
        ans[p][1]+=ans[i->v][0];
    }
}
ll work(int p){
    ll ret;
    dfs(p,NULL);
    dp(e1->v,NULL);
    ret=ans[e1->v][0];
    dp(e2->v,NULL);
    return max(ret,ans[e2->v][0]);
}
int main() {
    n=read();
    rep1(i,n){
        w[i]=read();
        add_edge(i,read());
    }
    rep1(i,n){
        if(!vis[i])
            sum+=work(i);
    }
    printf("%lld\n",sum);
    return 0;
}

