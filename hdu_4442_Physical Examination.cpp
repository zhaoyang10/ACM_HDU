#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define nMax 100010
const int MOD = 365*24*60*60;
struct Per{
    long long a,b;
}p[nMax];

bool cmp(Per p1,Per p2){
    return p1.a*p2.b<p1.b*p2.a;
}

int main()
{
    long long ans,tot,n,i,j,a,b;
    while(~scanf("%I64d",&n),n){
        for(i=0;i<n;i++)    scanf("%I64d%I64d",&p[i].a,&p[i].b);
        sort(p,p+n,cmp);
        ans = 0;
        for(i=0;i<n;i++){
            ans += ans * p[i].b + p[i].a;    ans %= MOD;
        }
        printf("%I64d\n",ans);
    }
    return 0;
}
