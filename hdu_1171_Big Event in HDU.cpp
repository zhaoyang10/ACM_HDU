#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define INF 250010
#define N 55
bool a[INF],b[INF];
int v[N],num[N];

int main()
{
    int n,i,j,k,sum,max,tmax,half;
    while(scanf("%d",&n)!=EOF  && n>0){
        for(i=1;i<=n;i++)  scanf("%d%d",&v[i],&num[i]);
        sum=0;
        for(i=1;i<=n;i++)  sum+=v[i]*num[i];
        memset(b,false,sizeof(b));
        memset(a,false,sizeof(a));
        for(i=0;i<=num[1];i++)  a[v[1]*i]=true;
        max=v[1]*num[1];
        for(k=2;k<=n;k++){
            tmax=max;
            for(i=0;i<=max;i++)
                for(j=0;j<=num[k];j++){
                    b[i+j*v[k]]|=a[i];
                   // printf("true=%d\n",i+j*v[k]);
                    if(tmax<i+j*v[k])  tmax=i+j*v[k];
                }
            max=tmax;
            for(i=0;i<=max;i++)  a[i]=b[i];
          //  printf("k=%d\n",k);
         //   for(i=0;i<=max;i++)  if(a[i]) printf("i=%d\n",i);
            memset(b,false,sizeof(b));
        }
        half=sum>>1;
       // printf("half=%d\n",half);
        while(half && !a[half]) half--;
        printf("%d %d\n",sum-half,half);
    }
    return 0;
}
