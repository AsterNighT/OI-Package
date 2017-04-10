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
const int MAXINT = 100010;
struct node{
	int l,r,f;
	int v,dis;
}heap[MAXINT];
int merge(int a,int b){
	if(a==0) return b;
	if(b==0) return a;
	if(heap[a].v<heap[b].v) swap(a,b);
	heap[a].r = merge(heap[a].r,b);
	heap[heap[a].r].f=a;
	if(heap[heap[a].l].dis < heap[heap[a].r].dis) swap(heap[a].r,heap[a].l);
	if(heap[a].r==0) heap[a].dis=0; else heap[a].dis=heap[heap[a].r].dis+1;
	return a;
}
int pop(int a){
	int l = heap[a].l;
    int r = heap[a].r;
    heap[l].f = l;
    heap[r].f = r;
    heap[a].l = heap[a].r = heap[a].dis = 0;
    return merge(l, r);
}
int find(int p){return p==heap[p].f?p:find(heap[p].f);}
int n,m,u,v;
int x,y,t;
int main() {
	while(cin>>n){
	
	rep1(i,n) heap[i].v=read(),heap[i].f=i,heap[i].l=heap[i].r=heap[i].dis=0;
	m=read();
	rep0(i,m){
		u=read();
		v=read();
		x=find(u);
		y=find(v);
		if(x!=y){
			heap[x].v/=2;
			t=pop(x);
			x=merge(x,t);
			
			heap[y].v/=2;
			t=pop(y);
			y=merge(y,t);
			
			printf("%d\n",heap[merge(x,y)].v);
		}else{
			printf("-1\n");
		}
	}}
    return 0;
}


