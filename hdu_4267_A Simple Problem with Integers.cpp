#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int nMax = 50001;

int s[10][10][nMax*3+1];
int n;
void M(int *a,int x,int y)
{
    while(x){
        a[x]+=y;
        x-=(x&(-x));
    }
}

void change()
{
    int a,b,k,c,he,ta,y;
    scanf("%d%d%d%d",&a,&b,&k,&c);
    y=a%k;    he=a/k+1;    ta=b/k+1;
    if( b%k < a%k )    ta--;
    M(s[k-1][y],ta,c);    M(s[k-1][y],he-1,-c);
}

int G(int *a,int x)
{
    int res=0;
    while(x<n*3){
        res+=a[x];
        x+=(x&(-x));
    }
    return res;
}


int main()
{
    int m,i,j,k,kind,a,pl;
    while(scanf("%d",&n)!=EOF){
        for(i=0;i<=9;i++)
            for(j=0;j<=i;j++)
                for(k=0;k<n*3;k++)
                    s[i][j][k]=0;
                
        for(i=1;i<=n;i++){    
            scanf("%d",&a);
            M(s[0][0],i+1,a);
            M(s[0][0],i,-a);
        }
        scanf("%d",&m);
        while(m--){
            scanf("%d",&kind);
            if(kind==1)    change();
            else{
                pl=0;
                scanf("%d",&a);
                for(i=1;i<=10;i++)    pl+=G(s[i-1][a%i],a/i+1);
                printf("%d\n",pl);
            }
        }
    }
    return 0;
}
