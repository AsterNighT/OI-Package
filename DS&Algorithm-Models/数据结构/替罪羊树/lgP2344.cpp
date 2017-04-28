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
#define eps 1e-7
#define INF 0x3f3f3f3f
#define MOD 1000000009
#define rep0(j,n) for(int j=0;j<n;++j)
#define rep1(j,n) for(int j=1;j<=n;++j)
#define pb push_back
#define set0(n) memset(n,0,sizeof(n))
#define ll long long
#define ull unsigned long long
#define iter(i,v) for(edge *i=head[v];i;i=i->nxt)
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
#define print_rumtime printf("Running time:%.3lfs\n",double(clock())/1000.0);
#define TO(j) printf(#j": %d\n",j);
//#define OJ
using namespace std;
const int MAXINT = 600000;
const int MAXNODE = 100010;
const int MAXEDGE = 2 * MAXNODE;
const double alpha = 0.75;
char BUF, *buf;
int read() {
    char c = getchar(); int f = 1, x = 0;
    while (!isdigit(c)) { if (c == '-') f = -1; c = getchar(); }
    while (isdigit(c)) { x = x * 10 + c - '0'; c = getchar(); }
    return f * x;
}
char get_ch() {
    char c = getchar();
    while (!isalpha(c)) c = getchar();
    return c;
}
//------------------- Head Files ----------------------//
int n, m;
ll sum[MAXINT];
struct node {
    node *l, *r;
    int v, sz;
    ll sum, f;
    void pushup() {
        sz = l->sz + r->sz + 1;
        sum = l->sum + r->sum + f;
    }
};
struct ScapeGoatTree {
    node mp[MAXINT], *root, *NIL, nil;
    node *st[MAXINT], **bad;
    int cnt, r, l, flag;
    node *new_node(int v, int sum) {
        node *p = &mp[cnt++];
        p->v = v;
        p->sz = 1;
        p->sum = sum;
        p->f = sum;
        p->l = p->r = NIL;
        return p;
    }
    ScapeGoatTree() {
        cnt = 0;
        nil.sz = nil.v = nil.sum = nil.f = 0;
        NIL = &nil;
        root = NIL;
    }
    void pia(node **p) {
        l = 0;
        dfs(*p);
        *p = rebuild(0, l, *p);
    }
    void dfs(node *p) {
        if (p == NIL) return;
        dfs(p->l);
        st[l++] = p;
        dfs(p->r);
    }
    node* rebuild(int lb, int rb, node *p) {
        if (rb == lb) { p = NIL; return p; }
        if (rb - lb == 1) {
            p = st[lb];
            p->l = p->r = NIL;
            p->sum = p->f;
            p->sz = 1;
            return p;
        }
        int mid = (lb + rb) / 2;
        p = st[mid];
        p->l = rebuild(lb, mid, p->l);
        p->r = rebuild(mid + 1, rb, p->r);
        p->pushup();
        return p;
    }
    void ins(int v, int f) {
        flag = 0;
        insert(root, v, f);
        if (flag) pia(bad);
    }
    void insert(node *&p, int v, int f) {
        if (p == NIL) {
            p = new_node(v, f);
            return;
        }
        if (v > p->v) insert(p->r, v, f);
        if (v < p->v) insert(p->l, v, f);
        if (v == p->v) p->f += f;
        p->pushup();
        if (p->l->sz > p->sz * alpha || p->r->sz > p->sz * alpha) {
            flag = 1;
            bad = &p;
        }
    }
    int ser(int v) {
        if (search(root, v) != NIL) return 1; else return 0;
    }
    node *search(node *p, int v) {
        if (p == NIL) return p;
        if (v > p->v) return search(p->r, v);
        if (v < p->v) return search(p->l, v);
        if (v == p->v) return p;
    }
    ll get(int v) {
        ll ans = _get(root, v);
        return ans % MOD;
    }
    ll _get(node *p, int v) {
        ll ans = 0;
        if (p == NIL) return 0;
        if (v >= p->v) ans += p->l->sum + p->f, ans += _get(p->r, v);
        if (v < p->v) ans += _get(p->l, v);
        return ans;
    }
} sgt;
void get_input();
void work();
int main() {
    get_input();
    work();
    return 0;
}
void work() {
    sgt.ins(0, 1);
    int p;
    rep1(i, n) {
        p = sgt.get(sum[i]);
        sgt.ins(sum[i], p);
    }
    printf("%d\n", p);
}
void get_input() {
    n = read();
    rep1(i, n) {
        sum[i] = sum[i - 1] + read();
    }
}

