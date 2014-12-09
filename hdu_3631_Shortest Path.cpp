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
#define N 301
int dp[N][N];
bool vis[N];
int n, m, q;
vector<int>E[N];

int main()
{
#ifndef ONLINE_JUDGE

//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);

#endif
    int i, j, k, u, v, c, sz, mu, mmin, op, cas = 1;
    while(~scanf("%d%d%d", &n, &m, &q))
    {
        if( !(n || m || q) )    break;
        memset(vis, 0, sizeof(vis));
        memset(dp, -1, sizeof(dp));
        for(i = 0; i < n; i ++)
        {
            dp[i][i] = 0;
            E[i].clear();
        }
        for(i = 1; i <= m; i ++)
        {
            scanf("%d%d%d", &u, &v, &c);
            E[u].push_back(v);
            if(dp[u][v] == -1 || dp[u][v] > c)
                dp[u][v] = c;
        }
        if(cas != 1)    puts("");
        printf("Case %d:\n", cas ++);
        while(q --)
        {
            scanf("%d", &op);
            if(op)
            {
                scanf("%d%d", &u, &v);
                if(!vis[u] || !vis[v])
                {
                    printf("ERROR! At path %d to %d\n", u, v);
                    continue;
                }
                if(dp[u][v] == -1)
                {
                    puts("No such path");
                    continue;
                }
                printf("%d\n", dp[u][v]);
            }else{
                scanf("%d", &u);
                if(vis[u])
                {
                    printf("ERROR! At point %d\n", u);
                    continue;
                }else{
                    vis[u] = true;
                    for(i = 0; i < n; i ++)
                        for(j = 0; j < n; j ++)
                        {
                            if(dp[i][u] == -1 || dp[u][j] == -1)    continue;
                            if(dp[i][j] == -1 || \
                               dp[i][j] > dp[i][u] + dp[u][j])
                                dp[i][j] = dp[i][u] + dp[u][j];
                        }
                }
            }
        }
    }
    return 0;
}
