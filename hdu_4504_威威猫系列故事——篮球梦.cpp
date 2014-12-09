#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<map>
#include<vector>
#include<queue>
#include<cmath>
using namespace std;
#define int long long
const int N = 25;
int dp[2][N*3];
int A,B,T,a,b;

main()
{
    while(~scanf("%I64d%I64d%I64d",&A,&B,&T)){
        T /= 15;
        b = T/2;
        a = T/2 + T%2;
        A = B + b - A;
        A = max(A+1,0ll);
        int m=3,k=1,kk,i,j;
        memset(dp,0,sizeof(dp));
        dp[0][0] = 1;
        for(j=1; j<=a; j++,k^=1,m+=3){
            kk = k^1;
            memset(dp[k],0,sizeof(dp[k]));
            for(i=1; i<=m; i++){
                dp[k][i] += dp[kk][i-1];
                if(i >= 2)  dp[k][i] += dp[kk][i-2];
                if(i >= 3)  dp[k][i] += dp[kk][i-3];
            }
        }
        k^=1;
        int ans=0;
        for(i=A; i<=m; i++)   ans+=dp[k][i];
        printf("%I64d\n",ans);
    }
    return 0;
}
