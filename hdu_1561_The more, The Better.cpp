#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<vector>
using namespace std;
#define nMax 210
vector<int>E[nMax];
int dp[nMax][nMax];
int n,m;
int c[nMax];
void dfs(int u){
    int i,sz = E[u].size(),j,k,v;
    for( i=0; i<sz; i++ ){
        v = E[u][i];
        dfs(v);
        for( j=m; j>=0; j-- )
            for( k=j; k>=0; k-- )
                dp[u][j] = max ( dp[u][j], dp[u][k] + dp[v][j-k] );
    }
    for( i=m+1; i>0; i-- )    dp[u][i] = dp[u][i-1] + c[u];
}

void init()
{
    memset(dp,0,sizeof(dp));
    for(int i=0; i<=n; i++)    E[i].clear();
    memset(c,0,sizeof(c));
}

int main()
{
    int i,j,k,u;
    while(~scanf("%d%d",&n,&m),n||m){
        init();
        for( i=1; i<=n; i++ ){
            scanf("%d%d",&u,&c[i]);
            E[u].push_back(i);
        }
        dfs(0);
        printf("%d\n",dp[0][m+1]);
    }
    return 0;
}
