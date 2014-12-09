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
#define N 12
#define Mod 13

ll dp[N][Mod][3];
ll p[N + 2], a[N + 2];
int main()
{
#ifndef ONLINE_JUDGE

    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);

#endif
    memset(dp, 0, sizeof(dp));
    dp[0][0][0] = 1;
    ll n, i, j, k, len, ans, mod = 1;
    bool flag;
    p[0] = 1;
    for(i = 1; i <= N; i ++)
    {
        p[i] = p[i - 1] * 10 % Mod;
    }
    for(i = 1; i < N; i ++)
    {
        mod = p[i - 1];
        for(j = 0; j < Mod; j ++)
        {
            for(k = 0; k < 10; k ++)
            {
                if(k == 3)
                {
                    dp[i][(j + 3 * mod) % Mod][0] += dp[i - 1][j][0];
                    dp[i][(j + 3 * mod) % Mod][1] += dp[i - 1][j][0];
                    dp[i][(j + 3 * mod) % Mod][2] += dp[i - 1][j][2];
                }else if(k == 1){
                    dp[i][(j + 1 * mod) % Mod][0] += dp[i - 1][j][0] - dp[i - 1][j][1];
                    dp[i][(j + 1 * mod) % Mod][2] += dp[i - 1][j][2] + dp[i - 1][j][1];
                }else{
                    dp[i][(j + k * mod) % Mod][0] += dp[i - 1][j][0];
                    dp[i][(j + k * mod) % Mod][2] += dp[i - 1][j][2];
                }
            }
        }
    }
/*
    for(i = 0; i < N; i ++, puts(""))
        for(j = 0; j < Mod; j ++, puts(""))
            for(k = 0; k < 3; k ++)
                printf("dp[%d][%d][%d] = %d\t\t", i, j, k, dp[i][j][k]);
*/

    while(~scanf("%I64d", &n))
    {
        n ++;
        len = 0;
        while(n)
        {
            a[++len] = n % 10;
            n /= 10;
        }
        flag = false;   ans = 0;    mod = 0;
        a[len + 1] = 0;
        for(i = len; i >= 1; i --)
        {
            for(j = 0; j < a[i]; j ++)
                ans += dp[i - 1][ (Mod - ( mod + j * p[i - 1]) % Mod + Mod) % Mod ][2];

            if(flag)
            {
                for(j = 0; j < a[i]; j ++)
                    ans += dp[i - 1][ (Mod - ( mod + j * p[i - 1] ) % Mod + Mod) % Mod ][0];
            }

            if(!flag && a[i] > 1)
            {
                ans += dp[i - 1][ (Mod - ( mod + 1 * p[i - 1] ) % Mod + Mod) % Mod ][1];
            }
            if(!flag && a[i + 1] == 1 && a[i] > 3)
            {
                ans += dp[i - 1][ (Mod - ( mod + 3 * p[i - 1] ) % Mod + Mod) % Mod ][0];
            }
            if(a[i + 1] == 1 && a[i] == 3)  flag = true;

            mod = (mod + a[i] * p[i - 1]) % Mod;
        }
        printf("%I64d\n", ans);
    }

    return 0;
}
