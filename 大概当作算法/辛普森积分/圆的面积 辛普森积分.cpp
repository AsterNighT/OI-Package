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
#define eps 10e-6
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
const int MAXINT = 210;
struct round{
	int x,r;
	double chord(double p){
		if(x+r<p||x-r>p) return 0.0;
		return sqrt(r*r-(p-x)*(p-x))*2;
	}
}r[MAXINT];
int n;
double f(double x){
	double ans=0;
	rep0(i,n) ans=fmax(ans,r[i].chord(x));
	return ans;
}
double s(double l,double r){
	return (f(l)+f(r)+f((l+r)/2)*4)*(r-l)/6;
}
double simpson(double l,double r,double pans){
	double lans=s(l,(l+r)*0.5);
	double rans=s((l+r)*0.5,r);
	if(fabs(pans-lans-rans)<eps) return pans;
	return simpson(l,(l+r)*0.5,lans)+simpson((l+r)*0.5,r,rans);
}
int main() {
	int lb=INF,rb=-INF;
	n=read();
	rep0(i,n) r[i].x=read();
	rep0(i,n) r[i].r=read();
	rep0(i,n){
		lb=min(lb,r[i].x-r[i].r);
		rb=max(rb,r[i].x+r[i].r);
	}
	printf("%.2lf",simpson(lb,rb,INF));
    return 0;
}



