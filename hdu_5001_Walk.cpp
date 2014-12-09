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
#define N 55
#define STEP 10010
vector<int>E[N];

double dp[N][STEP];
int n, d;
double solve(int x)
{
    int i, j, k, u, v, sz;
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1.0;
    double ans = 0;
    for(j = 0; j <= d; j ++)
    {
        for(i = 0; i <= n; i ++)
        {
            if(i == x)  continue;
            sz = E[i].size();
            double p = 1.0 / sz;
            for(k = 0; k < sz; k ++)
            {
                v = E[i][k];
                dp[v][j + 1] += dp[i][j] * p;
            }
        }
        ans += dp[x][j + 1];
    }
    //for(i = 1; i <= d + 1; i ++)

    return 1.0 - ans;
}

int main()
{
#ifndef ONLINE_JUDGE

    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);

#endif
    int m, i, j, u, v, T, sz;
    scanf("%d", &T);
    while(T --)
    {
        scanf("%d%d%d", &n, &m, &d);
        memset(dp, 0, sizeof(dp));
        for(i = 0; i <= n; i ++){
            E[i].clear();
        }
        for(i = 1; i <= m; i ++)
        {
            scanf("%d%d", &u, &v);
            E[u].push_back(v);
            E[v].push_back(u);
        }
        for(i = 1; i <= n; i ++)
        {
            E[0].push_back(i);
        }

        for(i = 1; i <= n; i ++)
        {
            printf("%.10lf\n", solve(i));
        }
    }
    return 0;
}
