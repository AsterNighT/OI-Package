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
int read(){
    char c=getchar();int f=1,x=0;
    while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
    while(isdigit(c)){x=x*10+c-'0';c=getchar();}
    return f*x;
}
const int MAXINT = 200010;
struct node{
    int lb,rb,mid;
    ll tag,val;
    node(){}
};
struct SegTree{
    node mempool[MAXINT*4];
	inline void seg_add(int p,int v){
		mempool[p].val+=(mempool[p].rb-mempool[p].lb)*v;
		mempool[p].tag+=v;
	}
    inline void pushdown(int p){
    	if(mempool[p].rb-mempool[p].lb>1){
    		seg_add(p*2,mempool[p].tag);
    		seg_add(p*2+1,mempool[p].tag);
		}
		mempool[p].tag=0;
	}
	inline void pushup(int p){
		mempool[p].val=mempool[p*2].val+mempool[p*2+1].val;
	}

    inline void make_tree(int *v,int p,int l,int r){
        mempool[p].lb=l;
        mempool[p].rb=r;
        mempool[p].mid=(l+r)>>1;
        mempool[p].tag=0;
        if(l==r-1) mempool[p].val=v[l];
        else{
            make_tree(v,p*2,l,(l+r)>>1);
            make_tree(v,p*2+1,(l+r)>>1,r);
            pushup(p);
        }
    }
    inline void seg_modify(int p,int l,int r,int v){
        if(mempool[p].lb==l&&mempool[p].rb==r){
            seg_add(p,v);
        }else{
        	pushdown(p);
            if(l<mempool[p].mid) seg_modify(p*2,l,min(r,mempool[p].mid),v);
            if(r>mempool[p].mid) seg_modify(p*2+1,max(l,mempool[p].mid),r,v);
    		pushup(p);
        }
    }
    inline ll seg_query(int p,int l,int r){
        ll ans=0;
        if(mempool[p].lb==l&&mempool[p].rb==r){
            return mempool[p].val;
        }else{
        	pushdown(p);
            if(l<mempool[p].mid) ans+=seg_query(p*2,l,min(r,mempool[p].mid));
            if(r>mempool[p].mid) ans+=seg_query(p*2+1,max(l,mempool[p].mid),r);
        }
        return ans;
    }
}st;
int a[MAXINT],n,q,op,l1,r1,v1;
int main() {

    n=read();
    rep0(i,n) a[i]=read();
    st.make_tree(a,1,0,n);
    q=read();
    while(q--){
        op=read();
        if(op==1){
            l1=read();r1=read();v1=read();
            st.seg_modify(1,l1-1,r1,v1);
        }
        if(op==2){
            l1=read();r1=read();
            printf("%lld\n",st.seg_query(1,l1-1,r1));
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
