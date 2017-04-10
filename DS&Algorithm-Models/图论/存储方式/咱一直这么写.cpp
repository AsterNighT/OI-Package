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
const int MAXINT = 1000;
struct edge{
	int u,v,l;
	edge(int _u,int _v,int _l):u(_u),v(_v),l(_l){}
	edge(){}
};
vector<int> e[MAXINT];
edge G[20010];
int cnt;
void add_edge(int u,int v,int l){
	G[cnt]=edge(u,v,l);
	e[u].pb(cnt++);
}
int main() {

    return 0;
}


