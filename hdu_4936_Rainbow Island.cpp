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
#define N 25
#define M 800
int n, ntot;
int g[N][N], p[M][M];
double dp[N][M], f[N][N], pp[M][M];
double x[N], pi[N];

void check_f()
{
    int i, j;
    puts("check matrix:");
    for(i = 1; i <= n; i ++)
    {
        for(j = 1; j <= n; j ++)
            printf("%lf\t", f[i][j]);
        printf("=\t%lf", f[i][n + 1]);
        puts("");
    }
    puts("end check matrix.");
}


struct RainBow{
    int l;
    int a[N];
    void init()
    {
        memset(a,0,sizeof(a));
        l = 0;
    }
    bool operator<(const RainBow & R)const
    {
        if(l == R.l)
        {
            for(int i = 1; i <= l; i ++)
            {
                if(a[i] == R.a[i])  continue;
                return a[i] < R.a[i];
            }
        }
        return l < R.l;
    }
}r, tr;

map<RainBow, int>m;
int a[N];
void dfs(int tot, int maxn, int d, int nd)
{
    if(nd > d)
    {
        int i;
        r.init();
        r.l = d;
        for(i = 1; i <= d; i ++)    r.a[i] = a[i];
        m[r] = ++ntot;
        for(i = 1; i <= d; i ++)
            pp[ntot][ntot] += r.a[i] * (r.a[i] - 1);
        pp[ntot][ntot] /= n * (n - 1);


//        printf("%d : l = %d\tnum =\t", ntot, d);
//        for(i = 0; i < N; i ++)    if(r.a[i]) printf("%d:%d\t", i, r.a[i]);
//        puts("");
        p[ntot][0] = 0;
        if(d == 1)  return;
        int j, k, t;
        bool flag;
        for(i = 1; i < d; i ++)
        {
            for(j = i + 1; j <= d; j ++)
            {
                tr = r;
                tr.l --;
                tr.a[i] += tr.a[j];
                k = i;
                while(k > 1 && tr.a[k - 1] < tr.a[k])
                {
                    swap(tr.a[k - 1], tr.a[k]);
                    k --;
                }
                for(k = j; k < d; k ++)
                    tr.a[k] = tr.a[k + 1];
                tr.a[d] = 0;
                k = m[tr];
                //
//                printf("k: tr.l = %d\tnum :\t", tr.l);
//                for(t = 0; t < N; t ++)
//                    if(tr.a[t]) printf("%d:%d\t", t, tr.a[t]);
//                puts("");
                //
                flag = true;

                for(t = 1; t <= p[ntot][0]; t ++)
                {
                    if(p[ntot][t] == k)
                    {
                        flag = false;
                        break;
                    }
                }
                if(flag)
                {
                    p[ntot][ ++p[ntot][0] ] = k;
                }
                pp[ntot][k] += (r.a[i] * r.a[j] * 2) / (1.0 * n) / (1.0 * n - 1);
//                printf("p[%d][%d] = %d\tpp[%d][%d] = %lf\n", ntot, p[ntot][0], k, ntot, k, pp[ntot][k]);
//                printf("dfs : p[%d][0] = %d\n", ntot, p[ntot][0]);
            }
        }

        return;
    }
    int i, j;
    if(d == nd && tot <= maxn)
    {
        a[nd] = tot;
        dfs(0, 0, d, nd + 1);
        return;
    }

    for(i = min(tot - d + nd, maxn); i >= 1; i --)
    {
        if((d - nd) * i < tot - i)  break;
        a[nd] = i;
        dfs(tot - i, i, d, nd +1);
    }
}

double get_sub(int state, int island)
{
    int tIsland, tState, i, j, k;
    double res = 0.0;

    for(i = 1; i <= g[island][0]; i ++)
    {
        tIsland = g[island][i];
        for(j = 1; j <= p[state][0]; j ++)
        {
            tState = p[state][j];
            res += pp[state][tState] * dp[tIsland][tState];
        }
    }
    res *= pi[island];
    res += g[island][0];
    return res;
}

void make_f(int state)
{
    int i, j, k, t;
    for(i = 1; i <= n; i ++)
        for(j = 1; j <= n + 1; j ++)
            f[i][j] = 0.0;

    for(i = 1; i <= n; i ++)
    {
        f[i][n + 1] = get_sub(state, i);
        f[i][i] = g[i][0];
        for(j = 1; j <= g[i][0]; j ++)
        {
            f[i][g[i][j]] -= (1 - pi[i]) + pi[i] * pp[state][state];
        }
    }
}

void gauss()
{
    int i, j, k, g, id;
    double m1, m2;
    for(i = 1; i <= n; i ++)
    {
        id = i;
        for(j = i + 1; j <= n; j ++)
            if(fabs(f[j][i]) - fabs(f[id][i]) > eps)
                id = j;
        if(fabs(f[id][i]) < eps)    continue;
        if(id != i)
        {
            for(j = i; j <= n + 1; j ++)
                swap(f[id][j], f[i][j]);
        }
        for(j = i + 1; j <= n; j ++)
            if(fabs(f[j][i]) > eps)
            {
                for(k = n + 1; k >= i; k --)
                    f[j][k] = f[j][k] - f[i][k] * f[j][i] / f[i][i];
            }
    }

    for(i = n; i >= 1; i --)
    {
        if(fabs(f[i][i]) < eps)
            x[i] = 0.0;
        else{
            for(j = i + 1; j <= n; j ++)
                f[i][n + 1] -= x[j] * f[i][j];
            x[i] = f[i][n + 1] / f[i][i];
        }
    }
}

int main()
{
#ifndef ONLINE_JUDGE

    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);

#endif
    double ans;
    int T, cas, i, j, k, t;
    scanf("%d", &T);
    for(cas = 1; cas <= T; cas ++)
    {
        scanf("%d", &n);

        for(i = 1; i <= n; i ++)     scanf("%lf", pi + i);
        for(i = 1; i <= n; i ++)
        {
            scanf("%d", &g[i][0]);
            for(j = 1; j <= g[i][0]; j ++)
            {
                scanf("%d", &g[i][j]);
            }
        }
        ntot = 0;
        memset(pp, 0, sizeof(pp));
        for(i = 1; i <= n; i ++)
            dfs(n, n, i, 1);

        for(i = 1; i <= n; i ++)    dp[i][1] = 0;
        for(k = 2; k <= ntot; k ++)
        {
            make_f(k);

            gauss();

            for(i = 1; i <= n; i ++)
                dp[i][k] = x[i];
        }
        printf("Case #%d: %.6lf\n", cas, dp[1][ntot]);
    }
    return 0;
}
