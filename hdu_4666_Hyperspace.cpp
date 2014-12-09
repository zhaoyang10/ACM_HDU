#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<set>
#include<map>
using namespace std;
multiset<int>ms[20];
map<int,int>mm[20];
multiset<int>::iterator h, t;
int d[10];
int main()
{
    int n, m, sum, a, b, i, j, k, ans, st, op;
    while(~scanf("%d%d", &n, &m))
    {
        st = 1 << (m - 1);
        for(i = 0; i < st; i ++)
        {
            ms[i].clear();
            mm[i].clear();
        }
        for(i = 1; i <= n; i ++)
        {
            scanf("%d", &op);
            if(op)
            {
                scanf("%d", &a);
                for(j = 0; j < st; j ++)
                {
                    ms[j].erase(ms[j].find(mm[j][a]));
                    mm[j].erase(a);
                }
            }else{
                for(j = 0; j < m; j ++)
                    scanf("%d", d + j);
                for(j = 0; j < m; j ++)
                for(k = 0; k < st; k ++)
                {
                    sum = d[0];
                    for(j = 1; j < m; j ++)
                        if(k & (1 << (j - 1)))
                            sum += d[j];
                        else
                            sum -= d[j];
                    ms[k].insert(sum);
                    mm[k][i] = sum;
                }
            }
            ans = 0;
            for(j = 0; j < st; j ++)
            {
                h = ms[j].begin();
                t = ms[j].end();
                t --;
                ans = max(*t - *h, ans);
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}
