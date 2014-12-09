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
#define N 2010
int m[N];
int dp[2][N];

int main()
{
#ifndef ONLINE_JUDGE

    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);

#endif
    int T, n, i, j, k, sum, now, pre;
    scanf("%d", &T);
    while(T --)
    {
        scanf("%d", &n);
        sum = 0;
        for(i = 1; i <= n; i ++)
        {
            scanf("%d", m + i);
            sum += m[i];
        }
        sum = (sum + 1) / 2;
        memset(dp[0], 0, sizeof(dp[0]));
        dp[0][0] = 1;
        for(i = 1; i <= n; i ++)
        {
            now = i & 1;    pre = now ^ 1;
            memset(dp[now], 0, sizeof(dp[now]));
            for(j = 0; j <= m[i]; j ++)
            {
                for(k = j; k <= sum; k ++)
                    dp[now][k] = (dp[now][k] + dp[pre][k - j]) % MOD;
            }
        }
        now = n & 1;
        printf("%d\n", dp[now][sum]);
    }
    return 0;
}
