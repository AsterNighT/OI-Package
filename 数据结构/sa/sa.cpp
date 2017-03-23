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
const int MAXINT = 1010;
int cntA[MAXINT]={},cntB[MAXINT]={},sa[MAXINT]={},rank[MAXINT]={},height[MAXINT]={},A[MAXINT],B[MAXINT],tsa[MAXINT];
int n;
char ch[MAXINT];
void solve()
{
    for (int i = 0; i < 256; i ++) cntA[i] = 0;
    for (int i = 1; i <= n; i ++) cntA[ch[i]] ++;
    for (int i = 1; i < 256; i ++) cntA[i] += cntA[i - 1];
    for (int i = n; i; i --) sa[cntA[ch[i]] --] = i;
    rank[sa[1]] = 1;
    for (int i = 2; i <= n; i ++)
    {
        rank[sa[i]] = rank[sa[i - 1]];
        if (ch[sa[i]] != ch[sa[i - 1]]) rank[sa[i]] ++;
    }
    for (int l = 1; rank[sa[n]] < n; l <<= 1)
    {
        for (int i = 0; i <= n; i ++) cntA[i] = 0;
        for (int i = 0; i <= n; i ++) cntB[i] = 0;
        for (int i = 1; i <= n; i ++)
        {
            cntA[A[i] = rank[i]] ++;
            cntB[B[i] = (i + l <= n) ? rank[i + l] : 0] ++;
        }
        for (int i = 1; i <= n; i ++) cntB[i] += cntB[i - 1];
        for (int i = n; i; i --) tsa[cntB[B[i]] --] = i;
        for (int i = 1; i <= n; i ++) cntA[i] += cntA[i - 1];
        for (int i = n; i; i --) sa[cntA[A[tsa[i]]] --] = tsa[i];
        rank[sa[1]] = 1;
        for (int i = 2; i <= n; i ++)
        {
            rank[sa[i]] = rank[sa[i - 1]];
            if (A[sa[i]] != A[sa[i - 1]] || B[sa[i]] != B[sa[i - 1]]) rank[sa[i]] ++;
        }
    }
    for (int i = 1, j = 0; i <= n; i ++)
    {
        if (j) j --;
        while (ch[i + j] == ch[sa[rank[i] - 1] + j]) j ++;
        height[rank[i]] = j;
    }
}   
int main(){

	return 0;
}

