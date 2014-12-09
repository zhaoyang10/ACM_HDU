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
#define i64 long long
const int mod=1000000007;
const int N=11;

int conn[1<<N],disc[1<<N],edge[1<<N];
int bico[1<<N],unco[1<<N],meth[1<<N][1<<N];
int n,m;
int a[N][N];

void cal(int st)
{
    edge[st]=0;
    int i,j,k;
    for(i=0;i<n;i++) if(st&(1<<i)) for(j=i+1;j<n;j++)
    {
        if(st&(1<<j)) edge[st]+=!a[i][j];
    }
    conn[st]=(1LL<<edge[st])%mod;
    int lowbit=st&(-st);
    int rst=st^lowbit;
    if(rst)
    {
        for(i=(rst-1)&rst;;i=(i-1)&rst)
        {
            int nst=i^lowbit;
            conn[st]-=(i64)conn[nst]*((1LL<<edge[st^nst])%mod)%mod;
            conn[st]%=mod;
            if(i==0) break;
        }
    }
    meth[0][st]=1;
    for(i=(st-1)&st;i;i=(i-1)&st)
    {
        i64 tmp=0;
        int lowbit=i&(-i);
        int rst=i^lowbit;
        for(j=rst;;j=(j-1)&rst)
        {
            int k=j^lowbit;
            tmp+=(i64)meth[i^k][st^i]*conn[k]%mod*(edge[st^i^k]-edge[st^i]-edge[k])%mod;
            tmp%=mod;
            if(j==0) break;
        }
        meth[i][st^i]=tmp;
    }
    bico[st]=conn[st];
    if(rst)
    {
        for(i=(rst-1)&rst;;i=(i-1)&rst)
        {
            int nst=i^lowbit;
            bico[st]-=(i64)bico[nst]*meth[st^nst][nst]%mod;
            bico[st]%=mod;
            if(i==0) break;
        }
    }
}

int main()
{

    int T;
    scanf("%d",&T);
    while(T--)
    {
        memset(a, 0, sizeof(a));
        scanf("%d%d",&n,&m);
        int i;
        for(i=1;i<=m;i++)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            u--; v--;
            a[u][v]=a[v][u]=1;
        }
        for(i=0;i<(1<<n);i++)
        {
            cal(i);
        }
        int ans=bico[(1<<n)-1];
        if(ans<0) ans+=mod;
        printf("%d\n",ans);
    }
    return 0;
}
