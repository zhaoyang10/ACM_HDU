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
#define N  1010
struct Point
{
    double p, pr, pd, ex;
}p[N][N];
int n, m;

bool check(int x, int y)
{
    return (x >= 0 && x < n && y >= 0 && y < m);
}

void dfs(int x, int y)
{
    if( !check(x,y) ) return;
    if(p[x][y].ex > -eps)   return;
    if(fabs(p[x][y].p - 1) < eps)
    {
        p[x][y].ex = 0;
        return;
    }
    dfs(x + 1, y);
    dfs(x, y + 1);
    p[x][y].ex = 0;
    p[x][y].ex += (p[x + 1][y].ex + 2) * p[x][y].pd / (1 - p[x][y].p);
    p[x][y].ex += (p[x][y + 1].ex + 2) * p[x][y].pr / (1 - p[x][y].p);
    p[x][y].ex += 2 * p[x][y].p / (1 - p[x][y].p);
//    printf("p[%d][%d].ex = %lf\n", x, y, p[x][y].ex);
    return;
}

int main()
{
#ifndef ONLINE_JUDGE

    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);

#endif
    int i, j, k, x, y;
    while(~scanf("%d%d", &n, &m))
    {
        for(i = 0; i <= m; i ++)
            p[n][i].ex = 0;
        for(i = 0; i <= n; i ++)
            p[i][m].ex = 0;
        for(i = 0; i < n; i ++)
            for(j = 0; j < m; j ++)
            {
                scanf("%lf%lf%lf",\
                      &p[i][j].p, &p[i][j].pr, &p[i][j].pd);
                p[i][j].ex = -1;
            }
        p[n - 1][m - 1].ex = 0;
        dfs(0,0);
        printf("%.3lf\n",p[0][0].ex);
    }
    return 0;
}
