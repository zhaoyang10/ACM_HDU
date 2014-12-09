#include<iostream>
#include<cstdio>
#include<cstring>
#define INF 100

double a[INF],b[INF],fac[INF];
int num[INF];
void init()
{
    memset(fac,0.0,sizeof(fac));
    fac[0]=1;
    for(int i=1;i<=10;i++)  fac[i]=i*fac[i-1];
}

int main()
{
    int i,j,k,n,m;
    init();
    while(scanf("%d%d",&n,&m)!=EOF){
        for(i=1;i<=n;i++)   scanf("%d",&num[i]);
        memset(b,0.0,sizeof(b));
        memset(a,0.0,sizeof(a));
        for(i=0;i<=num[1];i++)  a[i]=1/fac[i];
        for(k=2;k<=n;k++){
            for(i=0;i<=m;i++)
               for(j=0;j<=num[k] && i+j<=m;j++)
                   b[i+j]+=a[i]/fac[j];
            memcpy(a,b,sizeof(b));
            memset(b,0.0,sizeof(b));
            //for(i=1;i<=10;i++)  printf("b[%d]=%lf\n",i,a[i]);
        }
        printf("%.0lf\n",a[m]*fac[m]);
    }
    return 0;
}
