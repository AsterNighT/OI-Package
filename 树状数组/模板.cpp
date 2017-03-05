#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
#define maxn 222222
int n,tot,num[maxn];

struct BIT 
{
    #define lowbit(x) (x&(-x))
    int b[maxn],k;
    void init(int sz)
    {
        memset(b,0,sizeof(b));
		k=sz;
    }
    void update(int x,int v)
    {
        while(x<=k)
        {
            b[x]+=v;
            x+=lowbit(x);
        }
    }
    int query(int x)
    {
        int ans=0;
        while(x)
        {
            ans+=b[x];
            x-=lowbit(x);
        }
        return ans;
    }
    void clear(int x)
    {
        while(x<=k)
        {
            b[x]=0;
            x+=lowbit(x);
        }
    }
}bit;

int main()
{

}
