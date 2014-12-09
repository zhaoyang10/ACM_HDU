#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#include<set>
#include<queue>
using namespace std;
#define ll long long
#define N 100001

int a[N];
int check(int x, int y)
{
    if(x == 0 && y == 1)    return 0;
    if(x == 0 && y == 2)    return 0;
    if(x == 0 && y == 3)    return 0;


    if(x == 1 && y == 3)    return 0;
    if(x == 2 && y == 3)    return 0;

    if(x == 1 && y == 0)    return 1;
    if(x == 3 && y == 2)    return 1;

    if(x == 2 && y == 0)    return 2;
    if(x == 3 && y == 1)    return 2;

    if(x == 3 && y == 0)    return 3;

    if(x == 1 && y == 2)    return 4;

    if(x == 2 && y == 1)    return 5;

    if(x == 1 && y == 1)    return 1;

    if(x == y)              return -1;

    if(abs(x - y) <= 3)     return 0;


    return -1;

}

int main()
{
    //freopen("in.txt", "r", stdin);
    int T, cas, i, j, n, t1, t2, now, pre, type, ans;
    scanf("%d", &T);
    for(cas = 1; cas <= T; cas ++)
    {
        scanf("%d", &n);
        for(i = 1; i <= n; i ++)
            scanf("%d", a + i);
        ans = 1;
        bool flag = true;
        for(i = 2; i <= n; i ++)
        {

            type = check(a[i - 1], a[i]);
            if(type >= 4)
            {
                ans ++;
            }else if(type == -1)
            {
                //printf("a[%d] = %d\ta[%d] = %d\n", i - 1, a[i - 1], i, a[i]);
                flag = false;
                break;
            }
        }
        if(a[n] != 0)   ans *= 2;
        if(!flag)   ans = 0;
        if(a[1] > 3)    ans = 0;

        printf("Case #%d: %d\n",cas, ans);
    }
    return 0;
}
