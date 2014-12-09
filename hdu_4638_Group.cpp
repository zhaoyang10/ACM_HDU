#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
#define N 100010

struct Q{
    int l, r, id, d;
    bool operator<(const Q & q)const
    {
        if(d == q.d)    return r < q.r;
        return d < q.d;
    }
}q[N];

int ans[N], res, a[N];
bool vis[N];
void insert(int x)
{
    if(!vis[a[x] - 1] && !vis[a[x] + 1])  res ++;
    if(vis[a[x] - 1] && vis[a[x] + 1])    res --;
    vis[a[x]] = true;
}
void del(int x)
{
    if(!vis[a[x] - 1] && !vis[a[x] + 1])  res --;
    if(vis[a[x] - 1] && vis[a[x] + 1])    res ++;
    vis[a[x]] = false;
}

int main()
{
    int T, n, m, i, s, L, R;
    scanf("%d", &T);
    while(T --)
    {
        scanf("%d%d", &n, &m);
        memset(vis, 0, sizeof(vis));
        for(i = 1; i <= n; i ++)    scanf("%d", a + i);
        s = (int)sqrt(n);
        for(i = 1; i <= m; i ++)
        {
            scanf("%d%d", &q[i].l, &q[i].r);
            q[i].d = q[i].l / s;    q[i].id = i;
        }
        sort(q + 1, q + m + 1);
        res = 0;
        for(i = q[1].l; i <= q[1].r; i ++)
            insert(i);
        ans[q[1].id] = res;
        L = q[1].l; R = q[1].r;
        for(i = 2; i <= m; i ++)
        {
            while(R < q[i].r)   insert(++ R);
            while(L > q[i].l)   insert(-- L);
            while(R > q[i].r)   del(R --);
            while(L < q[i].l)   del(L ++);
            ans[q[i].id] = res;
        }
        for(i = 1; i <= m; i ++)    printf("%d\n", ans[i]);
    }
    return 0;
}
