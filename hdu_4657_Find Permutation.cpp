#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
#define N 100010
int a[N], b[N], c[N], id[N];
int main()
{
    int T, n, i, j, cur, l;
    scanf("%d", &T);
    while(T --)
    {
        scanf("%d", &n);
        for(i = 0; i < n; i ++)    scanf("%d", b + i);
        for(i = 0; i < n; i ++)    a[i] = c[i] = id[i] = i;
        for(i = 0; i < n; i ++)
        {
            l = i;
            while((a[l] + b[l]) % n != c[l])
            {
                j = id[(c[l] - b[l] + n) % n];
                swap(a[l], a[j]);
                swap(id[a[l]], id[a[j]]);
                if(j > i)   break;
                swap(c[j], c[i + 1]);
                l = j;
            }
        }
        for(i = 0; i < n - 1; i ++) printf("%d ", a[i]);    printf("%d\n", a[i]);
        for(i = 0; i < n - 1; i ++) printf("%d ", c[i]);    printf("%d\n", c[i]);
    }
    return 0;
}
