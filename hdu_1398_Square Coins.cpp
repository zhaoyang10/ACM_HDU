#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
#define max  300
int a[max+10],b[max+10];

int main()
{
    int n,i,j,k;
    for(i=0;i<=max;i++) a[i]=1;
        memset(b,0,sizeof(b));
        for(k=2;k<=17;k++){
            for(i=0;i<=max;i++)
                for(j=0;i+j<=max;j+=k*k)
                    b[i+j]+=a[i];
            memcpy(a,b,sizeof(b));
            memset(b,0,sizeof(b));
        }
    while(scanf("%d",&n)!=EOF && n)    printf("%d\n",a[n]);
    return 0;
}
