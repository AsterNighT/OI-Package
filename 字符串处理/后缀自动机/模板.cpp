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
const int MAXINT = 1000;
struct State {
    State *parent, *son[26];
    int val;
    State ( int _val ) : val ( _val ), parent ( 0 ) {
        memset ( son, 0, sizeof ( son ) );
    }
    State ( ) {}
};
struct SuffixAutoMaton {
    State *root, *last, *present;
    SuffixAutoMaton() {
        root = new State ( 0 );
        last = root;
        present = root;
    }
    void extend ( char c ) {
        int w = c - 'a';
        State *p = last;
        State *np = new State ( p->val + 1 );
        for ( ; p && p->son[w] == 0; p = p->parent ) p->son[w] = np;
        if ( p == 0 ) np->parent = root;
        else {
            State *q = p->son[w];
            if ( p->val + 1 == q->val ) {
                np->parent = q;
            } else {
                State *nq = new State ( p->val + 1 );
                memcpy ( nq->son, q->son, sizeof ( q->son ) );
                nq->parent = q->parent;
                q->parent = nq;
                np->parent = nq;
                for ( ; p && p->son[w] == q; p = p->parent ) p->son[w] = nq;
            }
        }
        last = np;
    }
    bool transit(char c){
        int w = c - 'a';
        if(present->son[w]==NULL) return false;
        else present=present->son[w];
        return true;
    }
};
int main() {

    return 0;
}

