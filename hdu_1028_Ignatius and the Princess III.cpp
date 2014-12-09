#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
#define max 120
int a[max+10],b[max+10];


void init()
{
    int i,j,k;
    memset(b,0,sizeof(b));
    for(i=0;i<=max;i++) a[i]=1;
    for(k=2;k<=max;k++){
        for(i=0;i<=max;i++)
            for(j=0;i+j<=max;j+=k)
                b[i+j]+=a[i];
        memcpy(a,b,sizeof(b));
        memset(b,0,sizeof(b));
    }
}

int main()
{
    int n;
    init();
    while(scanf("%d",&n)!=EOF) printf("%d\n",a[n]);
    return 0;
}
