#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
using namespace std;
#define nMax 1010
#define ll long long

ll dp[nMax],l[nMax];
ll m,len;
int next[nMax*2],first[nMax],in[nMax];
int tot,ltot;
struct Edge{
    int v;
    ll w;
}E[nMax*2];
int n;

void dfs(int u,int fa)
{
    int i,v;
    ll w;
    for( i=first[u]; i!=-1; i=next[i] ){
        v = E[i].v;
        if( v == fa )    continue;
        dfs(v,u);
        w = E[i].w > len ? m+1 : E[i].w ;
        dp[u] += min( w, dp[v] );
    }
}

void DP()
{
    dp[1] = 0;
    for(int i=2; i<=n; i++)    if(in[i] == 1)    dp[i] = m+1;    else    dp[i] = 0;
    dfs(1,0);
}

void init()
{
    memset(first,-1,sizeof(first));
    memset(in,0,sizeof(in));
    tot = 0; ltot = 0;
}

void insert(int u,int v,ll w)
{
    E[tot].v = v;    E[tot].w = w;    next[tot] = first[u];    first[u] = tot++;
    E[tot].v = u;     E[tot].w = w;    next[tot] = first[v];    first[v] = tot++;
}

int main()
{
    int u,v,he,ta,mid,i;
    ll w,pre;
    while(~scanf("%d%I64d",&n,&m),n||m){
        init();
        for( i=1; i<n; i++ ){
            scanf("%d%d%I64d",&u,&v,&w);
            l[i]=w;        in[u]++;    in[v]++;
            insert(u,v,w);
        }
        sort(l+1,l+n);
        for(i=1,ltot=0,pre=-1;i<n;i++)    if(  l[i] != pre ){    pre = l[i];    l[ltot++] = l[i];    }
        he=0;    ta=ltot;
        while( he < ta ){
            mid = ( he + ta ) >> 1;
            len = l[mid];
            DP();
            if( dp[1] > m )        he = mid + 1 ;
            else    ta = mid;
        }
        if( he == ltot )    puts("-1");
        else             printf("%I64d\n",l[he]);
    }
    return 0;
}
