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
const int MAXINT = 210;
struct edge {
    int v, cap;
    edge *next, *trans;
    edge ( int _v, int _c, edge* _nxt, edge* _trans ) : v ( _v ), cap ( _c ), next ( _nxt ), trans ( _trans ) {}
    edge (){};
};
struct network {
    edge memp[1000];
    edge* e[MAXINT];
    int num,cnt, dist[MAXINT];
    network(){
        cnt = 0;
    }
    void add_edge ( int u, int v, int c) {
        memp[cnt] = edge ( v, c, e[u], &memp[cnt + 1]);
        e[u] = &memp[cnt++];
        memp[cnt] = edge ( u, 0, e[v], &memp[cnt - 1]);
        e[v] = &memp[cnt++];
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
}net;
int n,m,u,v,c;
int main() {
#ifndef OJ
    freopen ( ".in", "r", stdin );
    freopen ( ".out", "w", stdout );
#endif // OJ
    m=read();
    n=read();
    rep0(i,m){
        u=read();v=read();c=read();
        net.add_edge(u,v,c);
    }
    printf("%d\n",net.max_flow(1,n))
;    return 0;
}

