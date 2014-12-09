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
#define NN 1010
int fa[N], first[N], ff[N], mp[N];
int n, m, tot;
double x[N];
double a[NN][NN];
bool vis[N];

struct Edge{
    int u, v;
}E[N * 4];

void init()
{
    int i, j;   tot = 0;
    for(i = 1; i <= n; i ++)    fa[i] = i, ff[i] = i;
    memset(first, -1, sizeof(first));
    memset(vis, 0, sizeof(vis));
}

int getfa(int a){   return fa[a] == a ? a : fa[a] = getfa(fa[a]);}
int getff(int a){   return ff[a] == a ? a : ff[a] = getff(ff[a]);}

void combine(int a, int b)
{
    int f1, f2;
    f1 = getfa(a);
    f2 = getfa(b);
    fa[f1] = f2;
}

void combineff(int a, int b)
{
    int f1, f2;
    f1 = getff(a);
    f2 = getff(b);
    ff[f1] = f2;
}

void gauss(int val, int col)
{
    int equ = val + 2;
    int i, j, k, maxRow;
    double m1, m2;
    for(i = 1; i <= val; i ++)
    {
        maxRow = i;
        for(j = i + 1; j <= equ; j ++)
            if(fabs(a[maxRow][i]) -  fabs(a[j][i]) < -eps)
                maxRow = j;
        if(fabs(a[maxRow][i]) < eps)    continue;
        for(j = i; j <= col; j ++)
            swap(a[maxRow][j], a[i][j]);
        for(j = i + 1; j <= equ; j ++)
            if(fabs(a[j][i]) > eps)
            {
                for(k = col; k >i; k --)
                    a[j][k] -= a[j][i] * a[i][k] / a[i][i];
                a[j][i] = 0;
            }
    }
    for(i = val; i >= 1; i --)
    {
        for(j = val; j > i; j --)
        {
            a[i][col] -= x[j] * a[i][j];
        }
        x[i] = a[i][col] / a[i][i];
      //  printf("x[%d] = %lf\n", i, x[i]);
    }
}

int main()
{
#ifndef ONLINE_JUDGE

    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);

#endif
    int s, t, type, u, v, tot1, T, i, j;
    scanf("%d", &T);
    while(T --)
    {
        scanf("%d%d%d%d", &n, &m, &s, &t);
        init();
        while(m --)
        {
            scanf("%d%d%d", &u, &v, &type);
            if(type)
            {
                tot ++;
                E[tot].u = u;
                E[tot].v = v;

            }else{
                combine(u,v);
            }
            combineff(u,v);
        }

    //    puts("over!");


        if(getff(s) != getff(t))
        {
            puts("inf");
            continue;
        }
        s = getfa(s);   t = getfa(t);
        if(s == t)
        {
            puts("0.000000");
            continue;
        }
      //  puts("mp");
        memset(mp, -1, sizeof(mp));
        int tt, F = getff(s);   tot1 = 0;
        for(i = 1; i <= n; i ++)
        {
            //printf("fa[%d] = %d\n", i, getfa(i));
            if(F != getff(i))   continue;
            tt = getfa(i);
            if(mp[tt] == -1)
            {
                mp[tt] = ++tot1;
            }
        }
      //  puts("aa");
        memset(a, 0, sizeof(a));
        for(i = 1; i <= tot; i ++)
        {
            u = E[i].u; v = E[i].v;
            if(F != getff(u) || F != getff(v))  continue;
            u = getfa(u); u = mp[u];
            v = getfa(v); v = mp[v];
            a[u][u] += 1.0; a[u][v] += -1.0;
            a[v][u] += -1.0;    a[v][v] += 1.0;
        }
        for(i = 1; i <= tot1; i ++)     a[tot1 + 1][i] = 0, a[ mp[s] ][i] =0, a[ mp[t] ][i] = 0;
        a[tot1 + 1][ mp[s] ] = 1;       a[tot1 + 1][tot1 + 1] = 1;
        a[tot1 + 2][ mp[t] ] = 1;       a[tot1 + 2][tot1 + 1] = 0;

        //
 /*           puts("begin");
            for(i = 1; i <= tot1 + 2; i ++)
            {
                for(j = 1; j <= tot1 + 1; j ++)
                    printf("%.2lf\t", a[i][j]);
                puts("");
            }
            puts("end");
*/
        //

        gauss(tot1, tot1 + 1);
        memset(vis, 0, sizeof(vis));
        double ans = 0.0;
        s = mp[s];
        for(i = 1; i <= tot; i ++)
        {
            u = E[i].u; v = E[i].v;
            u = getfa(u);   v = getfa(v);
            u = mp[u];  v = mp[v];
          //  printf("u = %d\tv = %d\n", u, v);
            if(u == mp[t] && v != mp[t] && v != -1 )
            {
                ans += x[v];
                vis[v] = true;
               // printf("x[%d] = %lf\n", v, x[v]);
            }else if(u != mp[t] && v == mp[t] && u != -1)
            {
                ans += x[u];
                vis[u] = true;
            //    printf("x[%d] = %lf\n", u, x[u]);
            }
        }
        ans = 1.0 / ans;
        printf("%.6lf\n", ans);
    }
    return 0;
}
