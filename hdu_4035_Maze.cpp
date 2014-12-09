/*
    Ai =        (ki+(1-ki-ei)/m*∑Aj)   / (1 - (1-ki-ei)/m*∑Bj);
    Bi =        (1-ki-ei)/m            / (1 - (1-ki-ei)/m*∑Bj);
    Ci = ( (1-ki-ei)+(1-ki-ei)/m*∑Cj ) / (1 - (1-ki-ei)/m*∑Bj);

    对于叶子结点
    Ai = ki;
    Bi = 1 - ki - ei;
    Ci = 1 - ki - ei;
*/
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
#define N 10010
double E[N], K[N], A[N], B[N], C[N];
vector<int>e[N];

void dfs(int u, int f)
{
    int i, v, sz = e[u].size();
    double m = 0, sa = 0, sb = 0, sc = 0;
    //printf("u = %d\t sz = %d\n", u, sz);
    if(sz == 1 && u != 1)
    {
        A[u] = K[u];
        B[u] = 1.0 - K[u] - E[u];
        C[u] = 1.0 - K[u] - E[u];
    }else{
        m = sz;
        m = (1 - K[u] - E[u]) / m;
        for(i = 0; i < sz; i ++)
        {
            v = e[u][i];
            if(v == f)  continue;
            dfs(v, u);
            sa += A[v];
            sb += B[v];
            sc += C[v];
        }
        A[u] = (K[u] + m * sa) / (1 - m * sb);
        B[u] = m / (1 - m * sb);
        C[u] = (1 - K[u] - E[u] + m * sc) / (1 - m * sb);
    }
//    printf("%d : A = %lf\tB = %lf\tC = %lf\n", u, A[u], B[u], C[u]);
    return;
}

int main()
{
#ifndef ONLINE_JUDGE

    freopen("in.txt","r",stdin);
//    freopen("out-2.txt","w",stdout);

#endif
    int T, i, j, u, v, n, cas;
    scanf("%d", &T);
    for(cas = 1; cas <= T; cas ++)
    {
        scanf("%d", &n);
        for(i = 1; i <= n; i ++)
            e[i].clear();
        for(i = 1; i < n; i ++)
        {
            scanf("%d%d", &u, &v);
            e[u].push_back(v);
            e[v].push_back(u);
        }
        for(i = 1; i <= n; i ++)
        {
            scanf("%lf%lf", K + i, E + i);
            K[i] /= 100;
            E[i] /= 100;
        }

        dfs(1, 0);
        printf("Case %d: ", cas);
        if(fabs(1.0 - A[1])  < eps)
        {
            puts("impossible");
        }else{
            printf("%.6lf\n", C[1] / (1.0 - A[1]));
        }
    }
    return 0;
}
