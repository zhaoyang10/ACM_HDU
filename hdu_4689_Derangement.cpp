#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 22
long long dp[N][N];
int n;
char str[N];
int main()
{
    int i, j;
    //freopen("in.txt", "r", stdin);
    while(~scanf("%s", str))
    {
        memset(dp, 0, sizeof(dp));
        n = strlen(str);
        dp[0][0] = 1;
        for(i = 1; i <= n; i ++)
        {
            if(str[i - 1] == '+')
            {
                for(j = 0; j <= i; j ++)
                {
                    if(j)   dp[i][j] += dp[i - 1][j - 1];
                    dp[i][j] += j * dp[i - 1][j];
                    //printf("dp[%d][%d] = %I64d\n", i, j, dp[i][j]);
                }
            }else if(str[i - 1] == '-'){
                for(j = 0; j <= i; j ++)
                {
                    dp[i][j] += j * dp[i - 1][j];
                    if(j + 1 <= i - 1)   dp[i][j] += (j + 1) * (j + 1) * dp[i - 1][j + 1];
                    //printf("dp[%d][%d] = %I64d\n", i, j, dp[i][j]);
                }
            }
        }
        printf("%I64d\n", dp[n][0]);
    }
    return 0;
}
