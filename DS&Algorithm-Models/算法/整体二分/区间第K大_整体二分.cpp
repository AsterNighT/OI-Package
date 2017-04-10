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
#define lowbit(x) (x&-x)
using namespace std;
int read(){
    char c=getchar();int f=1,x=0;
    while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
    while(isdigit(c)){x=x*10+c-'0';c=getchar();}
    return f*x;
}
const int MAXINT = 100010;
int n,m,ans[MAXINT],cnt=0;
struct FT{
	int sum[MAXINT],sz;
	void add(int p,int v){
		for(;p<=sz;p+=lowbit(p)) sum[p]+=v;
	}
	int get(int p){
		int ans=0;
		for(;p;p-=lowbit(p)) ans+=sum[p];
		return ans;
	}
}ft;
struct query{
	int l,r,k,cnt,no,tp;
	query(){}
	query(int _l,int _r,int _k,int _no){
		l=_l;
		r=_r;
		k=_k;
		no=_no;
		cnt=0;
		tp=2;
	}
	query(int _p,int _no){
		l=r=cnt=0;
		k=_p;
		no=_no;
		tp=1;
	}
}q[MAXINT*2],tmp[MAXINT*2];
void divide(int l_q,int r_q,int l_v,int r_v){//分别是询问[L,R)，二分到的答案的[L,R) 
	if(r_v-l_v<=1){
		for(int i=l_q;i<r_q;i++) if(q[i].tp==2) ans[q[i].no]=l_v;
		return ;
	}
	int mid=((l_v+r_v)>>1)-1;
	for(int i=l_q;i<r_q;i++) if(q[i].tp==1&&q[i].k<=mid) ft.add(q[i].no,1);
	for(int i=l_q;i<r_q;i++) if(q[i].tp==2) q[i].cnt = ft.get(q[i].r)-ft.get(q[i].l-1);
	for(int i=l_q;i<r_q;i++) if(q[i].tp==1&&q[i].k<=mid) ft.add(q[i].no,-1);
	int h=l_q,t=r_q;
	for(int i=l_q;i<r_q;i++) {
		if(q[i].tp==2){
			if(q[i].k<=q[i].cnt) tmp[h++]=q[i];
			else{
				q[i].k-=q[i].cnt;
				tmp[--t]=q[i];
			}
		}else{
			if(q[i].k<=mid) tmp[h++] = q[i];
			else tmp[--t] = q[i];
		}
	}
	for(int i=l_q;i<r_q;i++) q[i]=tmp[i];
	if(l_q!=h) divide(l_q,h,l_v,mid+1);
	if(r_q!=t) divide(t,r_q,mid+1,r_v);
}
void get_input(){
	n=read();m=read();
	int t1,t2,t3;
	rep1(i,n) {
		t1=read();
		q[cnt++] = query(t1,i);
	}
	rep0(i,m){
		t1=read();t2=read();t3=read();
		q[cnt++]=query(t1,t2,t3,i);
	}
	ft.sz=n;
}
void work(){
	divide(0,cnt,-INF,INF);
	rep0(i,m) printf("%d\n",ans[i]);
}
int main() {
    //freopen("in.txt","r",stdin);
	get_input();
	work();
    return 0;
}


