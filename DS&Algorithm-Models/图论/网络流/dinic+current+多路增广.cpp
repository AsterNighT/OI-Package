#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>
#include <cmath>
#include <map>
#include <vector>
#include <queue>
#define eps 10e-7
#define INF 0x3f3f3f3f
#define rep(j) for(int i=0;i<j;i++)

using namespace std;

const int MAXINT = 1000;

struct edge {
	int f,t,v;
	edge() {}
	edge(int _f,int _t,int _v):f(_f),t(_t),v(_v) {}
} side[MAXINT*MAXINT];

vector<int> tab[MAXINT];

int dis[MAXINT],n,r=0,m,current[MAXINT];   //n indicate the number of nodes in the graph, of which 1 is the source and n is the sink.

int add_edge(int f,int t,int v) {
	tab[f].push_back(r);
	side[r++]=edge(f,t,v);
	tab[t].push_back(r);
	side[r++]=edge(t,f,0);
}

int bfs() {
	memset(dis,0xffff,sizeof(dis));  //fill dis with -1.
	queue<int> q;
	int p;
	dis[1]=0;
	q.push(1);
	while(!q.empty()) {
		p=q.front();
		q.pop();
		for(int i=0; i<tab[p].size(); i++) {
			edge &e = side[tab[p][i]];  //&e是一个引用
			if(dis[e.t]==-1&&e.v>0) {
				dis[e.t]=dis[p]+1;
				q.push(e.t);
			}
		}
	}
	return (dis[n]>-1);  //if it is impossible to reach n from 1 in the remaining network, stop the dinic.
}

int dinic(int p,int flow) {
	int a,remain=flow;
	if(p==n) return flow;
	for(int i=current[p]; i<tab[p].size(); i++) {
		current[p]=i;
		edge &e = side[tab[p][i]];
		if(dis[e.t]==dis[p]+1&&e.v>0&&(a=dinic(e.t,min(remain,e.v)))) {
			e.v-=a;
			side[tab[p][i]^1].v+=a;
			remain-=a;
			if(remain==0) break;
		}
	}
	return(flow-remain);
}

int calc() {
	int ans=0,a;
	while(bfs()) {
		memset(current,0,sizeof(current));
		while(a=dinic(1,INF)) ans+=a;
	}
	return ans;
}

int main() {
	int f,t,v;
	cin>>n>>m;
	rep(m){
		cin>>f>>t>>v;
		add_edge(f,t,v);
	}
	cout<<calc()<<endl;
	return 0;
}
