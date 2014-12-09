#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
using namespace std;
#define N 20010
#define ll long long
vector<int>p[N];
int phi[N], sum[N];
ll all, ans[N];
void init()
{
    int i, j;
    for(i = 1; i < N; i ++) p[i].clear();
    for(i = 1; i < N; i ++)
        for(j = i; j < N; j += i)
            p[j].push_back(i);
    for(i = 1; i < N; i ++) phi[i] = i;
    for(i = 2; i < N; i ++)
        if(phi[i] == i)
            for(j = i; j < N; j += i)
                phi[j] -= phi[j] / i;
}
int a[N];
struct Query{
    int l, r, id, d;
    bool operator<(const Query & q)const
    {
        if(d == q.d)    return r < q.r;
        return d < q.d;
    }
}q[N];


void insert(int x)
{
    int i, j, sz = p[a[x]].size();
    for(i = 0; i < sz; i ++)
    {
        j = p[a[x]][i];
        all += 1LL* phi[j] * sum[j];
        sum[j] ++;
    }
}

void del(int x)
{
    int i, j, sz = p[a[x]].size();
    for(i = 0; i < sz; i ++)
    {
        j = p[a[x]][i];
        sum[j] --;
        all -= 1LL * phi[j] * sum[j];
    }
}


int main()
{
    init();
    int T, s, n, i, m, L, R, cas = 1;
    scanf("%d", &T);
    while(T --)
    {
        scanf("%d", &n);    s = (int)sqrt(n);
        for(i = 1; i <= n; i ++)    scanf("%d", a + i);
        memset(sum, 0, sizeof(sum));
        scanf("%d", &m);
        for(i = 1; i <= m; i ++)
        {
            scanf("%d%d", &q[i].l, &q[i].r);
            q[i].d = q[i].l / s;    q[i].id = i;
        }
        sort(q + 1, q + m + 1); all = 0LL;
        for(i = q[1].l; i <= q[1].r; i ++)      insert(i);
        //printf("q[1].id = %d\n", q[1].id);
        ans[q[1].id] = all;
        //printf("ans[%d] = %I64d\n", q[1].id, ans[q[1].id]);
        L = q[1].l; R = q[1].r;
        for(i = 2; i <= m; i ++)
        {
            while(R < q[i].r)   insert(++ R);
            while(L > q[i].l)   insert(-- L);
            while(R > q[i].r)   del(R --);
            while(L < q[i].l)   del(L ++);
            ans[q[i].id] = all;
        }
        printf("Case #%d:\n", cas ++);
        for(i = 1; i <= m; i ++)    printf("%I64d\n", ans[i]);
    }
    return 0;
}
