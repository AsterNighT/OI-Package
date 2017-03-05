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
const int MAXINT = 100010;
struct edge {
	int u, v, l;
	edge(int _u, int _v, int _l) :u(_u), v(_v), l(_l) {}
	edge() {}
} tab[MAXINT * 2 + 100000];
int mid,lb = 0, rb = int(1e9)+10/*int(1e9)+10*/;
struct node {
	int lb,rb,mx;
	bool reset;
};
struct Segtree {
	node seg[400000];
	void init(int p,int l,int r) {
		if(l!=r) {
			init(p*2,l,(l+r)/2);
			init(p*2+1,(l+r)/2+1,r);
		}
		seg[p].lb=l;
		seg[p].rb=r;
		seg[p].mx=-INF;
		seg[p].reset=false;
	}
	void try_modify(int p,int l,int v) {
		if(seg[p].lb==seg[p].rb&&seg[p].lb==l) {
			if(seg[p].reset) {
				seg[p].mx=-INF;
				seg[p].reset=0;
			}
			seg[p].mx=max(seg[p].mx,v);
			return ;
		}
		if(seg[p].reset) {
			seg[p].mx=-INF;
			seg[p].reset=false;
			seg[p*2].reset=true;
			seg[p*2].mx=-INF;
			seg[p*2+1].reset=true;
			seg[p*2+1].mx=-INF;
		}
		int mid=(seg[p].lb+seg[p].rb)/2;
		if(mid>=l) try_modify(p*2,l,v);
		else try_modify(p*2+1,l,v);
		seg[p].mx=max(seg[p*2].mx,seg[p*2+1].mx);
	}
	int query(int p,int l,int r) {
		int ans=-INF;
		if(seg[p].lb==l&&seg[p].rb==r) {
			if(seg[p].reset) {
				seg[p].mx=-INF;
				seg[p].reset=0;
				seg[p*2].reset=true;
				seg[p*2].mx=-INF;
				seg[p*2+1].reset=true;
				seg[p*2+1].mx=-INF;
			}
			return seg[p].mx;
		}
		if(seg[p].reset) {
			seg[p].mx=-INF;
			seg[p].reset=0;
			seg[p*2].reset=true;
			seg[p*2].mx=-INF;
			seg[p*2+1].reset=true;
			seg[p*2+1].mx=-INF;
		}
		int mid=(seg[p].lb+seg[p].rb)/2;
		if(mid>=l) ans=max(ans,query(p*2,l,min(r,mid)));
		if(mid<r) ans=max(ans,query(p*2+1,max(l,1+mid),r));
		return ans;
	}
	void master_spark() {
		seg[1].reset=true;
	}
} segtree;
int n, l, r,cnt = 0,fa[MAXINT],Max,root,num;
int sz[MAXINT];
int maxv[MAXINT];
int vis[MAXINT];
int dis[MAXINT];
ll ans = 0;
vector<int> side[MAXINT + 10];
set<int> adrs;
int add_edge(int u, int v, int l) {
	tab[cnt] = edge(u, v, l);
	side[u].push_back(cnt++);
	tab[cnt] = edge(v, u, l);
	side[v].push_back(cnt++);
	return 0;
}
int getsize(int p,int fa) {
	sz[p]=1;
	maxv[p]=0;
	rep0(i,side[p].size()) {
		edge &eg=tab[side[p][i]];
		if(eg.v==fa||vis[eg.v])continue;
		getsize(eg.v,p);
		sz[p]+=sz[eg.v];
		if(sz[eg.v]>maxv[p]) maxv[p]=sz[eg.v];
	}
	return 0;
}
void dfsroot(int r,int p,int fa)  {
	if(sz[r]-sz[p]>maxv[p]) maxv[p]=sz[r]-sz[p];
	if(maxv[p]<Max)Max=maxv[p],root=p;
	rep0(i,side[p].size()) {
		edge &eg=tab[side[p][i]];
		if(eg.v==fa||vis[eg.v])continue;
		dfsroot(r,eg.v,p);
	}
}
void getinfo(int p,int d,int fa,int sum)  {
	if(d>r) return ;
	segtree.try_modify(1,d,sum);
	rep0(i,side[p].size()) {
		edge &eg=tab[side[p][i]];
		if(eg.v==fa||vis[eg.v])continue;
		getinfo(eg.v,d+1,p,sum+(eg.l>=mid?1:-1));
	}
}
void getans(int p,int d,int fa,int sum)  {
	if(d>r) return ;
	if(sum+segtree.query(1,max(0,l-d),r-d)>=0) {
		ans=1;
		return;
	}
	rep0(i,side[p].size()) {
		edge &eg=tab[side[p][i]];
		if(eg.v==fa||vis[eg.v])continue;
		getans(eg.v,d+1,p,sum+(eg.l>=mid?1:-1));
	}
}
int calc(int root) {
	rep0(i,side[root].size()) {
		edge &eg=tab[side[root][i]];
		if(vis[eg.v])continue;
		getans(eg.v,1,root,(eg.l>=mid?1:-1));
		getinfo(eg.v,1,root,(eg.l>=mid?1:-1));
	}
}

void dfs(int p)  {
	int rt;
	segtree.master_spark();
	segtree.try_modify(1,0,0);
	Max=n;
	getsize(p,-1);
	dfsroot(p,p,-1);
	calc(root);
	vis[root]=1;
	rt=root;
	rep0(i,side[rt].size()) {
		edge &eg=tab[side[rt][i]];
		if(vis[eg.v])continue;
		dfs(eg.v);
	}
}
int check(int a) {
	ans=-1;
	memset(vis,0,sizeof(vis));
	dfs(1);
	if(ans==1) return 1;
	return 0;
}
int main() {
	freopen("date.in","r",stdin);
	freopen("date.out","w",stdout);
	segtree.init(1,0,100000);
	int x,y,z;
	scanf("%d%d%d", &n, &l, &r);
	rep0(i, n - 1) {
		scanf("%d%d%d", &x, &y, &z);
		add_edge(x, y, z);
	}
	while (rb - lb > 1) {
		mid = (rb + lb) / 2;
		if (check(mid)) lb = mid;
		else rb = mid;
	}
	printf("%d", lb);
	return 0;
}
/*
С�� Լ��
(date.pas/c/cpp)
��Ŀ����
����ԲȦ֮�󣬿��ϱ����һ�����ȴ���԰������Լ�� 0.0
�ȴ���԰�� N �����㣬ͨ�� N-1 ��С��������ǡ�ù���һ�����Ρ���һ��С������ѡ
��һ����� S ��һ���յ� T�����Ŵ� S �� T �����·����ɢ�����ġ��졣������һ������
ֻ��ά��һ��ʱ�䣬�������־���Լ��ʱ�䲻��̫�̣�������Ҫ�� S �� T ��·���ϰ�����
��������С�� L��Ҳ���ܳ��� R��
ÿ��С������һ��Լ��ָ��������Ѵ� S �� T ����������С����Լ��ָ��˳��д����
����һ�����У���ô���ǿ��԰�������д�С��������Ȼ�����������е���λ��������
����ʱȡ�м�����ż������ʱȡ�м�ƫ��������������λ���ͼ�Ϊ�� S �� T ��·����Լ��
ָ������һ��֪����������Ҫ���ǰ���£�ѡ����� S ���յ� T�����Եõ��� S �� T ��·
�������Լ��ָ���Ƕ��٣�

�����ʽ
��һ���������� N,L,R��
������ N-1 ��ÿ���������� x,y,z����ʾ���� x,y ֮����һ��Լ��ָ��Ϊ z ��˫��С����

�����ʽ
���һ����������ʾ���Լ��ָ����

�����ģ���� 
*/ 
