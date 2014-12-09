#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

long long n, m, a, b, c, ans, i, j, k;

long long pow3(long long x)
{
    long long res = (long long)pow(x*1.0, 1.0 / 3.0);
    while(res * res * res > x)  res --;
    while(res * res * res < x)  res ++;
    return res + 1;
}

long long pow2(long long x)
{
    long long res = (long long)sqrt(x * 1.0);
    while(res * res > x)    res --;
    while(res * res < x)    res ++;
    return res + 1;
}

int main()
{
    int cas = 1;
    while(~scanf("%I64d", &n))
    {
        ans = 0;
        a = pow3(n);
        b = pow2(n);
        for(i = 1; i <= a; i ++)
            for(j = i; j <= b; j ++)
            {
                k = n / i / j;
                if(k < j)   break;
                if(i == j)
                    ans += (k - j) * 3 + 1;
                else
                    ans += (k - j) * 6 + 3;
            }

        printf("Case %d: %I64d\n", cas++, ans);
    }
    return 0;
}
