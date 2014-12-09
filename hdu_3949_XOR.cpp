#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
using namespace std;
#define nMax 10010
#define mMax 61
#define ull long long
int n,m,N;
ull a[nMax];

void gauss()
{
    int i,j=0,k;
    for(i=60; i>=0; i--){
        for(k=j; k<n; k++)
            if( (a[k] >> i)&1 )    break;
        if(k<n){
            swap(a[j],a[k]);
            for(k=0; k<n; k++)    if( (a[k] >> i)&1 && k!=j)    a[k] ^= a[j];
            j++;
        }
    }
    N = j;
}

void solve()
{
    int Q,i,j;
    ull q;
    scanf("%d",&Q);
    while(Q--){
        scanf("%I64d",&q);
        if(N < n){
            if(q == 1){    puts("0");    continue;}
            else    q--;
        }
        if( (q>>N) >= 1 )    puts("-1");
        else{
            ull res = 0;
            for(i=0; i<N; i++)    if( (q>>i)&1 )    res ^= a[N-i-1];
            printf("%I64d\n",res);
        }
    }
}

int main()
{
    int T,cas,i,j,k;
    scanf("%d",&T);
    for(cas=1; cas <= T; cas++){
        scanf("%d",&n);
        for(i=0;i<n;i++)    scanf("%I64d",a+i);
        gauss();
        printf("Case #%d:\n",cas);
        solve();
    }
    return 0;
}
