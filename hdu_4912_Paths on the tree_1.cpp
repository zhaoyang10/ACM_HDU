#pragma comment(linker, "/STACK:102400000,102400000")
#include"cstdio"
#include"iostream"
#include"set"
#include"queue"
#include"string.h"
using namespace std;
#define N 100010
struct Edge{
    int from, to, nex;
}edge[2*N];
int head[N],edgenum,dis[N],fa[N][20],dep[N];  //fa[i][x] 是i的第2^x个父亲（如果超过范围就是根）
void add(int u,int v){
    Edge E={u,v,head[u]};
    edge[edgenum] = E;
    head[u]=edgenum++;
}
void bfs(int root){
    queue<int> q;
    fa[root][0]=root;dep[root]=0;dis[root]=0;
    q.push(root);
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int i=1;i<20;i++)fa[u][i]=fa[fa[u][i-1]][i-1];
        for(int i=head[u]; ~i;i=edge[i].nex){
            int v=edge[i].to;if(v==fa[u][0])continue;
            dep[v]=dep[u]+1;dis[v]=dis[u]+1;fa[v][0]=u;
            q.push(v);
        }
    }
}
int Lca(int x,int y){
    if(dep[x]<dep[y])swap(x,y);
    for(int i=0;i<20;i++)if((dep[x]-dep[y])&(1<<i))x=fa[x][i];
    if(x==y)return x;
    for(int i=19;i>=0;i--)if(fa[x][i]!=fa[y][i])x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
void init(){memset(head, -1, sizeof head); edgenum = 0;}

int n, m;
struct node{
    int l, r, lca;
}q[N];
bool cmp(node a, node b){
    return dep[a.lca] > dep[b.lca];
}
int vis[N], tim;
int main(){
    int i, j, u, v;
    memset(vis, 0, sizeof vis);
    tim = 1;
    while(~scanf("%d %d",&n,&m)){
        init();
        tim++;
        for(i = 1; i < n; i++)
        {
            scanf("%d %d",&u,&v);
            add(u, v);
            add(v, u);
        }
        bfs(1);
        for(i = 1; i <= m; i++)
        {
            scanf("%d %d",&q[i].l, &q[i].r);
            q[i].lca = Lca(q[i].l, q[i].r);
        }
        sort(q+1, q+1+m, cmp);
        int ans = 0;
        for(i = 1; i <= m; i++)
        {
            int lca = q[i].lca;
            u = q[i].l, v = q[i].r;
            if(vis[lca] == tim)continue;
            bool ok = true;
            if(u == lca)
            {
                while(v!=lca){
                    if(vis[v]==tim){ok = false;break;}
                    v = fa[v][0];
                }
                if(ok)
                {
                    ans++;
                    v = q[i].r;
                    while(v!=lca){
                        vis[v]==tim;
                        v = fa[v][0];
                    }
                    vis[lca] = tim;
                }
            }
            else if(v==lca){
                while(u!=lca){
                    if(vis[u]==tim){ok=false;break;}
                    u = fa[u][0];
                }
                if(ok)
                {
                    ans++;
                    u = q[i].l;
                    while(u!=lca){
                        vis[u]==tim;
                        u = fa[u][0];
                    }
                    vis[lca] = tim;
                }
            }
            else {
                while(v!=lca){
                    if(vis[v]==tim){ok = false;break;}
                    v = fa[v][0];
                }
                if(ok)
                while(u!=lca){
                    if(vis[u]==tim){ok=false;break;}
                    u = fa[u][0];
                }
                if(ok)
                {
                    ans++;
                    u = q[i].l, v = q[i].r;
                    while(v!=lca){
                        vis[v]==tim;
                        v = fa[v][0];
                    }
                    while(u!=lca){
                        vis[u]==tim;
                        u = fa[u][0];
                    }
                    vis[lca] = tim;
                }
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
