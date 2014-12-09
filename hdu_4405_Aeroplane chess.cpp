#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
const double eps = 1e-8;
const int nMax = 100100;
const int mMax = 1010;
double  dp[nMax];
int n,tot;
int first[nMax];
struct Edge{
    int v,nxt;
}e[mMax];

double dfs(int x)
{
    if(x>=n)    return 1.0;
    if(first[x]!=-1)    return dfs(e[first[x]].v);
    if(dp[x]>eps)    return dp[x];
    double res=0.0;
    for(int i=1;i<=6;i++)    res+=dfs(x+i);
    return ( dp[x]= ( ( res / 6.0 ) + 1 ) );
}

void insert(int u,int v)
{
    e[tot].v=v;    e[tot].nxt=first[u];    first[u]=tot++;
}

int main()
{
    int m,i,j,k,u,v;
    while(scanf("%d%d",&n,&m)!=EOF){
        if(n==0  &&  m==0)    break;
        memset(dp,0,sizeof(dp));
        memset(first,-1,sizeof(first));
        tot=0;
        while(m--){
            scanf("%d%d",&u,&v);
            insert(u,v);
        }
        printf("%.4lf\n",dfs(0)-1);
    }
    return 0;
}
