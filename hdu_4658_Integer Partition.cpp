#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 100010
#define MOD 1000000007
int fa[N], fb[N], na, nb, p[N];
void init()
{
    int i, j;
    for(na = 1; ; na ++)
    {
        fa[na] = na * (3 * na + 1) / 2;
        if(fa[na] >= N) break;
    }
    for(nb = 1; ; nb ++)
    {
        fb[nb] = nb * (3 * nb - 1) / 2;
        if(fb[nb] >= N) break;
    }
    p[0] = 1;
    for(i = 1; i < N; i ++)
    {
        p[i] = 0;
        for(j = 1; j <= na && fa[j] <= i; j ++)
            if(j & 1)   p[i] = (p[i] + p[i - fa[j]]) % MOD;
            else        p[i] = (p[i] - p[i - fa[j]]) % MOD;
        for(j = 1; j <= nb && fb[j] <= i; j ++)
            if(j & 1)   p[i] = (p[i] + p[i - fb[j]]) % MOD;
            else        p[i] = (p[i] - p[i - fb[j]]) % MOD;
        p[i] = (p[i] + MOD) % MOD;
    }
    //for(i = 1; i <= 10; i ++)   printf("p[%d] = %d\n", i, p[i]);
}

void solve(int n, int k)
{
    int i, j, r = 0;
    r = p[n];
    for(i = 1; i <= na && k * fa[i] <= n; i ++)
        if(i & 1)   r = ((r - p[n - k * fa[i]]) % MOD + MOD) % MOD;
        else        r = ((r + p[n - k * fa[i]]) % MOD + MOD) % MOD;
    for(i = 1; i <= nb && k * fb[i] <= n; i ++)
        if(i & 1)   r = ((r - p[n - k * fb[i]]) % MOD + MOD) % MOD;
        else        r = ((r + p[n - k * fb[i]]) % MOD + MOD) % MOD;
    printf("%d\n", r);
}

int main()
{
    int T, n, k;
    init();
    scanf("%d", &T);
    while(T --)
    {
        scanf("%d%d", &n, &k);
        solve(n, k);
    }
    return 0;
}
