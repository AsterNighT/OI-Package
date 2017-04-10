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
const int MAXINT = 1000;
struct node{
    int v,size;
    node *child[2],*fa;
    void pushup(){
        size=child[0]->size+child[1]->size+1;
        //calculate something else like max or min
    }
    void pushdown(){
        //do something like lazy tags
    }
    node(){}
};
struct Splay{
    node mempool[MAXINT];
    int cnt;
    node nil,*root,*NIL;
    Splay(){
        cnt=0;
        NIL=&nil;
        NIL->v=INF;
        NIL->size=0;
        NIL->child[0]=NIL->child[1]=NIL->fa=NIL;
        root=NIL;

    }
    node *newnode(node *fa,int v){
        node *now=&mempool[cnt++];
        now->v=v;
        now->fa=fa;
        now->child[0]=now->child[1]=NIL;
        now->pushup();
        return now;
    }
    int checkfa(node* p){
        if(p==p->fa->child[0]) return 0; else return 1;
    }
    void rotate(node *p,int d){//0 for left,1 for right
        node *pfa=p->fa;
        pfa->pushdown();
        pfa->child[d]->pushdown();
        p->pushdown();
        //pushdown tags
        p->fa=pfa->fa;
        pfa->child[d^1]=p->child[d];
        pfa->child[d^1]->fa=pfa;
        p->child[d]=pfa;
        if(p->fa->child[0]==pfa) p->fa->child[0]=p;
        if(p->fa->child[1]==pfa) p->fa->child[1]=p;
        pfa->fa=p;
        //exchange children&father
        pfa->pushup();
        //pushup information
        if(root==pfa) root=p;//change root
    }
    void splay(node *p,node *pfa){
        p->pushdown();
        while(p->fa!=pfa){
            if(p->fa->fa==pfa){//need only 1 rotate
                rotate(p,checkfa(p)^1);
            }else
            if(checkfa(p)){
                if(checkfa(p->fa))rotate(p->fa,0);
                rotate(p,0);
            }else{
                if(!checkfa(p->fa))rotate(p->fa,1);
                rotate(p,1);
            }
        }
        p->pushup();
    }
    void find_s(int k,node *pfa){ //sequence
        node *p=root;
        p->pushdown();
        while(k!=p->child[0]->size+1){
            if(k<=p->child[0]->size) p=p->child[0];
            else k-=p->child[0]->size+1,p=p->child[1];
            p->pushdown();
        }
        splay(p,pfa);
    }
    void find(int k,node *pfa){ //BST
        node *p=root;
        p->pushdown();
        while(k!=p->v&&p!=NIL){
            if(k<p->v) p=p->child[0];
            else p=p->child[1];
            p->pushdown();
        }
        if(p!=NIL) splay(p,pfa);
    }
    int get_rank(int k) { //BST
		node *p=root;
		int ans=0;
		while(p!=NIL) {
			if(p->v>k) p=p->child[0];
            else if(p->v==k) {
                ans+=p->child[0]->size;
                break;
            } else {
                ans+=p->child[0]->size+1;
                p=p->child[1];
            }
		}
		return ans;
	}
	void insert_node(int k) { //BST
	    int tag;
		node *p=root;
		p->pushdown();
		if(root==NIL){ root=newnode(NIL,k);return ;}
		while(true) {
            if(k==p->v){
                //do something to cnt of p or sth
                break;
			}
			tag=k<p->v?0:1;
            if(p->child[tag]==NIL){
                p->child[tag]=newnode(p,k);
                p=p->child[tag];
                break;
            }else{
                p=p->child[tag];
                continue;
            }
            p->pushdown();
		}
		splay(p,NIL);
		return ;
	}
};
int main() {
    #ifndef OJ
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
    #endif // OJ

    return 0;
}

