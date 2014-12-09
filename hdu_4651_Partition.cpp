#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 100010
#define MOD 1000000007
int fa[N], fb[N], na, nb, ans[N];
void init()
{
    int i, j;
    for(na = 1; ; na ++)
    {
        fa[na] = na * (3 * na + 1) / 2;
        //printf("fa[%d] = %d\n", na, fa[na]);
        if(fa[na] >= N) break;
    }
    for(nb = 1; ; nb ++)
    {
        fb[nb] = nb * (3 * nb - 1) / 2;
        //printf("fb[%d] = %d\n", nb, fb[nb]);
        if(fb[nb] >= N) break;
    }
    ans[0] = 1;
    for(i = 1; i < N; i ++)
    {
        ans[i] = 0;
        for(j = 1; j <= na && fa[j] <= i; j ++)
            if((j & 1) == 0)   ans[i] = ((ans[i] - ans[i - fa[j]]) % MOD + MOD) % MOD;
            else        ans[i] = ((ans[i] + ans[i - fa[j]]) % MOD + MOD) % MOD;
        for(j = 1; j <= nb && fb[j] <= i; j ++)
            if((j & 1) == 0)   ans[i] = ((ans[i] - ans[i - fb[j]]) % MOD + MOD) % MOD;
            else        ans[i] = ((ans[i] + ans[i - fb[j]]) % MOD + MOD) % MOD;
        ans[i] = (ans[i] % MOD + MOD) % MOD;
    }

}

int main()
{
    int T, n;
    init();
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        printf("%d\n", ans[n]);
    }
}
