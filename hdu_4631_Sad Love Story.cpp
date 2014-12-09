#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<set>
using namespace std;
#define N 1000010
#define Max 1LL<<60
#define ll long long

set<int>sx, sy[N];
set<int>::iterator ix, iy, jx, jy;
int main()
{
    int T, n, i;
    ll ax, ay, az, cx, cy, cz;
    scanf("%d", &T);
    while(T --)
    {
        scanf("%d%I64d%I64d%I64d%I64d%I64d%I64d", &n, &ax, &ay, &az, &cx, &cy, &cz);
        ll ans = 0,  m = Max, dx, dy, d, x = 0, y = 0;
        x = (x * ax + ay) % az; y = (y * cx + cy) % cz;
        sx.clear();  sx.insert(x);
        for(i = 0; i < az; i ++)    sy[i].clear();  sy[x].insert(y);
        for(i = 2; i <= n; i ++)
        {
            x = (x * ax + ay) % az; y = (y * cx + cy) % cz;
            jx = sx.lower_bound(x);
            for(ix = jx; ix != sx.end(); ix ++)
            {
                dx = ((*ix) - x) * ((*ix) - x);
                if(dx >= m)  break;
                jy = sy[(*ix)].lower_bound(y);
                if(jy != sy[(*ix)].end())
                {
                    dy = ((*jy) - y) * ((*jy) - y);
                    d = dx + dy;
                    if(d < m)   m = d;
                }
                if(jy != sy[(*ix)].begin())
                {
                    jy --;
                    dy = ((*jy) - y) * ((*jy) - y);
                    d = dx + dy;
                    if(d < m)   m = d;
                }
            }
            if(jx != sx.begin())
            {
                while(1)
                {
                    jx--;
                    dx = ((*jx) - x) * ((*jx) - x);
                    if(dx >= m) break;
                    jy = sy[(*jx)].lower_bound(y);
                    if(jy != sy[(*jx)].end())
                    {
                        dy = ((*jy) - y) * ((*jy) - y);
                        d = dx + dy;
                        if(d < m)   m = d;
                    }
                    if(jy != sy[(*jx)].begin())
                    {
                        jy --;
                        dy = ((*jy) - y) * ((*jy) - y);
                        d = dx + dy;
                        if(d < m)   m = d;
                    }
                    if(jx == sx.begin())    break;
                }
            }
            ans += m;
            sx.insert(x);   sy[x].insert(y);
        }
        printf("%I64d\n", ans);
    }
    return 0;
}
