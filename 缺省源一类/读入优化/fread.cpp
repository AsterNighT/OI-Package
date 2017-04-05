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
const int MAXINT = 1000000;
char buf[MAXINT],*p;
int read(){
	int f=1,x=0;
	while(!isdigit(*p)){if((*p++)=='-') f=-1;}
	while(isdigit(*p)){x=x*10+(*p++)-'0';}
	return x*f;
}
int main() {
	fread(buf,1,MAXINT,stdin);
	p=buf;
    return 0;
}


