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
double p[5], c[N], px[N];
double p21, p31, p41, ta, tb;
double dp[N][N];
int main()
{
#ifndef ONLINE_JUDGE

    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);

#endif
    int n, m, K, i, j, k;
    while(~scanf("%d%d%d%lf%lf%lf%lf", \
    &n, &m, &K, p + 1, p + 2, p + 3, p + 4))
    {
        if(p[4] < eps)
        {
            puts("0.00000");
            continue;
        }
        p21 = p[2] / (1 - p[1]);
        p31 = p[3] / (1 - p[1]);
        p41 = p[4] / (1 - p[1]);

        dp[1][1] = p41 / (1 - p21);

        px[0] = 1.0;
        for(i = 1; i <= n; i ++)
            px[i] = px[i - 1] * p21;

        for(i = 2; i <= n; i ++)
        {
            c[1] = p41;
            k = min(K, i);
            for(j = 2; j <= k; j ++)
            {
                c[j] = p31 * dp[i - 1][j - 1] + p41;
            }
            for(; j <= i; j ++)
            {
                c[j] = p31 * dp[i - 1][j - 1];
            }
            ta = px[i];
            tb = 0.0;
            for(j = 2; j <= i; j ++)
            {
                tb *= p21;
                tb += c[j];
            }
            tb *= p21;
            tb += p41;
            dp[i][1] = tb / (1 - ta);
            for(j = 2; j <= i; j ++)
            {
                dp[i][j] = p21 * dp[i][j - 1] + c[j];
            }
        }
        printf("%.5lf\n", dp[n][m]);
    }



    return 0;
}
