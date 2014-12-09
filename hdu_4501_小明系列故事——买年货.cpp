#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<map>
#include<vector>
#include<queue>
#include<cmath>
using namespace std;
#define ll long long
const int N = 110;
const int K = 10;

int dp[N][N][K];
int c1[N],c2[N],vv[N];

int n,v1,v2,k;



int main()
{
    int i,j,g,ans,tn,tk;
    while(scanf("%d%d%d%d",&n,&v1,&v2,&k) != EOF){
        for(i=1; i<=n; i++) scanf("%d%d%d",c1+i,c2+i,vv+i);
        for(i=0; i<=v1; i++)
            for(j=0; j<=v2; j++)
                for(tk=0; tk<=k; tk++)
                    dp[i][j][tk] = -1;
        dp[v1][v2][k] = 0;
        ans=0;
        for(i=1; i<=n; i++)
            if(c1[i] == 0 || c2[i] == 0){
                dp[v1][v2][k] += vv[i];
                c1[i]=c1[n];
                c2[i]=c2[n];
                vv[i]=vv[n];
                n--;
                i--;
            }
        c1[0] = c2[0] = vv[0] = 0;
        for(tn = 0; tn <= n; tn++)
        for(i = 0; i <= v1; i++)
        for(j = 0; j <= v2; j++)
        for(tk = 0; tk <=k; tk++){
            if(tk < k && dp[i][j][tk+1] != -1 && dp[i][j][tk] < dp[i][j][tk+1] + vv[tn])
                dp[i][j][tk] = dp[i][j][tk+1]  + vv[tn];
            if(i + c1[tn] <= v1 && dp[i+c1[tn]][j][tk] != -1 && dp[i][j][tk] < dp[i+c1[tn]][j][tk] + vv[tn])
                dp[i][j][tk] = dp[i+c1[tn]][j][tk] + vv[tn];
            if(j + c2[tn] <= v2 && dp[i][j+c2[tn]][tk] != -1 && dp[i][j][tk] < dp[i][j+c2[tn]][tk] + vv[tn])
                dp[i][j][tk] = dp[i][j+c2[tn]][tk] + vv[tn];
            if(dp[i][j][tk] > ans)  ans = dp[i][j][tk];
          //  printf("dp[%d][%d][%d] = %d\tans = %d\n",i,j,tk,dp[i][j][tk],ans);
        }
        printf("%d\n",ans);
    }
    return 0;
}
