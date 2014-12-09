#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
using namespace std;
#define ll long long
#define nMax 100010
#define kMax 15
int K,n,tot;
ll dp[nMax][kMax];
int next[nMax*2],first[nMax];
struct Edge{
    int v;
    ll w;
}E[nMax*2];

void insert(int u,int v,ll w)
{
    E[tot].v = v;        E[tot].w = w;    next[tot] = first[u];        first[u] = tot ++;
    E[tot].v = u;         E[tot].w = w;    next[tot] = first[v];        first[v] = tot ++;
}

void init()
{
    int i,j,k;
    tot = 0;

    for( i=0; i<=n; i++ ){
        first[i] = -1;
        for( j=0; j<=K; j++ )
            dp[i][j] = 0;
    }
}

void dfs(int u,int fa)
{
    int i,j,k,v;
    ll w;
    for( i=first[u]; i!=-1; i=next[i] ){
        v = E[i].v;
        if( v == fa )    continue;
        w = E[i].w;
        dfs( v, u );
        for( j = K; j >= 0; j-- ){
            dp[u][j] += dp[v][0]+ 2*w;
            for( k = 0; k <= j; k++ )
                dp[u][j] = min ( dp[u][j], dp[u][j-k] + k * w + dp[v][k] );
        }
    }
}

int main()
{
    int i,u,v,S;
    ll w;
    while(~scanf("%d%d%d",&n,&S,&K)){
        init();
        for( i=1; i<n; i++ ){
            scanf("%d%d%I64d",&u,&v,&w);
            insert(u,v,w);
        }
        dfs(S,0);
        printf("%I64d\n",dp[S][K]);
    }
    return 0;
}
