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
#define eps 1e-7
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define rep0(j,n) for(int j=0;j<n;++j)
#define rep1(j,n) for(int j=1;j<=n;++j)
#define pb push_back
#define mp make_pair
#define set0(n) memset(n,0,sizeof(n))
#define ll long long
#define ull unsigned long long
#define iter(i,v) for(edge *i=head[v];i;i=i->nxt)
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
#define print_runtime printf("Running time:%.3lfs\n",double(clock())/1000.0)
#define TO(j) printf(#j": %d\n",j);
//#define OJ
using namespace std;
const int MAXINT = 100010;
const int MAXNODE = 100010;
const int MAXEDGE = 2 * MAXNODE;
char BUF, *buf;
int read() {
    char c = getchar(); int f = 1, x = 0;
    while (!isdigit(c)) { if (c == '-') f = -1; c = getchar(); }
    while (isdigit(c)) { x = x * 10 + c - '0'; c = getchar(); }
    return f * x;
}
char get_ch() {
    char c = getchar();
    while (!isalpha(c)) c = getchar();
    return c;
}
//------------------- Head Files ----------------------//
ll ans = 0;
int cnt[MAXINT], n, mu[MAXINT], prime[MAXINT], not_prime[MAXINT], cnt_p;
int a[MAXINT];
ll fm(ll b, ll u) {
    ll ans = 1;
    for (; u; u >>= 1, b = b * b % MOD) if (u & 1) ans = ans * b % MOD;
    return ans;
}
void get_mu() {
    mu[1] = 0;
    for (int i = 2; i <= 100000; i++) {
        if (!not_prime[i]) {
            prime[cnt_p++] = i;
            mu[i] = 1;
        }
        for (int j = 0; j < cnt_p && prime[j]*i <= 100000; j++) {
            not_prime[prime[j]*i] = 1;
            if (i % prime[j] == 0) {
                mu[prime[j]*i] = 0;
                break;
            } else {
                mu[prime[j]*i] = -mu[i];
            }
        }
    }
}
void get_input();
void work();
int main() {
    get_input();
    get_mu();
    work();
    return 0;
}
void work() {
    ans = fm(2, n) - 1;
    rep0(i, n) {
        if (a[i] == 1) continue;
        int ub = sqrt(a[i]), cnt_d = 0;
        for (int j = 1; j <= ub; j++) {
            if (a[i] % j == 0) {
                if (a[i] / j == j) cnt[j]++, cnt_d++;
                else cnt[j]++, cnt[a[i] / j]++, cnt_d += 2;
            }
        }
        //ans += cnt_d - 2;
    }
    ans = ans + MOD;
    rep1(i, 100000) {
        ans -= mu[i]*(fm(2, cnt[i]) - 1);
        ans = ans % MOD + MOD;
    }
    ans = ans % MOD;
    printf("%lld\n", ans);
}
void get_input() {
    n = read();
    rep0(i, n) a[i] = read();
}



