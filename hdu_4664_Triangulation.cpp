#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
#define N 110
bool vis[N];
int sg[N];
int a[] = {4,8,1,1,2,0,3,1,1,0,3,3,2,2,4,4,5,5,9,3,3,0,1,1,3,0,2,1,1,0,4,5,3,7};
void init()
{
    int i, j;
    sg[1] = sg[0] = 0;
    for(i = 2; i <= 100; i ++)
    {
        memset(vis, 0, sizeof(vis));
        for(j = 0; j <= i - 2; j ++)
            vis[sg[j]^sg[i - 2 - j]] = true;
        for(j = 0;vis[j]; j ++);
        sg[i] = j;
    }
}

int getsg(int x)
{
    if(x <= 100)    return sg[x];
    return a[x%34];
}

int main()
{
    init();
    int T, n, i, j, ans;
    scanf("%d", &T);
    while(T --)
    {
        scanf("%d", &n);    ans = 0;
        for(i = 1; i <= n; i ++)
        {
            scanf("%d", &j);
            ans ^= getsg(j);
        }
        if(ans) puts("Carol");
        else    puts("Dave");
    }
    return 0;
}
