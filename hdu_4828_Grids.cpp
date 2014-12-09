#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<set>
#include<map>
#include<cmath>
using namespace std;
#define eps 1e-8
#define ll long long
#define ull unsigned long long
#define MOD 1000000007
#define N 1000000
ll f[N+1];

ll ext_gcd(ll a,ll b,ll& x,ll& y){
    ll t,ret;
    if (!b){
        x=1,y=0;
        return a;
    }
    ret=ext_gcd(b,a%b,x,y);
    t=x,x=y,y=t-a/b*y;
    return ret;
}


int main()
{
    int cas,T,i,n = N;
    scanf("%d",&T);
    ll x,y;
    f[1] = 1;
    for(i=2; i<=n; i++)
    {
        ext_gcd(i+1,MOD,x,y);
        f[i] =( ( (f[i-1] * (4 * i - 2)) % MOD )*  ( (x + MOD) % MOD ) ) % MOD;
    }

    for(cas = 1; cas <= T; cas ++)
    {
        scanf("%d",&n);
        printf("Case #%d:\n%I64d\n",cas,f[n]);
    }

    return 0;
}
