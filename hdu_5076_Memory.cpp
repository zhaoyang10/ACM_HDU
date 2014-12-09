#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int nMax = 600;
const int oo = 99999999;
const int dd = 1024;
struct Edge{
    int v,flow,nxt;
}edge[nMax*nMax*100];
int g[nMax],nume;
int src,sink;
void init()
{
    memset(g,0,sizeof(g));
    nume = 1;
}
inline void addedge(int u,int v,int flow)
{
    edge[++nume].v = v,edge[nume].flow = flow,edge[nume].nxt = g[u],g[u] = nume;
    edge[++nume].v = u,edge[nume].flow = 0,   edge[nume].nxt = g[v],g[v] = nume;
}
int que[nMax],dist[nMax];
bool dinic_bfs()
{
    memset(dist,63,sizeof(dist));
    dist[src] = 0;
    que[0] = src;
    for(int l = 0,r = 0;l <= r;l++){
        int cur = que[l];
        for(int i = g[cur]; i ;i = edge[i].nxt){
            int v = edge[i].v;
            if( edge[i].flow && dist[v] > dist[cur] + 1 ){
                dist[v] = dist[cur] + 1;
                if( v == sink )
                    return true;
                que[++r] = v;
            }
        }
    }
    return false;
}
int st[nMax],c[nMax],p[nMax];
int dinic_dfs()
{
    int top = 0,ret = 0;
    memcpy(c,g,sizeof(g));
    st[++top] = src;
    while( top ){
        int cur = st[top];
        if( cur != sink ){
            int i;
            for(i = c[cur]; i ;i = edge[i].nxt)
                if( edge[i].flow && dist[edge[i].v] == dist[cur] + 1 )
                    break;
            if( i )
                st[++top] = edge[i].v,c[cur] = p[top] = i;
            else
                --top,dist[cur] = oo;
        }
        else{
            int delta = oo;
            for(int i = top;i >= 2;i--)
                delta = min(delta,edge[p[i]].flow);
            for(int i = top;i >= 2;i--){
                edge[p[i]].flow -= delta;
                edge[p[i]^1].flow += delta;
                if( !edge[p[i]].flow )
                    top = i-1;
            }
            ret += delta;
        }
    }
    return ret;
}
int dinic()
{
    int ret = 0;
    while( dinic_bfs() ){
        ret += dinic_dfs();
    }
    return ret;
}
int w[nMax][nMax],thr[nMax],U[nMax];
int n,m;
int Left[nMax],Right[nMax];
void build()
{
    for(int i = 0;i < 1<<n;i++){
        Left[i] = thr[i]-1;
        for(int j = thr[i]-1;j >= 0;j--){
            if( w[i][j] > w[i][Left[i]] )
                Left[i] = j;
        }
        Right[i] = thr[i];
        for(int j = thr[i];j < 1<<m;j++){
            if( w[i][j] > w[i][Right[i]] )
                Right[i] = j;
        }
    }
    init();
    for(int i = 0;i < 1<<n;i++){
        int num = 0;
        for(int j = 0;j < n;j++){
            if( i&(1<<j) )
                num++;
        }
        if( num%2 ){
            if( Left[i] != -1 )
                addedge(src,i,w[i][Left[i]]+dd);
            addedge(i,sink,w[i][Right[i]]+dd);
        }
        else{
            if( Left[i] != -1 )
                addedge(i,sink,w[i][Left[i]]+dd);
            addedge(src,i,w[i][Right[i]]+dd);
        }
    }
    for(int i = 0;i < 1<<n;i++){
        int num = 0;
        for(int j = 0;j < n;j++){
            if( i&(1<<j) )
                num++;
        }
        for(int j = i+1;j < 1<<n;j++){
            int same = 0;
            for(int k = 0;k < n;k++){
                if( (i&(1<<k)) == (j&(1<<k)) )
                    same++;
            }
            if( same == n-1 ){
                if( num%2 ){
                    addedge(i,j,U[i]^U[j]);
                }
                else{
                    addedge(j,i,U[i]^U[j]);
                }
            }
        }
    }
}
int ans[nMax];
int vis[nMax];
void bfs()
{
    memset(vis,0,sizeof(vis));
    vis[src] = 1;
    que[0] = src;
    for(int l = 0,r = 0;l <= r;l++){
        int cur = que[l];
        for(int i = g[cur]; i ;i = edge[i].nxt){
            int v = edge[i].v;
            if( edge[i].flow && !vis[v] ){
                vis[v] = 1;
                que[++r] = v;
            }
        }
    }
}
int main()
{
    int t;
    //freopen("1.c","r",stdin);
    scanf("%d",&t);
    while( t-- ){
        scanf("%d %d",&n,&m);
        src = (1<<n),sink = (1<<n)+1;
        for(int i = 0;i < 1<<n;i++)
            scanf("%d",&thr[i]);
        for(int i = 0;i < 1<<n;i++)
            scanf("%d",&U[i]);
        for(int i = 0;i < 1<<n;i++)
            for(int j = 0;j < 1<<m;j++)
                scanf("%d",&w[i][j]);
        build();
        dinic();
        bfs();
        for(int i = 0;i < (1<<n);i++){
            int num = 0;
            for(int j = 0;j < n;j++){
                if( i&(1<<j) )
                    num++;
            }
            if( vis[i] ){
                if( num%2 )
                    ans[i] = Left[i];
                else
                    ans[i] = Right[i];
            }
            else{
                if( num%2 )
                    ans[i] = Right[i];
                else
                    ans[i] = Left[i];
            }
        }
        for(int i = 0;i < (1<<n)-1;i++)
            printf("%d ",ans[i]);
        printf("%d\n",ans[(1<<n)-1]);
    }
    return 0;
}
