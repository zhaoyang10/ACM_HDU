#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<set>
#include<map>
#include<cmath>
using namespace std;
#define eps 1e-8
#define ll long long
#define ull unsigned long long
#define MOD 1000000007
#define N 100010
vector<int>e[N];
int num[N],fa[N],idx[N],dep[N],top[N],son[N],first[N],left1[N],right1[N],sum[N];
int tot,n,ans;
int dp[N*5][30],node[N*5],p[30];

struct Edge
{
    int u,v,d,r;
    bool operator<(const Edge& E)const
    {
        return d > E.d;
    }
}E[N];

void dfs(int u,int ufa,int depth)
{
    dep[u] = depth;
    idx[++tot]=u;
    first[u]=tot;
    int v,i,sz=e[u].size();
    for(i=0; i<sz; i++)
    {
        v=e[u][i];
        if(v==ufa)  continue;
        dfs(v,u,depth+1);
        idx[++tot]=u;
    }
    idx[++tot]=u;
}

void RMQ()
{
    int i,j,nn,k,r,len=0;
    nn = tot;
    nn >>= 1;
    while(nn)
    {
        nn>>=1;
        len++;
    }
    p[0]=1;
    for(i=1; p[i-1]<=tot; i++)  p[i]=2*p[i-1];

    for(i=1; i<=tot; i++)   dp[i][0]=idx[i];
/*
    for(i=1; i<=tot; i++)
    {
        printf("dp[%d][0] = %d\n",i,dp[i][0]);
    }
*/
    for(j=1; j<=len; j++)
    {
        for(i=1; i<=tot; i++)
        {
            r = i + p[j-1];
            //printf("l = %d\tr = =%d\tp[%d] = %d\n",i,r,i,p[i])
            if(r > tot) dp[i][j]=dp[i][j-1];
            else
            {
                if( dep[ dp[i][j-1] ] < dep[ dp[r][j-1] ] )
                {
                    dp[i][j] = dp[i][j-1];
                }
                else
                {
                    dp[i][j] = dp[r][j-1];
                }
            }
//            printf("dp[%d][%d] = %d\n",i,j,dp[i][j]);
        }
    }
}

int REQ(int u,int v)
{
    int i,j,l,r,k,len;
    u = first[u];
    v = first[v];
    if(u>v) swap(u,v);
    len = v - u + 1;
    k=0;
    len>>=1;
    while(len)
    {
        len>>=1;
        k++;
    }
    l = v - p[k] + 1;
    if(dep[dp[u][k]] < dep[dp[l][k]])   return dp[u][k];
    return dp[l][k];
}

void dfs2(int u,int ufa)
{
    left1[u] = ++tot;
    int i,sz=e[u].size(),v;
    for(i=0; i<sz; i++)
    {
        v=e[u][i];
        if(v==ufa)  continue;
        dfs2(v,u);
    }
    right1[u] = tot;
}


void init_tree()
{
    memset(sum,0,sizeof(sum));
}

inline void add(int x,int a)
{
    while(x)
    {
        sum[x]+=a;
        x -= x&(-x);
    }
}

inline int get(int x)
{
    int res = 0;
//    printf("x = %d\tn = %d\n",x,n);
    while(x<=n)
    {
//        printf("sum[%d] = %d\n",x,sum[x]);
        res += sum[x];
        x += x&(-x);
//        printf("res = %d\n",res);
    }
    return res;
}

inline void insert(int x)
{
    int l = left1[E[x].r];
    int r = right1[E[x].r];
    add(r,1);
    add(l-1,-1);
}

bool check(int x)
{
    int i,j,k,u=E[x].u,v=E[x].v,r=E[x].r;
    int t1,t2,t3;
    t1 = get(left1[u]);
    t2 = get(left1[v]);
    t3 = get(left1[r]);
/*
    printf("left1[%d] = %d\tsum = %d\n",u,left1[u],t1);
    printf("left1[%d] = %d\tsum = %d\n",v,left1[v],t2);
    printf("left1[%d] = %d\tsum = %d\n",r,left1[r],t3);
*/
    if( t1 || t2 || t3)  return false;
    return true;
}

int main()
{
    int m,i,j,u,v;
    while(~scanf("%d%d",&n,&m))
    {
        for(i=1; i<=n; i++) e[i].clear();
        for(i=1; i<n; i++)
        {
            scanf("%d%d",&u,&v);
            e[u].push_back(v);
            e[v].push_back(u);
        }
        tot=0;
        dfs(1,1,1);
        RMQ();
        for(i=1; i<=m; i++)
        {
            scanf("%d%d",&E[i].u,&E[i].v);

            E[i].r = REQ(E[i].u,E[i].v);
            E[i].d = dep[E[i].r];

        }

        sort(E+1,E+m+1);
        tot=0;
        dfs2(1,1);

        init_tree();
        ans = 0;
        for(i=1; i<=m; i++)
        {
            if(check(i))
            {
                insert(i);
                ans++;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
