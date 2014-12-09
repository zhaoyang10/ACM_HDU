#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
#define max 50
int a[max+10],b[max+10],num[30];
int main()
{
    int T,i,j,k;
    scanf("%d",&T);
    while(T--){
        for(i=1;i<=26;i++)  scanf("%d",&num[i]);
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        for(i=0;i<=num[1];i++)  a[i]=1;
        for(k=2;k<=26;k++){
            for(i=0;i<=max;i++)
                for(j=0;j<=num[k] && i+j*k<=max;j++)
                    b[i+j*k]+=a[i];
            memcpy(a,b,sizeof(b));
            memset(b,0,sizeof(b));
        }
        int ans=0;
       // for(i=1;i<=max;i++)  printf("a[%d]=%d\n",i,a[i]);
        for(i=1;i<=max;i++)   ans+=a[i];
        printf("%d\n",ans);
    }
    return 0;
}
