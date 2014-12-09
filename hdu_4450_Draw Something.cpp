#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<cmath>
using namespace std;

int main()
{
    int i,n;
    long long a,ans;
    while(~scanf("%d",&n),n){
        ans = 0;
        for( i=1; i<=n; i++ ){    scanf("%I64d",&a);    ans += a*a;}
        printf("%I64d\n",ans);
    }
    return 0;
}
