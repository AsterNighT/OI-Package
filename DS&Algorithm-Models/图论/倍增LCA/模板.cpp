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
#define v(n) n->second
#define ll long long

using namespace std;
const int MAXINT = 1000;
vector<int> e[MAXINT]; //������ 
int dep[MAXINT]={},father[MAXINT][20]={}; //father[N][0] ΪN�ĸ��ڵ㣬���ڵ��ĸ��ڵ�Ϊ-1 
int dfs(int p,int depth);
int getA(int p); 
int n;//total number of nodes
int main() {
	
    return 0;
}
int dfs(int p,int depth){
	dep[p]=depth;
	rep0(i,e[p].size()){
		dfs(e[p][i],depth+1);
	}
	return 0;
}
int getA(int p){
	for(int i=1;i<20;i++){
		rep1(j,n){
			if(father[j][i-1]!=-1){
				father[j][i]=father[father[j][i-1]][i-1];
			}
		}
	}
	return 0;
} 
int getLCA(int u,int v){
	int i,j;
	if(dep[u]<dep[v]) swap(u,v);
	for(i=0;(1<<i)<=dep[u];i++);
	i--;
	for(j=i;j>=0;j--) if(dep[a]-(1<<j)>=dep[b]) a=father[a][j];
	if(a==b) return a;
	for(j=i;j>=0;j--){
		if(father[a][j]!=-1&&father[a][j]!=father[b][j]){
			a=father[a][j];
			b=father[b][j];
		}
	}
	return father[a][j];
}

