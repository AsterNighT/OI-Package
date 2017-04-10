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
	char c=getchar();
	while(!isalpha(c))c=getchar();
	return c;
}
const int MAXINT = 100010;
int dfn_cnt;
struct graph_node {
	int dfn, mdfn, sz, dep;
	graph_node *fa, *bson, *top;
	vector<graph_node*> e;
} v[MAXINT];
void dfs1 ( graph_node *p ) {
	p->sz = 1;
	rep0 ( i, p->e.size() ) {
		if ( p->e[i] != p->fa ) {
			p->e[i]->fa = p;
			p->e[i]->dep = p->dep + 1;
			dfs1 ( p->e[i] );
			p->sz += p->e[i]->sz;
			if ( !p->bson || p->bson->sz < p->e[i]->sz ) p->bson = p->e[i];
		}
	}
}
int dfs2 ( graph_node *p ) {
	p->dfn = p->mdfn = dfn_cnt++;
	if(p->bson) {
		p->bson->top = p->top;
		dfs2 ( p->bson );
		p->mdfn = max ( p->mdfn, p->bson->mdfn );
	}
	rep0 ( i, p->e.size() ) {
		if ( p->e[i] != p->fa&&p->e[i] != p->bson ) {
			p->e[i]->top = p->e[i];
			dfs2 ( p->e[i] );
			p->mdfn = max ( p->mdfn, p->e[i]->mdfn );
		}
	}
}
struct node {
	int lb, rb, mid;
	int tag, val;
	node* child[2];
	node() {}
	inline void pushup() {
		val = child[0]->val + child[1]->val;
	}
	inline void seg_set ( int t ) {
		val = ( rb - lb ) * t;
		tag = t;
	}
	inline void pushdown() {
		if ( rb - lb > 1 && tag != -1 ) rep0 ( i, 2 ) child[i]->seg_set ( tag );
		tag = -1;
	}
};
struct SegTree {
	node mempool[MAXINT * 4];
	node* root;
	int cnt;
	inline void make_tree ( int l, int r ) {
		root = make_tree(root,l,r);
	}
	inline node* make_tree ( node *v, int l, int r ) {
		int no = cnt++;
		mempool[no].lb = l;
		mempool[no].rb = r;
		mempool[no].mid = ( l + r ) >> 1;
		mempool[no].tag = 0;
		mempool[no].val=0;
		if(r-l>1) {
			mempool[no].child[0] = make_tree ( v, l, ( l + r ) >> 1 );
			mempool[no].child[1] = make_tree ( v, ( l + r ) >> 1, r );
			mempool[no].pushup();
		}
		return &mempool[no];
	}
	SegTree() {
		cnt = 0;
	}
	inline void seg_modify ( int l, int r, int v ) {
		seg_modify ( root, l, r,  v );
	}
	inline void seg_modify ( node* p, int l, int r, int v ) {
		if ( p->lb == l && p->rb == r ) {
			p->seg_set ( v );
		} else {
			p->pushdown();
			if ( l < p->mid ) seg_modify ( p->child[0], l, min ( r, p->mid ), v );
			if ( r > p->mid ) seg_modify ( p->child[1], max ( l, p->mid ), r, v );
			p->pushup();
		}
	}
	inline ll seg_query ( int l, int r ) {
		return seg_query ( root, l, r );
	}
	inline ll seg_query ( node* p, int l, int r ) {
		ll ans = 0;
		p->pushdown();
		if ( p->lb == l && p->rb == r ) {
			return p->val;
		} else {
			if ( l < p->mid ) ans += seg_query ( p->child[0], l, min ( r, p->mid ) );
			if ( r > p->mid ) ans += seg_query ( p->child[1], max ( l, p->mid ), r );
		}
		return ans;
	}
} st;
int install ( graph_node *p, graph_node *q=&v[0] ) { // for install
	int ans = 0;
	while ( p->top != q->top ) {
		if ( p->dep > q->dep ) {
			ans += p->dep - p->top->dep + 1 - st.seg_query ( p->top->dfn, p->dfn + 1 );
			st.seg_modify ( p->top->dfn, p->dfn + 1, 1 );
			p = p->top->fa;
		} else {
			ans += q->dep - q->top->dep + 1 - st.seg_query ( q->top->dfn, q->dfn + 1 );
			st.seg_modify ( q->top->dfn, q->dfn + 1, 1 );
			q = q->top->fa;
		}
	}
	if ( p->dep > q->dep ) {
		ans += p->dep - q->dep + 1 - st.seg_query ( q->dfn, p->dfn + 1 );
		st.seg_modify ( q->dfn, p->dfn + 1, 1 );
	} else {
		ans += q->dep - p->dep + 1 - st.seg_query ( p->dfn, q->dfn + 1 );
		st.seg_modify ( p->dfn, q->dfn + 1, 1 );
	}
	return ans;
}
int uninstall ( graph_node *p ) {
	int ans = 0;
	ans = st.seg_query ( p->dfn, p->mdfn + 1 );
	st.seg_modify ( p->dfn, p->mdfn +1, 0 );
	return ans;
}
int n,q,u;
char op;
int main() {

	n=read();
	st.make_tree(0,n);
	rep1(i,n-1) {
		u=read();
		v[i].e.pb(&v[u]);
		v[u].e.pb(&v[i]);
	}
	v[0].dep=1;
	dfs1(&v[0]);
	dfs2(&v[0]);
	//rep0(i,n) printf("%d %d %d\n",i,v[i].sz,v[i].dfn);
	q=read();
	while(q--) {
		op=get_ch();
		u=read();
		if(op=='i') {
			printf("%d\n",install(&v[u]));
		}
		if(op=='u') {
			printf("%d\n",uninstall(&v[u]));
		}
	}
	return 0;
}
/*
2
0
5
i 1
u 1
i 1
u 0
i 0
*/
