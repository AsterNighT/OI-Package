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
#define eps 1e-7
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define rep0(j,n) for(int j=0;j<n;++j)
#define rep1(j,n) for(int j=1;j<=n;++j)
#define pb push_back
#define set0(n) memset(n,0,sizeof(n))
#define ll long long
#define iter(i,v) for(edge *i=head[v];i;i=i->nxt)
using namespace std;
const int MAXNODE = 50;
const int MAXEDGE = 5000;
int read(){
    char c=getchar();int f=1,x=0;
    while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
    while(isdigit(c)){x=x*10+c-'0';c=getchar();}
    return f*x;
}
int out[MAXNODE],cnt,n,m,vis[MAXNODE],mk_t;
struct edge{
	int u,v,is_rev;
	edge *nxt;
	edge(){}
	edge(int _u,int _v,edge* _nxt,int t){
		u=_u;
		v=_v;
		nxt=_nxt;
		is_rev= t;
	}
}*head[MAXNODE],e[MAXEDGE];
void add_edge(int u,int v){
	out[u]++;
	e[cnt] = edge(u,v,head[u],0);
	head[u]=&e[cnt++];
	e[cnt] = edge(v,u,head[v],1);
	head[v]=&e[cnt++];
}
struct gauss{
	double mat[MAXNODE][MAXNODE];
	int sz;
	void clear(){
		sz=0;
		memset(mat,0,sizeof(mat));
	}
	double solve(){
		int i,j,k,l;
		double prop;
		for(i=1;i<=sz;i++){
			for(j=i;j<=sz;j++) if(fabs(mat[j][i])>eps) break;
			if(fabs(mat[j][i])<eps) continue;
			if(i!=j) swap(mat[j],mat[i]),j=i;
			for(k=1;k<=sz;k++){
				if(k==j)continue;
				if(fabs(mat[k][i])<eps) continue;
				prop=mat[j][i]/mat[k][i];
				for(l=1;l<=sz+1;l++){
					mat[k][l]=mat[k][l]*prop-mat[j][l];
				}
			}
		}
		for(i=1;i<=sz;i++) if(fabs(mat[i][1])>eps){
			return mat[i][sz+1]/mat[i][1];
		}
		return 0.0;
	}
}gs;
void get_input(){
	n=read();m=read();
	int u,v;
	rep0(i,m){
		u=read();v=read();
		add_edge(u,v);
	}
}
void dfs(int p,int rt){
	vis[p]=mk_t;
	gs.mat[p][p]=1;
	if(out[p]==0){
		if(p==rt)gs.mat[p][n+1]=1;
		else gs.mat[p][n+1]=0;
	}
	iter(i,p){
		if(vis[i->v]!=mk_t&&i->is_rev) dfs(i->v,rt);
		if(i->is_rev==0){
			gs.mat[p][i->v] = -1.0/out[p];
			gs.mat[i->v][i->v] = 1;
		}
	}
}
double get_ans(int p){
	double ans;
	mk_t=p;
	gs.clear();
	gs.sz=n;
	dfs(p,p); 
	ans=gs.solve();
	return ans;
}
void work(){
	memset(vis,0xffff,sizeof(vis));
	double ans=0,tot=0,t;
	rep1(i,n){
		if(out[i]==0){
			t=get_ans(i);
			ans=fmax(t,ans);
			tot+=t;
		}
	}
	printf("%.6lf",ans/tot);
}
int main() {
	get_input();
	work();
    return 0;
}


