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
#define LEN 32
int dp[LEN][3];
int a[LEN];

int get(int x)
{
    int i, j, k, len = 0, res = 0, y = x;
    while(x)
    {
        a[++len] = x % 10;
        x /= 10;
    }
    bool flag = false;
    int f = 0;
    int last = 0;
    for(i = len; i >= 1; i --)
    {
        res += a[i] * dp[i - 1][2];

        if(flag)    res += a[i] * dp[i - 1][0];
        if(!flag && last == 6 && a[i] > 2)   res += dp[i - 1][0];
        if(!flag && a[i] > 4)   res += dp[i - 1][0];
        if(!flag && a[i] > 6)   res += dp[i - 1][1];
        if( (last == 6 && a[i] == 2) || a[i] == 4 )  flag = true;

        last = a[i];
    }
    return y - res;
}

int main()
{
#ifndef ONLINE_JUDGE

    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);

#endif
    dp[0][0] = 1;   // bu han 62 & 4
    dp[0][1] = 0;   // bu han 62 & 4 dan yi 2 jie wei
    dp[0][2] = 0;   // han 62 huo 4

    int i, j, k, ans1, ans2, n, m;
    for(i = 1; i < LEN; i ++)
    {
        dp[i][0] = dp[i - 1][0] * 9  - dp[i - 1][1];
        dp[i][1] = dp[i - 1][0];
        dp[i][2] = dp[i - 1][2] * 10 + dp[i - 1][1] + dp[i - 1][0];

//        printf("%d : %d %d %d\n", i, dp[i][0], dp[i][1], dp[i][2]);
    }
    while(~scanf("%d%d", &n, &m) && (n || m))
    {
        ans1 = get(n);
        ans2 = get(m + 1);
//        printf("ans1 = %d\tans2 = %d\n", ans1, ans2);
        printf("%d\n", ans2 - ans1);
    }
    return 0;
}
