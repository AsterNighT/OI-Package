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
#define ll long long

using namespace std;
const int MAXINT = 1010;
struct edge{
	int u,v,l;
	edge(int _u,int _v,int _l):u(_u),v(_v),l(_l){}
	edge(){}
};
vector<int> e[MAXINT];
edge G[20010];
int cnt = 0,v[MAXINT]={},dis[MAXINT],inq[MAXINT]={};
int add_edge(int u,int v,int l){
	G[cnt]=edge(u,v,l);
	e[u].pb(cnt++);
	return 0;
}
int n,ml,md,n1,n2,d,ans;
int spfa(int src,int dist);
int main() {
	scanf("%d%d%d",&n,&ml,&md);
	rep0(i,ml){
		scanf("%d%d%d",&n1,&n2,&d);
		add_edge(n1,n2,d); //n2-n1<=D => n1->n2,D
	}
	rep0(i,md){
		scanf("%d%d%d",&n1,&n2,&d);
		add_edge(n2,n1,-d); //n2-n1>=D => n1-n2<=-d => n2->n1,-d
	}
	ans=spfa(1,n);
	printf("%d\n",ans);
    return 0;
}
int spfa(int src,int dist){
	memset(dis,INF,sizeof(dis));
	int p;
	queue<int> q;
	dis[src]=0;
	q.push(src);
	inq[src]=1;
	while(!q.empty()){
		p=q.front(); q.pop();
		inq[p]=0; v[p]++;
		if(v[p]>n) return -1; //复权环
		rep0(i,e[p].size()){
			edge& eg=G[e[p][i]];
			if(dis[p]+eg.l<dis[eg.v]){
				dis[eg.v]=dis[p]+eg.l;
				if(!inq[eg.v]){
					inq[eg.v]=1;
					q.push(eg.v);
				}
			}
		}
	}
	return dis[dist]==INF?-1:dis[dist]; //走不到终点说明对距离没有约束 
}
//http://oi.cdshishi.net/hzw/5051.html 
