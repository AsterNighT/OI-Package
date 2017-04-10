/* TODO (#9#): æÿ≥À ‘ ‘£ø */

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
	int u,v;
	edge *nxt;
	edge(){}
	edge(int _u,int _v,edge* _nxt){
		u=_u;
		v=_v;
		nxt=_nxt;
	}
}*head[MAXNODE],e[MAXEDGE];
void add_edge(int u,int v){
	out[u]++;
	e[cnt] = edge(u,v,head[u]);
	head[u]=&e[cnt++];
}
struct matrix{
	double mat[MAXNODE][MAXNODE];
	int r,c;
	void clear(){
		r=c=0;
		memset(mat,0,sizeof(mat));
	}
	matrix(){
		clear();
	}
	matrix mul(matrix b){
		matrix ans;
		ans.r=r;
		ans.c=b.c;
		//c==b.r
		rep1(i,r){
			rep1(j,b.c){
				rep1(k,c){
					ans.mat[i][j]+=mat[i][k]*b.mat[k][j];
				}
			}
		}
		return ans;
	}
	void print(){
		rep1(i,r){
			rep1(j,c) printf("%.2lf ",mat[i][j]);
			printf("\n");
		}
		printf("\n");
	}
	matrix pow(int u){
		matrix base,ans;
		memcpy(&base,this,sizeof(base));
		ans.r=ans.c=max(r,c);
		rep1(i,ans.r) ans.mat[i][i]=1;
		for(;u;u>>=1,base=base.mul(base)) if(u&1) ans=ans.mul(base);
		return ans;
	}
}mtx,org;
void get_input(){
	n=read();m=read();
	int u,v;
	rep0(i,m){
		u=read();v=read();
		add_edge(u,v);
	}
}

void work(){
	double tot=0,mx=0;
	rep1(i,n){
		if(out[i]==0) mtx.mat[i][i]=1;
		else iter(j,i) mtx.mat[i][j->v]=1.0/out[i];
	}
	org.r=1;org.c=n;org.mat[1][1]=1;
	mtx.r=mtx.c=n;
	matrix ans = org.mul(mtx.pow(100));
	rep1(i,n) if(out[i]==0){
		mx=max(mx,ans.mat[1][i]);
		tot+=ans.mat[1][i];
	}
	printf("%.6lf",mx/tot);
}
int main() {
	get_input();
	work();
    return 0;
}


