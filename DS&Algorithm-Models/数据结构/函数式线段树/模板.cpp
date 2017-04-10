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
#define lc child[0]
#define rc child[1]

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
const int MAXINT = 100010;
struct node {
	int lb,rb,mid,cnt;
	node* child[2];
	node():lb(0),rb(0),mid(0),cnt(0) {}
	inline void pushup() {
		cnt=child[0]->cnt+child[1]->cnt;
	}
};
struct FunctionalSegTree {
	node mempool[MAXINT*300];
	node* mempool2[MAXINT],**root;
	int cnt,num;
	inline node* new_node(int l,int r){
        mempool[cnt].lb=l;
        mempool[cnt].rb=r;
        mempool[cnt].mid=(l+r)>>1;
        return &mempool[cnt++];
	}
	inline void make_tree (int l, int r ) {
		root[0] = __make_tree(l,r);
		num=r;
	}
	inline node* __make_tree(int l,int r) {
		int no=cnt++;
		mempool[no].lb=l;
		mempool[no].rb=r;
		mempool[no].mid=(l+r)>>1;
		if(l==r-1) mempool[no].cnt=0;
		else {
			mempool[no].child[0]=__make_tree(l,(l+r)>>1);
			mempool[no].child[1]=__make_tree((l+r)>>1,r);
			mempool[no].pushup();
		}
		return &mempool[no];
	}
	FunctionalSegTree() {
		cnt=0;
		root=&mempool2[0];
	}
	inline void insert_number(int p,int v){
        __insert_number(root[p-1],root[p],v);
	}
	inline void __insert_number(node *&p,node *&d,int v){
        d=new_node(p->lb,p->rb);
        d->child[0]=p->child[0];
        d->child[1]=p->child[1];
        d->cnt=p->cnt+1;
        if(p->rb-p->lb==1) return;
        if(v<p->mid) __insert_number(p->child[0],d->child[0],v);
        else __insert_number(p->child[1],d->child[1],v);
	}
	inline int query_kth(int l,int r,int k){
        return __query_kth(root[l],root[r],k);
	}
	inline int __query_kth(node *l,node* r,int k){
	    if(r->rb-r->lb==1) return r->lb;
        if(r->child[0]->cnt-l->child[0]->cnt>=k) return __query_kth(l->child[0],r->child[0],k);
        else return __query_kth(l->child[1],r->child[1],k-(r->child[0]->cnt-l->child[0]->cnt));
	}
} st;
int a[MAXINT],b[MAXINT],c,n,m,l,r,k;
int main() {
	freopen("in.txt","r",stdin);
	freopen("m.txt","w",stdout);
    n=read();m=read();c=0;
    rep1(i,n) b[++c]=a[i]=read();
    sort(b+1,b+c+1);
    rep1(i,n) a[i]=lower_bound(b+1,b+n+1,a[i])-b;
    st.make_tree(1,c+1);
    rep1(i,n) st.insert_number(i,a[i]);
    while(m--){
        l=read();r=read();k=read();
        printf("%d\n",b[st.query_kth(l-1,r,k)]);
    }
	return 0;
}
/*
5 3
9999 1 2 3 999
1 5 4
2 5 4
3 5 2
*/ 
