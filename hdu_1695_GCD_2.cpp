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
#define eps 1e-11
#define ll long long
#define ull unsigned long long
#define MOD 1000000007
#define N 100001
int pri[N], phi[N], p[N], num[N], ans[N];
bool vis[N];
ll f[N];
int tot = 0;


ll cal(int a, int b)
{
    if(a > b)   swap(a, b);
    if(a <= 0)  return 0LL;
    int i, j, k, t, state, s, mt;
    ll res = f[a], tres;

    for(i = a + 1; i <= b; i ++)
    {
        t = i;
        k = 0;
        while(t > 1)
        {
            j = ans[t];
            p[k++] = pri[j];
            if(pri[j] == 0) while(1);
            while(t % pri[j] == 0)  t /= pri[j];
        }
        tres = 0;
        state = (1 << k);
        for(j = 0; j < state; j ++)
        {
            mt = 1;
            s = 0;
            for(t = 0; t < k; t ++)
                if((j >> t) & 1)
                {
                    mt *= p[t];
                    s ++;
                }
            if(mt == 0) while(1);
            if(s & 1)   tres -= a / mt;
            else        tres += a / mt;
        }
        res += tres;
    }

    return res;
}

void init()
{
    int i, j, t;
    memset(vis, 0, sizeof(vis));
    for(i = 2; i < N; i ++)
    {
        if(!vis[i])
        {
            ans[i] = tot;
            pri[tot ++] = i;
        }
        for(j = 0; j < tot && i * pri[j] < N; j ++)
        {
            t = i * pri[j];
            vis[t] = true;
            ans[t] = j;
            if(i % pri[j] == 0) break;
        }
    }
    for(i = 1; i < N; i ++) phi[i] = i;
    for(i = 2; i < N; i += 2)   phi[i] >>= 1;
    for(i = 3; i < N; i += 2)
    {
        if(phi[i] == i)
        {
            for(j = i; j < N ; j += i)
            {
                phi[j] = phi[j] - phi[j] / i;
            }
        }
    }
    f[0] = 0;
    f[1] = 1;
    for(i = 2; i < N; i ++) f[i] = f[i - 1] + phi[i];
}

int main()
{
#ifndef ONLINE_JUDGE

    freopen("in.txt","r",stdin);
//    freopen("out-2.txt","w",stdout);

#endif
    int cas, T, n, i, j, a, b, c, d, k;
    ll ans[4];
    scanf("%d", &T);
    init();
    for(cas = 1; cas <= T; cas ++)
    {
        scanf("%d%d%d%d%d", &a, &b, &c, &d, &k);
        if(k == 0)
        {
            printf("Case %d: 0\n", cas);
            continue;
        }
        if(a > b)   swap(a, b);
        if(c > d)   swap(c, d);
        ans[0] = cal(b / k, d / k);
        ans[1] = cal((a - 1) / k, d / k);
        ans[2] = cal(b / k, (c - 1) / k);
        ans[3] = cal((a - 1) / k, (c - 1) / k);
        printf("Case %d: %I64d\n", cas, ans[0] - ans[1] - ans[2] + ans[3]);
    }
    return 0;
}
