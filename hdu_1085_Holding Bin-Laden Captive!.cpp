#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
#define INF 10010
int a[INF],b[INF];
int main()
{
    int i,j,k,x,y,z,max;
    while(scanf("%d%d%d",&x,&y,&z)!=EOF && (x|| y || z)){
        max=x+2*y+5*z;
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        for(i=0;i<=x;i++)  a[i]=1;
        for(i=0;i<=x;i++)
           for(j=0;j<=y;j++)
               b[i+j*2]+=a[i];
        memcpy(a,b,sizeof(b));
        memset(b,0,sizeof(b));

       /* for(i=0;i<=x+2*y;i++){
            a[i]=b[i];
            b[i]=0;
        }
        */
        for(i=0;i<=x+2*y;i++)
            for(j=0;j<=z;j++)
                b[i+j*5]+=a[i];
        bool flag=true;
        for(i=0;i<=max;i++)
            if(!b[i]){
                printf("%d\n",i);
                flag=false;
                break;
            }
        if(flag) printf("%d\n",max+1);
    }
    return 0;
}
