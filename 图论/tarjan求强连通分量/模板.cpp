//codevs 1332 
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
#define rep0(j,n) for(int j=0;j<n;j++)
#define rep1(j,n) for(int j=1;j<=n;j++)
#define pb push_back
#define set0(n) memset(n,0,sizeof(n))
#define k(n) n->first
#define ll long long

using namespace std;
const int MAXINT = 5050;
struct edge{
	int u,v;
	edge(int _u,int _v):u(_u),v(_v){}
	edge(){}
};
vector<int> e[MAXINT];
vector<int> compo[MAXINT];
edge G[100010];
int dfn[MAXINT]={},low[MAXINT]={},cnt=0,no=0,color[MAXINT]={},size[MAXINT]={},inStack[MAXINT]={},cnt1=0,maxn=0,maxs=0;
stack<int> s;
int tarjan(int p){
	dfn[p]=low[p]=cnt++;
	inStack[p]=1;s.push(p);
	rep0(i,e[p].size()){
		edge &eg=G[e[p][i]];
		if(dfn[eg.v]==-1){
			tarjan(eg.v);
			low[p]=min(low[p],low[eg.v]);
		}else{
			if(inStack[eg.v]) low[p]=min(low[p],dfn[eg.v]);
		}
	}
	if(dfn[p]==low[p]){
		int tp;
		do{
			tp=s.top();s.pop();
			color[tp]=no;
			compo[no].pb(tp);
			inStack[p]=0;
		}while(tp!=p);
		no++;
	}
}
void add_edge(int u,int v,int d){
	G[cnt1]=edge(u,v);
	e[u].pb(cnt1++);
	if(d==2){
		G[cnt1]=edge(v,u);
		e[v].pb(cnt1++);
	}
}
int n,m;
int main() {
	int t1,t2,t3;
	memset(dfn,0xffff,sizeof(dfn));
	scanf("%d%d",&n,&m);
	rep0(i,m){
		scanf("%d%d%d",&t1,&t2,&t3);
		add_edge(t1,t2,t3);
	}
	rep1(i,n){
		if(dfn[i]==-1) tarjan(i);
	}
	maxs=0;
	rep0(i,no){
		sort(compo[i].begin(),compo[i].end());
		if(compo[i].size()>maxs){
			maxs=compo[i].size();
			maxn=i;
		}
		if(compo[i].size()==maxs&&compo[i][0]<compo[maxn][0]){
			maxs=compo[i].size();
			maxn=i;
		}
	}
	sort(compo[maxn].begin(),compo[maxn].end());
	printf("%d\n",maxs);
	rep0(i,maxs){
		printf("%d ",compo[maxn][i]);
	}
	putchar('\n');
    return 0;
}


