#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<map>
#include<vector>
using namespace std;
const int nMax = 3010;
const int MAX = 100000000;

map< pair< int , int >,int >mp;
vector<int>E[nMax];


bool vis[nMax];
int a[nMax][nMax],f[nMax][nMax];
int d[nMax],pre[nMax];
int n,ans,tans;
void init()
{
    int i,j;
    ans=0;    tans=0;
    memset(vis,0,sizeof(vis));
    memset(pre,-1,sizeof(pre));
    for(i=0;i<n;i++){
        for(j=0;j<n;j++)
            f[i][j]=a[i][j]=MAX;
        d[i]=MAX;    E[i].clear();
    }
    mp.clear();
}

void prim()
{
    int s,mark=-1,t,Min;    s=0;
    vis[s]=true;    d[s]=0;    Min=MAX;
    while(1){
        for(t=1;t<n;t++){
            if(d[t]>f[s][t]){    d[t]=f[s][t];    pre[t]=s;}
            if(d[t]<Min && !vis[t]){
                Min=d[t];    mark=t;
            }
        }
        if(mark==-1)    break;
        ans+=Min;    t=mark;
        vis[t]=true;    f[t][pre[t]]=f[pre[t]][t]=MAX;
        E[t].push_back(pre[t]);        E[pre[t]].push_back(t);
        s=t;    mark=-1;    Min=MAX;
    }
}

int dfs1(int u,int fa,int rt)
{
    int i,sz,v;
    for(i=0,sz=E[u].size();i<sz;i++){
        v=E[u][i];
        if(v==fa)    continue;
        f[rt][u] = min( f[rt][u] , dfs1( v, u, rt ) );
    }
    return f[rt][u];
}

int dfs2(int u,int fa,int rt)
{
    int i,sz,v,tmp;
    tmp=f[u][rt];
    for(i=0,sz=E[u].size();i<sz;i++){
        v=E[u][i];
        if(v==fa)    continue;
        tmp = min ( tmp, dfs2( v,u,rt ) );
    }
    return tmp;
}

int main()
{
    int m,q,u,v,w,i,j,k,sz,tmp;
    while(~scanf("%d%d",&n,&m) && (n||m)){
        init();
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            a[u][v]=a[v][u]=f[u][v]=f[v][u]=w;
        }
        prim();
        for(i=0;i<n;i++)    dfs1(i,-1,i);
        for(i=0;i<n;i++)
            for(j=0,sz=E[i].size();j<sz;j++){
                tmp=dfs2(E[i][j],i,i);
                mp[make_pair(E[i][j],i)]=tmp;
    //            printf("%d %d:%d\n",E[i][j],i,tmp);
            }
        scanf("%d",&q);
        m=q;
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            if( mp.count( make_pair( u , v ) ) )    tans+=min(mp[make_pair(u,v)],w)-a[u][v];
        }
//        printf("ans=%d\ttans=%d\n",ans,tans);

        printf("%.4lf\n",ans+tans*1.0/q);
    }
    return 0;
}
