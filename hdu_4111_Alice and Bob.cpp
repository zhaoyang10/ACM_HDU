#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
using namespace std;

const int nMax = 55;
const int mMax = 55000;
int dp[nMax][mMax];
int a[nMax];

int dfs(int x,int y)
{
    if(dp[x][y]!=-1)    return dp[x][y];
    if(y==1)    return dp[x][1]=dfs(x+1,0);
    dp[x][y]=0;
    if(x>=1 && !dfs(x-1,y))        dp[x][y]=1;
    if(x>=1 && y && !dfs(x-1,y+1))    dp[x][y]=1;
    if(x>=2 &&    ( (y&&!dfs(x-2,y+3)) || (y==0 && !dfs(x-2,2)) ) )    dp[x][y]=1;
    if(y>=2 && !dfs(x,y-1))        dp[x][y]=1;
    return dp[x][y];
}

int main()
{
    memset(dp,-1,sizeof(dp));
    dp[0][0]=0;
    int T,n,i,j,k,ca,x,y;
    scanf("%d",&T);
    for(ca=1;ca<=T;ca++){
        scanf("%d",&n);
        x=0,y=0;
        for(i=1;i<=n;i++){
            scanf("%d",a+i);
            if(a[i]==1)    x++;
            else y+=a[i]+1;
        }
        if(y)    y--;
        dfs(x,y);
        printf("Case #%d: ",ca);
        if(dp[x][y])    printf("Alice\n");
        else             printf("Bob\n");
    }
    return 0;
}
