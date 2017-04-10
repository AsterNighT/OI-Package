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
	char c=getchar();
	int f=1,x=0;
	while(!isdigit(c)) {
		if(c=='-') f=-1;
		c=getchar();
	}
	while(isdigit(c)) {
		x=x*10+c-'0';
		c=getchar();
	}
	return f*x;
}
const int MAXINT = 200010;
struct node {
	int lb,rb,mid;
	ll tag,val;
	node* child[2];
	node() {}
	inline void pushup() {
		val=child[0]->val+child[1]->val;
	}
	inline void seg_add(ll t) {
		val+=(rb-lb)*t;
		tag+=t;
	}
	inline void pushdown() {
		if(rb-lb>1) rep0(i,2) child[i]->seg_add(tag);
		tag=0;
	}
};
struct SegTree {
	node mempool[MAXINT*4];
	node* root;
	int cnt;
	inline void make_tree (int *v, int l, int r ) {
		root = __make_tree(v,l,r);
	}
	inline node* __make_tree(int *v,int l,int r) {
		int no=cnt++;
		mempool[no].lb=l;
		mempool[no].rb=r;
		mempool[no].mid=(l+r)>>1;
		mempool[no].tag=0;
		if(l==r-1) mempool[no].val=v[l];
		else {
			mempool[no].child[0]=__make_tree(v,l,(l+r)>>1);
			mempool[no].child[1]=__make_tree(v,(l+r)>>1,r);
			mempool[no].pushup();
		}
		return &mempool[no];
	}
	SegTree() {
		cnt=0;
	}
	inline void seg_modify ( int l, int r, int v ) {
		seg_modify ( root, l, r,  v );
	}
	inline void seg_modify(node* p,int l,int r,int v) {
		if(p->lb==l&&p->rb==r) {
			p->seg_add(v);
		} else {
			p->pushdown();
			if(l<p->mid) seg_modify(p->child[0],l,min(r,p->mid),v);
			if(r>p->mid) seg_modify(p->child[1],max(l,p->mid),r,v);
			p->pushup();
		}
	}
	inline ll seg_query ( int l, int r ) {
		return seg_query ( root, l, r );
	}
	inline ll seg_query(node* p,int l,int r) {
		ll ans=0;
		p->pushdown();
		if(p->lb==l&&p->rb==r) {
			return p->val;
		} else {
			if(l<p->mid) ans+=seg_query(p->child[0],l,min(r,p->mid));
			if(r>p->mid) ans+=seg_query(p->child[1],max(l,p->mid),r);
		}
		return ans;
	}
} st;
int a[MAXINT],n,q,op,l1,r1,v1;
int main() {

	n=read();
	rep0(i,n) a[i]=read();
	st.make_tree(a,0,n);
	q=read();
	while(q--) {
		op=read();
		if(op==1) {
			l1=read();
			r1=read();
			v1=read();
			st.seg_modify(l1-1,r1,v1);
		}
		if(op==2) {
			l1=read();
			r1=read();
			printf("%lld\n",st.seg_query(l1-1,r1));
		}
	}
	return 0;
}
/*
3
1 2 3
3
1 1 3 10
1 2 2 -10
2 1 3
*/
