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
#define TO(j) printf(#j": %d\n",j);
//#define OJ
using namespace std;
const int MAXINT = 100010;
const int MAXNODE = 300010;
const int MAXEDGE = 2*MAXNODE;
char BUF,*buf;
int read(){
    char c=getchar();int f=1,x=0;
    while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
    while(isdigit(c)){x=x*10+c-'0';c=getchar();}
    return f*x;
}
char get_ch(){
    char c=getchar();
    while(!isalpha(c)) c=getchar();
    return c;
}
//------------------- Head Files ----------------------//
int n,cnt,dis[MAXNODE],q[MAXNODE],vis[MAXINT],far,mx,p1,p2,len,s;

struct edge{
	int u,v,l,bak;
	edge *nxt;
	edge(){}
	edge(int _v,int _u,int _l,edge *_nxt):u(_u),v(_v),l(_l),nxt(_nxt){}
}mp[MAXEDGE],*head[MAXNODE],*from[MAXNODE],*to[MAXNODE];
void add_edge(int,int,int);
void get_input();
void work();
int bfs(int);
int check(int);
int main() {
    get_input();
    work();
    return 0;
}
void work(){
	int p = p2;
	while(p!=p1){
		from[p]->bak=from[p]->l;
		from[p]->l=0;
		to[from[p]->u]=from[p];
		p=from[p]->u;
	}
	while(p!=p1){
		from[p]->l=from[p]->bak;
		p=from[p]->u;
	}
	bfs(p1);
	int lb=mx-1,rb=len;
	while(rb-lb>0){
		int mid = (lb+rb)/2;
		if(check(mid)) rb=mid;
		else lb=mid;
	}
	printf("%d\n",rb);
}
void get_input(){
    n=read();s=read();
    rep0(i,n-1){
    	int u=read(),v=read(),l=read();
    	add_edge(u,v,l);
    }
    p1=bfs(1);p2=bfs(p1);
    len=mx;
}
void add_edge(int u,int v,int l){
	mp[cnt]=edge(u,v,l,head[u]);
	head[u]=&mp[cnt++];
	mp[cnt]=edge(v,u,l,head[v]);
	head[v]=&mp[cnt++];
}
int bfs(int p){
	int *h,*t;
	memset(vis,0,sizeof(vis));
	memset(dis,INF,sizeof(dis));
	h=t=q;
	*t++=p;
	vis[p]=1;
	dis[p]=0;
	while(h!=t){
		p=*h++;
		iter(i,p){
			if(!vis[i->v]){
				vis[i->v]=1;
				dis[i->v]=dis[p]+i->l;
				*t++=i->v;
				from[i->v]=i;
			}
		}
	}
	mx=-1;
	rep1(i,n){
		if(dis[i]>mx){
			mx=dis[i];
			far=i;
		}
	}
	return far;
}
int check(int mxl){
	int pl=len;
	for(int t=mxl,p=p1;to[p]&&t>=to[p]->l;t-=to[p]->l,pl-=to[p]->l,p=to[p]->v);
	for(int t=mxl,p=p2;from[p]&&t>=from[p]->l;t-=from[p]->l,pl-=from[p]->l,p=from[p]->u);
	return pl<=s;
}

/*
思路很好的题，推荐一下
首先，答案路径一定在直径上，这个我不会严谨的证明，只有一个思路是这样的：
分两种情况：
1、其中一个端点不在直径上，那么从那个在直径的端点上dfs一遍，那么那个不在直径上的点的子树里一定会有某个点比直径的另一端还要远，不然这样不会是最优答案，这与直径的定义矛盾
2、两个端点都不在直径上，思路和上一个差不多
有了这个性质，显然答案的下界就是树上所有不在直径上的点到直径距离的最大值mx_l，这个把直径上的边长度设为0，dfs一遍就好了
答案的上界更显然，就是直径的长度len
现在唯一的问题就是，直径可能太长，不满足路径长度小于s这个限制
然后我们考虑一个直径的性质——从树上上任何一个点开始dfs，距离最远的一个点一定是直径的两个端点之一，那么如果我们把直径的端点向里“缩”一些距离w，这个距离至少要是mx_l，我们的最大距离也不会超过w！因为如果这个距离超过了w，那些原来走到直径上的终点没有被缩掉的点，到直径的距离不会变，变的只可能因为原来的终点不在路径上了，所以距离变长了，这样的话终点只可能是当前路径的端点，那从这个端点开始dfs，某个点会比原来直径的端点还远，这是不符合直径的性质的。
然后我们就可以二分这个w，如果直径两边各往里缩w之后长度<=s，就是可行
因为据说会爆栈？所以我写了BFS
*/