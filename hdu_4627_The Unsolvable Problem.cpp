#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<cmath>
using namespace std;

int main()
{
    int T;
    long long n, i, j;
    scanf("%d", &T);
    while(T --)
    {
        scanf("%I64d", &n);
        for(i = n / 2; i >= 1; i --)
            if(__gcd(i, n - i) == 1)    break;
        printf("%I64d\n", i * (n - i));
    }
    return 0;
}
