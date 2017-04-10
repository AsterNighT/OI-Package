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
const int MAXINT = 500100;
const int c_set=26;
int cnt=0,h,t;
struct node{
	node* c[c_set];
	node* fail;
	int count; //有多少个单词以此节点为结尾
	node(){
		memset(c,NULL,sizeof(c));
		fail=NULL;
		count=0;
	} 
}*q[MAXINT],mp[MAXINT],rn,*root=&rn;
char a[1000010];
node* new_node(){
	mp[cnt]=node();
	return &mp[cnt++];
}
void insert(char *s,node *p=root){
	int id,len=strlen(s);
	rep0(i,len){
		id=s[i]-'a';
		if(!p->c[id]) p->c[id]=new_node();
		p=p->c[id];
	}	
	p->count++;
}
void build_fail(node *r=root){
	node *temp,*p;
	root->fail=NULL;
	q[t++]=root;
	while(h!=t){
		temp=q[h++];
		p=NULL;
		rep0(i,c_set){
			if(temp->c[i]!=NULL){
				if(temp==root) temp->c[i]->fail=root;
				else{
					p=temp->fail;
					while(p){
						if(p->c[i]){
							temp->c[i]->fail=p->c[i];
							break;
						}
						p=p->fail;
					}
					if(!p) temp->c[i]->fail=root;
				}
				q[t++]=temp->c[i];
			}
		}
	}
}
int query(char *s,node *p=root){
	int ans=0,id,len=strlen(s);
	rep0(i,len){
		id=s[i]-'a';
		while(p!=root&&p->c[id]==NULL) p=p->fail;
		p=p->c[id];
		p=(p==NULL)?root:p;
		node *temp=p;
		while(temp!=root&&temp->count>=0){
			ans+=temp->count;
			temp->count=-temp->count;
			temp=temp->fail;
		}
	}
	return ans;
}
int n,m;
int main() {
	n=read();
	while(n--){
		m=read();
		cnt=0;
		rn=node();
		while(m--){
			scanf("%s",a);
			insert(a);
		}
		build_fail();
		scanf("%s",a);
		printf("%d\n",query(a));
	}
    return 0;
}


