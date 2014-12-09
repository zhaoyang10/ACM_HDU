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

double p[30];
int main()
{
#ifndef ONLINE_JUDGE

    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);

#endif
    int n, i, j, state, cnt;
    double ans, t;
    while(~scanf("%d", &n))
    {
        for(i = 0; i < n; i ++)
            scanf("%lf", p + i);
        ans = 0.0;
        state = (1 << n);
        for(i = 1; i < state; i ++)
        {
            t = 0;
            cnt = 0;
            for(j = 0; j < n; j ++)
                if(i & (1 << j))
                {
                    t += p[j];
                    cnt ++;
                }
            if(cnt & 1) ans += 1.0 / t;
            else        ans -= 1.0 / t;
        }
        printf("%.5lf\n", ans);
    }
    return 0;
}
