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
#define iter(i,v) for(edge* i=head[v];i;i=i->nxt)

using namespace std;
const int MAXINT = 1010;
const int MAXBUF = 5000000;
int boy,girl,n,m,cnt,mc[MAXINT],dis[MAXINT],ds,vis[MAXINT],mark_time,q[MAXINT],h,t;
char BUF[MAXBUF],*buf=BUF;
int read(){
    int x=0;
    while(!isdigit(*buf)){buf++;}
    while(isdigit(*buf)){x=x*10+*buf-'0';buf++;}
    return x;
}

struct edge{
	int u,v;
	edge *nxt;
	edge(){}
	edge(int _u,int _v,edge* _nxt){
		u=_u;v=_v;nxt=_nxt;
	}
}*head[MAXINT],e[500010];
void add_edge(int u,int v){
	e[cnt]=edge(u,v,head[u]);
	head[u]=&e[cnt++];
	//e[cnt]=edge(v,u,head[v]);
	//head[v]=&e[cnt++];
}
void get_input(){
	cnt=0;
	boy=read();girl=read();m=read();
	int u,v;
	rep0(i,m){
		u=read();v=read();
		add_edge(u,v+boy);
	}
}
bool bfs(){
	h=0;t=0;
	memset(dis,0xffff,sizeof dis);
	ds=INF;
	rep1(i,boy) if(!mc[i]) q[t++]=i,dis[i]=0;
	while(t!=h){
		int p=q[h++];
		if(dis[p]>ds) break;
		iter(i,p){
			if(dis[i->v]==-1){
				dis[i->v]=dis[p]+1;
				if(!mc[i->v]) ds=dis[i->v];
				else{
					dis[mc[i->v]]=dis[i->v]+1;
					//printf("%d \n",mc[i->v]);
					q[t++]=mc[i->v];
				}
			}
		}
	}
	return ds!=INF;
}
bool dfs(int p){
	iter(i,p){
		if(vis[i->v]<mark_time&&dis[i->v]==dis[p]+1){
			vis[i->v]=mark_time;
			if(!mc[i->v]||dfs(mc[i->v])){
				mc[p]=i->v;
				mc[i->v]=p;
				return 1;
			}
		}
	}
	return 0;
}
int get_match(){
	int ans=0;
	mark_time=0;

	while(bfs()){
		mark_time++;
		rep1(i,boy) if(!mc[i]&&dfs(i)) ans++;
	}
	return ans;
}
void work(){
	printf("%d\n",get_match());
	rep1(i,boy) printf("%d ",max(0,mc[i]-boy));
	printf("\n");
}
int main() {
	fread(BUF,1,MAXBUF,stdin);
    get_input();
	work();
    return 0;
}


