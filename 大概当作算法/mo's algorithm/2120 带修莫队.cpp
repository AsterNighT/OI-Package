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
    while(!isdigit(c)){c=getchar();}
    while(isdigit(c)){x=x*10+c-'0';c=getchar();}
    return f*x;
}
char get_ch(){
	char c= getchar();
	while(!isalpha(c)) c=getchar();
	return c;
}
const int MAXINT = 100010;
int n,m,cnt[MAXINT],l,r,cnt_b,sz,cnt_q,cnt_c=-1,ans[MAXINT],lb,rb,cntn,px;
int a[MAXINT],b[MAXINT];
char op;
struct query{
	int l,r,x,id,bl;
	query(int _l,int _r,int _x,int _id){
		l=_l;
		r=_r;
		x=_x;
		id=_id;
		bl=(l-1)/sz;
	}
	query(){}	
}q[MAXINT];
struct change{
	int p,v,ov,fc;
	change(){};
	change(int _p,int _v,int _ov){
		p=_p;
		v=_v;
		ov=_ov;
	}
}c[MAXINT];
bool operator < (const query &a,const query &b){
	return a.bl==b.bl?(a.r==b.r?a.x<b.x:a.r<b.r):a.bl<b.bl;
}
void add(int v){
	cnt[v]++;
	if(cnt[v]==1) cntn++;
}
void del(int v){
	cnt[v]--;
	if(cnt[v]==0) cntn--;
}
void add(int l,int r,change &v){
	v.ov=a[v.p];
	if(l<=v.p&&v.p<=r){
		add(v.v),del(v.ov);
	}
	a[v.p]=v.v;
}
void del(int l,int r,change &v){
	if(l<=v.p&&v.p<=r){
		del(v.v),add(v.ov);
	}
	a[v.p]=v.ov;
}
int main() {
	freopen("in.txt","r",stdin);
	freopen("outw.txt","w",stdout);
	n=read();m=read();
	rep1(i,n) a[i]=b[i]=read();
	sz=ceil(pow(n,0.666666666666666666));
	cnt_b=n;
	rep0(i,m){
		op=get_ch();
		l=read();
		r=read();
		if(op=='Q') {
			q[cnt_q]=query(l,r,cnt_c,cnt_q);
			cnt_q++;
		}else{
			b[++cnt_b] = r;
			c[++cnt_c] = change(l,r,a[l]);
		}
	}
	sort(b+1,b+cnt_b+1);
	cnt_b= unique(b+1,b+cnt_b+1) - b - 1;
	rep1(i,n) a[i] = lower_bound(b+1,b+cnt_b+1,a[i]) - b;
	rep0(i,cnt_c+1){
		c[i].ov= lower_bound(b+1,b+cnt_b+1,c[i].ov) - b;
		c[i].v= lower_bound(b+1,b+cnt_b+1,c[i].v) - b;
	}
	sort(q,q+cnt_q);
	lb=1;rb=0;px=-1;
	rep0(i,cnt_q){
		for(;lb<q[i].l;del(a[lb]),lb++);
		for(;lb>q[i].l;lb--,add(a[lb]));
		for(;rb<q[i].r;rb++,add(a[rb]));
		for(;rb>q[i].r;del(a[rb]),rb--);
		for(;px<q[i].x;px++,add(lb,rb,c[px]));
		for(;px>q[i].x;del(lb,rb,c[px]),px--);
		ans[q[i].id] = cntn;
	}
	rep0(i,cnt_q) printf("%d\n",ans[i]);
    return 0;
}


