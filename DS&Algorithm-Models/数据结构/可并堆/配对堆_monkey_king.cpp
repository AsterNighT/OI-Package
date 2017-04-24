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
#define MOD 1000000007
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
#define TO(j) printf("j: %d\n",j);
//#define OJ
using namespace std;
const int MAXINT = 100100;
const int MAXNODE = 100010;
const int MAXEDGE = 2 * MAXNODE;
char BUF, *buf;
int read() {
	int c = getchar(); int f = 1, x = 0;
	while (!isdigit(c)) {if (c == '-') f = -1; if(c==-1) return -INF; c = getchar();}
	while (isdigit(c)) {x = x * 10 + c - '0'; c = getchar();}
	return f * x;
}
char get_ch() {
	char c = getchar();
	while (!isalpha(c)) c = getchar();
	return c;
}
//------------------- Head Files ----------------------//
int cnt, h, t, n,a[MAXINT],m,fa[MAXINT];
struct node {
	node *f, *prv, *nxt, *c;
	int v, tag;
}*q[2 * MAXINT], *root[MAXINT], mp[MAXINT * 2];
node* new_node(int v) {
	mp[cnt].f=mp[cnt].nxt=mp[cnt].prv=mp[cnt].c=NULL;
	mp[cnt].v = v;
	return &mp[cnt++];
}
int find_fa(int p) {
	return fa[p]==p ? p:fa[p]=find_fa(fa[p]);
}
node* combine(node *a, node *b) {
	if(!a) return b;
	if(!b) return a;
	if (a->v < b->v) swap(a, b);
	b->nxt = a->c;
    if(a->c) a->c->prv = b;
    a->c = b;
    b->f = a;
	return a;
}

node* pop(node *pt) {
	h = t = 0;
	node *p = pt->c;
	while (p) {
		q[t++] = p;
		p = p->nxt;
	}
	rep0(i,t) q[i]->f=q[i]->nxt=NULL;
	while (t - h > 1) q[t++] = combine(q[h], q[h + 1]), h += 2;
	pt->c=NULL;
	return (h!=t?q[h]:NULL);
}
void del(node *p){
	if(p->prv) p->prv->nxt=p->nxt;
	if(p->nxt) p->nxt->prv=p->nxt;
	if(p==p->f->c) p->f->c=p->nxt;
	p->f=p->prv=p->nxt=NULL;
}
void get_input();
void work();
int main() {
	//freopen("in.txt","r",stdin);
	while((n=read())!=-INF){
		cnt=0;
		rep1(i,n) fa[i]=i,root[i]=&mp[i];
		get_input();
		work();
	}
	return 0;
}
void work() {
	rep0(i, m) {
		int u = read(),v=read();
		u=find_fa(u);v=find_fa(v);
		node* x=root[u],*y=root[v];
		if(x==y) printf("-1\n");
		else{
			fa[u]=v;
			node *_x = pop(x);
			node *_y = pop(y);
			x->v/=2;
			y->v/=2;
			x=combine(x,_x);
			y=combine(y,_y);
			x=combine(x,y);
			root[v]=x;
			printf("%d\n",x->v);
		}
	}
}
void get_input() {
	rep1(i,n){
		mp[i].v=read();
		mp[i].f=mp[i].nxt=mp[i].c=NULL;
	}
	m=read();
}

