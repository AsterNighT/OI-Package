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
const int MAXINT = 5010;
struct edge {
    int u,v, cap, cost, lower;
    edge *next, *trans;
    edge ( int _u,int _v, int _c, edge* _nxt, edge* _trans ,int _cost, int lb) :u(_u),v ( _v ), cap ( _c ), next ( _nxt ), trans ( _trans ),cost(_cost),lower(lb) {}
    edge(){};
};
struct network {
    edge memp[100010];
    edge* e[MAXINT],*from[MAXINT];
    int num,cnt, dist[MAXINT], in[MAXINT], out[MAXINT],cnt2[MAXINT], ss, tt,vis[MAXINT];
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
    void delete_edge ( int u, int v ) {
        e[u] = e[u]->next;
        e[v] = e[v]->next;
    }
    int bfs ( int u, int v ) {
        int p;
        memset ( dist, 0xffff, sizeof ( dist ) );
        dist[u] = 0;
        queue<int> q;
        q.push ( u );
        while ( !q.empty() ) {
            p = q.front();
            q.pop();
            for ( edge *i = e[p]; i != NULL; i = i->next ) {
                if ( dist[i->v] == -1 && i->cap > 0 ) {
                    dist[i->v] = dist[p] + 1;
                    q.push ( i->v );
                }
            }
        }
        if ( dist[v] == -1 ) return 0;
        else return 1;
    }
    int flow ( int p, int t, int f ) {
        if ( p == t ) return f;
        int pflow = 0, tmp;
        for ( edge *i = e[p]; i != NULL; i = i->next ) {
            if ( dist[i->v] == dist[p] + 1 &&
                i->cap > 0 &&
                (tmp = flow ( i->v, t, min ( f - pflow, i->cap ) )) ) {
                i->cap -= tmp;
                i->trans->cap += tmp;
                pflow += tmp;
            }
        }
        return pflow;
    }
    int max_flow ( int s, int t ) {
        int tmp, ans = 0;
        while ( bfs ( s, t ) ) {
            while ( tmp = flow ( s, t, INF ) ) ans += tmp;
        }
        return ans;
    }
    int valid_flow() { //check if there is a valid flow,and do corresponding changes to the network
        int d,sf=0,tmp;
        rep1(i,num){
            d=in[i]-out[i];
            if(d>0){
                add_edge(ss,i,d,0);
                sf+=d;
            }
            if(d<0){
                add_edge(i,tt,-d,0);
            }
        }
        rep0(i,cnt){
            memp[i].cap=memp[i].cap-memp[i].lower;
        }
        tmp=max_flow(ss,tt);
        if(tmp==sf) return 1;else return 0;
    }
    void remove_sstt(){
        rep1(i,num){
            if(e[i]->v==ss) delete_edge(i,ss);
            if(e[i]->v==tt) delete_edge(i,tt);
        }
    }
    int valid_max_flow(int s,int t){ //valid flow quest will destroy the map
        int c1,c2;
        add_edge(t,s,INF,0);
        valid_flow();
        remove_sstt();
        c1=INF-e[t]->cap;
        delete_edge(s,t);
        c2=max_flow(s,t);
        return c1+c2;
    }
    int valid_min_flow(int s,int t){
        int c1,c2;
        add_edge(t,s,INF,0);
        valid_flow();
        remove_sstt();
        c1=INF-e[t]->cap;
        delete_edge(s,t);
        c2=max_flow(t,s);
        return c1-c2;
    }
    int spfa(int s,int t){
        int p;
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
    int min_cost_valid_flow(int s,int t){
        int tmp=cnt,cost=0;
        rep0(i,tmp){
            if(memp[i].cap>0&&memp[i].lower>0){
                add_edge(ss,memp[i].v,memp[i].lower,memp[i].cost,0);
                add_edge(memp[i].u,tt,memp[i].lower,0,0);
                memp[i].cap-=memp[i].lower;
            }
        }
        cost=min_cost_flow(s,t);
        return cost;
    }
};

int main() {
#ifndef OJ
    freopen ( ".in", "r", stdin );
    freopen ( ".out", "w", stdout );
#endif // OJ

    return 0;
}

