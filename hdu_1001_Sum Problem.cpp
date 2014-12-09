#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
using namespace std;

int main()
{
    long long n;
    while(scanf("%I64d",&n)!=EOF){
        printf("%I64d\n\n",n*(n+1)/2);
    }
    return 0;
}
