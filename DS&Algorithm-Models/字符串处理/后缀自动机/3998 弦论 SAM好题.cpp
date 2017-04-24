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
#include <time.h>
#define eps 10e-7
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define rep0(j,n) for(int j=0;j<n;++j)
#define rep1(j,n) for(int j=1;j<=n;++j)
#define pb push_back
#define set0(n) memset(n,0,sizeof(n))
#define ll long long
#define OJ BZOJ
using namespace std;
int read(){
    char c=getchar();int f=1,x=0;
    while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
    while(isdigit(c)){x=x*10+c-'0';c=getchar();}
    return f*x;
}
char get_ch(){
    char c=getchar();
    while(!isalpha(c)) c=getchar();
    return c;
}
const int MAXINT = 2000010;
int _type,k,n;
char c[500010];
struct state{
    state* c[26],*parent;
    int num,maxl,sum;
};
struct SAM{
    state mp[MAXINT],r;
    state* root,*last,*present,*pos[MAXINT];
    int cnt_max[500010];
    int cnt;
    SAM(){
        cnt=0;
        present=root=last=&r;
    }
    state* new_state(int maxl){
        mp[cnt].maxl=maxl;
        return &mp[cnt++];
    }
    void extend(char c){
        int w=c-'a';
        state *p=last;
        state* np=new_state(p->maxl+1);
        for(;p&&!p->c[w];p=p->parent) p->c[w]=np;
        if(!p) np->parent=root;
        else{
            state* q=p->c[w];
            if(q->maxl==p->maxl+1) np->parent=q;
            else{
                state* nq=new_state(p->maxl+1);
                memcpy(nq->c,q->c,sizeof(q->c));
                nq->parent=q->parent;
                q->parent=np->parent=nq;
                for(;p&&p->c[w]==q;p=p->parent) p->c[w]=nq;
            }
        }
        last=np;
        np->num=1;
        //printf("%d\n",cnt);
    }
    void transit(char c){
        int w=c-'a';
        present=present->c[w]?present->c[w]:root;
    }
    void pre_calc(int __type){
        rep0(i,cnt) cnt_max[mp[i].maxl]++;
        rep1(i,n) cnt_max[i]+=cnt_max[i-1];
        for(int i=cnt-1;i>=0;i--) pos[cnt_max[mp[i].maxl]--]=&mp[i];
        for(int i=cnt;i;i--){
            if(__type==0) pos[i]->num=1;
            else pos[i]->parent->num+=pos[i]->num;
        }
        root->num=0;
        for(int i=cnt;i;i--){
            pos[i]->sum=pos[i]->num;
            rep0(j,26) if(pos[i]->c[j]) pos[i]->sum+=pos[i]->c[j]->sum;
        }
        rep0(j,26) if(root->c[j]) root->sum+=root->c[j]->sum;
    }
    void dfs(int k,state* p){
        if(k<=p->num) return;
        k-=p->num;
        rep0(i,26){
            if(p->c[i]){
                if(k<=p->c[i]->sum){
                    putchar(i+'a');
                    dfs(k,p->c[i]);
                    return ;
                }
                k-=p->c[i]->sum;
            }
        }
    }
}sam;
int main() {
    #ifndef OJ
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
    #endif // OJ
    scanf("%s",c);
    _type=read();k=read();
    n=strlen(c);
    rep0(i,n) sam.extend(c[i]);
    sam.pre_calc(_type);
    //printf("%d\n",sam.root->sum);
    if(sam.root->sum<k) return printf("-1\n"),0;
    sam.dfs(k,sam.root);
    return 0;
}

