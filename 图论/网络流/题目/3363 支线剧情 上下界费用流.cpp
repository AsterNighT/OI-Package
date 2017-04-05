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
int read() {
    char c = getchar();
    int f = 1, x = 0;
    while ( !isdigit ( c ) ) {
        if ( c == '-' ) f = -1;
        c = getchar();
    }
    while ( isdigit ( c ) ) {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return f * x;
}
char get_ch() {
    char c = getchar();
    while ( !isalpha ( c ) ) c = getchar();
    return c;
}
const int MAXINT = 1000;
struct edge {
    int u,v, cap, cost, lower;
    edge *next, *trans;
    edge ( int _u,int _v, int _c, edge* _nxt, edge* _trans ,int _cost, int lb) :u(_u),v ( _v ), cap ( _c ), next ( _nxt ), trans ( _trans ),cost(_cost),lower(lb) {}
    edge(){};
};
struct network {
    edge memp[MAXINT * MAXINT];
    edge* e[MAXINT],*from[MAXINT];
    int num,cnt, dist[MAXINT], in[MAXINT], out[MAXINT],cnt2[MAXINT],ss,tt,vis[MAXINT],tq[90000];
    network(){
        cnt = 0;
        set0 ( in );
        set0 ( out );
    }
    void add_edge ( int u, int v, int c, int cost = 0,int lower = 0 ) {
        memp[cnt] = edge ( u,v, c, e[u], &memp[cnt + 1], cost, lower );
        e[u] = &memp[cnt++];
        memp[cnt] = edge ( v,u, 0, e[v], &memp[cnt - 1], -cost, 0 );
        e[v] = &memp[cnt++];
        in[v] += lower;
        out[u] += lower;
    }
    /*int spfa(int s,int t){
        int p,l=0,r=1;
        set0(cnt2);
        memset(dist,INF,sizeof(dist));
        memset(from,0,sizeof(from));
        memset(vis,0,sizeof(vis));
        queue<int> q;
        dist[s]=0;
        q.push(s);
        while(!q.empty()){
            p=q.front();q.pop();
            vis[p]=1;
            for(edge *i=e[p];i;i=i->next){
                if(i->cap>0&&dist[i->v]>dist[p]+i->cost){
                    dist[i->v]=dist[p]+i->cost;
                    from[i->v]=i;
                    if(!vis[i->v]){
                        vis[i->v]=1;
                        cnt2[i->v]++;
                        if(cnt2[i->v]>num) return i->v;
                        q.push(i->v);
                    }
                }
            }
            vis[p]=0;
        }
        if(dist[t]==INF) return 0; else return -1;
    }*/
    int spfa(int s,int t){
        int p,l=0,r=1;
        set0(cnt2);
        memset(dist,INF,sizeof(dist));
        memset(from,0,sizeof(from));
        memset(vis,0,sizeof(vis));
        dist[s]=0;
        tq[l]=s;
        while(l!=r){
            p=tq[l++];
            vis[p]=1;
            for(edge *i=e[p];i;i=i->next){
                if(i->cap>0&&dist[i->v]>dist[p]+i->cost){
                    dist[i->v]=dist[p]+i->cost;
                    from[i->v]=i;
                    if(!vis[i->v]){
                        vis[i->v]=1;
                        cnt2[i->v]++;
                        if(cnt2[i->v]>num) return i->v;
                        tq[r++]=i->v;
                    }
                }
            }
            vis[p]=0;
        }
        if(dist[t]==INF) return 0; else return -1;
    }
    int cost_flow(int s,int t){
        int u=s,v=t,flow=INF,ans=0;
        for(;v!=u;v=from[v]->u) flow=min(flow,from[v]->cap);
        for(v=t;v!=u;v=from[v]->u) {
            ans+=flow*from[v]->cost;
            from[v]->cap-=flow;
            from[v]->trans->cap+=flow;
        }
        return ans;
    }
    int remove_negative_circle(int p){
        set0(vis);
        int u=p,flow=INF,ans;
        do{
            vis[u]=1;
            u=from[u]->u;
        }while(!vis[u]);
        p=u;
        do{
            flow=min(flow,from[u]->cap);
            u=from[u]->u;
        }while(u!=p);
        do{
            ans+=flow*from[u]->cost;
            from[u]->cap-=flow;
            from[u]->trans->cap+=flow;
            u=from[u]->u;
        }while(u!=p);
        return ans;
    }
    int min_cost_flow(int s,int t){
        int cost=0,tmp;
        while(tmp=spfa(s,t)){
            if(tmp==-1) cost+=cost_flow(s,t);
            else cost+=remove_negative_circle(tmp);
        }
        return cost;
    }
    int min_cost_valid_flow(){
        int tmp=cnt,cost=0;
        rep0(i,tmp){
            if(memp[i].cap>0&&memp[i].lower>0){
                add_edge(ss,memp[i].v,memp[i].lower,memp[i].cost,0);
                memp[i].cap-=memp[i].lower;
            }
        }
        rep1(i,num) add_edge(i,tt,out[i],0,0);
        cost=min_cost_flow(ss,tt);
        return cost;
    }
}net;
int n,k,v,c;
int main() {
#ifndef OJ
    freopen ( ".in", "r", stdin );
    freopen ( ".out", "w", stdout );
#endif // OJ
    n=read();
    rep1(i,n){
        k=read();
        rep0(j,k){
            v=read();c=read();
            net.add_edge(i,v,INF,c,1);
        }
        net.add_edge(i,1,INF,0,0);
    }
    net.ss=n+1;
    net.tt=n+2;
    net.num=n;
    printf("%d\n",net.min_cost_valid_flow());
    return 0;
}
/*
6
2 2 1 3 2
2 4 3 5 4
2 5 5 6 6
0
0
0
*/
