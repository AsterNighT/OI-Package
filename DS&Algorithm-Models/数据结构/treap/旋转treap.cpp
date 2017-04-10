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
	const int MAXINT = 500010;
	struct node{
		int v,fix,sz,cnt;
		node *fa,*c[2];
		void pushup(){
			sz=c[0]->sz+c[1]->sz+cnt;
		}
		int checkfa(){
			if(this==fa->c[0]) return 0; else return 1;
		}
	};
	struct Treap{
		node mempool[MAXINT],nil;
		node *NIL,*root;
		int cnt;
		Treap(){
			NIL=&nil;
			NIL->c[0]=NIL->c[1]=NIL->fa=NIL;
			NIL->v=NIL->fix=NIL->cnt=NIL->sz=0;
			root=NIL;
			cnt=0;
		}
		node* new_node(int v,node* fa){
			mempool[cnt].v=v;
			mempool[cnt].fix=rand();
			mempool[cnt].sz=mempool[cnt].cnt=1;
			mempool[cnt].c[0]=mempool[cnt].c[1]=NIL;
			mempool[cnt].fa=fa;
			if(fa!=NIL) {if(fa->v>v) fa->c[0]=&mempool[cnt]; else fa->c[1]=&mempool[cnt];}
			return &mempool[cnt++];
		}
		void rotate(node *p,int d){ //0 for left rotation
			node *pfa=p->fa;
			p->fa=pfa->fa;
			pfa->fa=p;
			pfa->c[d^1]=p->c[d];
			pfa->c[d^1]->fa=pfa;
			p->c[d]=pfa;
			pfa->pushup();
			p->pushup();
			if(root==pfa) root=p; else if(p->fa->c[0]==pfa) p->fa->c[0]=p; else p->fa->c[1]=p;
		}
		void insert(int v){
			node *p=root,*pre=NIL;
			while(p!=NIL){
				pre=p;
				if(v==p->v){
					p->cnt++;
					return ;
				}
				if(v>p->v) p=p->c[1]; else
				if(v<p->v) p=p->c[0];
			}
			p=new_node(v,pre);
			if(pre==NIL) root=p;
			heapify(p);
		}
		void heapify(node *p){
			while(p->fa!=NIL&&p->fix>p->fa->fix) rotate(p,p->checkfa()^1);
		}
		int find(int v){
			node *p=root;
			while(p!=NIL){
				if(p->v==v) return 1;
				if(p->v<v) p=p->c[1];
				if(p->v>v) p=p->c[0];
			}
			return 0;
		}
	}treap;
	int n,m,t;
	int main() {
		m=read();n=read();
		rep0(i,m){
			treap.insert(read());
		}
		rep0(i,n){
			printf("%d ",treap.find(read()));
		}
	    return 0;
	}

/*
5 5
9999999 4289 894 14 156
4289 894 14 156 9999999 

5 5
5 4 3 1 2
4 3 1 2 5

*/

