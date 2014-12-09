#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<set>
#include<algorithm>
using namespace std;
int s,t,ss,tt;
//s-源点  t-汇点
#define inf  1<<30
#define MAXN 1100
#define MAXM 210000
#define cc system("pause");
int d[MAXN],first[MAXN],first1[MAXN],q[MAXN],pre[MAXN];
bool full[MAXN];
int tot;
struct edge
{
    int u,v;
    int f,c,id;
    int next;
}e[MAXM];

void insert(int u,int v,int c,int id)
{
    e[tot].u=u;  e[tot].v=v;  e[tot].c=c;  e[tot].f=0;
    e[tot].next=first[u];  e[tot].id = id;  first[u]=tot++;

    e[tot].u=v;  e[tot].v=u;  e[tot].c=0;  e[tot].f=0;
    e[tot].next=first[v];  e[tot].id = id;  first[v]=tot++;
}

bool make_level()
{
    int u,v,ee;
    queue<int>q;
    q.push(s);
    memset(d,0,sizeof(d));
    d[s]=1;
    while(!q.empty()){
         u=q.front(); q.pop();
         for(ee=first[u]; ee!=-1 ;ee=e[ee].next){
             v=e[ee].v;
             if(d[v]==0 && e[ee].c-e[ee].f>0){
                 d[v]=d[u]+1;
                 q.push(v);
                 if(v==t)  return true;
             }
         }
    }
    return false;
}

int dinic()
{
    int top,temp,minf,f=0,i,j,ee;
    top=1;
    for(i=0;i<=t;i++)  first1[i]=first[i];
    memset(full,false,sizeof(full));
    q[top]=s;
    while(top>0){
        if(q[top]==t){
            minf=inf;
            for(i=top;i>=2;i--)    if(e[pre[q[i]]].c-e[pre[q[i]]].f<minf)  minf=e[pre[q[i]]].c-e[pre[q[i]]].f;
            f+=minf;
            for(i=top;i>=2;i--){
                e[pre[q[i]]].f+=minf;
                e[pre[q[i]]^1].f-=minf;
                if(e[pre[q[i]]].f==e[pre[q[i]]].c)   temp=i;
            }
            top=temp-1;
        }else {
            for(ee=first1[q[top]];ee!=-1;ee=e[ee].next)
                if(d[e[ee].v]==d[e[ee].u]+1 && e[ee].c-e[ee].f>0 && !full[e[ee].v]){
                    first1[q[top]]=e[ee].next;
                    q[++top]=e[ee].v;
                    pre[e[ee].v]=ee;
                    break;
                }else continue;
                if(ee==-1)  full[q[top--]]=true;
        }
    }
    return f;
}


int maxflow()
{
    int maxf=0;
    while(make_level())   maxf+=dinic();
    return maxf;
}

void init()
{
    memset(first, -1, sizeof(first));
    s = 0;  tot = 0;
}

void check()
{
    for(int i=0;i<tot;i++)   printf("i=%d\tu=%d\tv=%d\tf=%d\tc=%d\n",i,e[i].u,e[i].v,e[i].f,e[i].c);
    printf("s=%d\tt=%d\n",s,t);
}

set<int>E;
int vis[MAXN];
void dfs(int u, int f)
{
    if(vis[u])  return;
    vis[u] = true;

    int i;
    for(i = first[u]; i != -1; i = e[i].next)
    {
        if(e[i].v == f) continue;
        if(e[i].c == e[i].f)    continue;
        dfs(e[i].v, u);
    }
}

void getEdge()
{
    int i;
    E.clear();
    memset(vis, 0, sizeof(vis));
    dfs(s, 0);
//    for(i = 1; i < t; i ++)
//        if(vis[i])  printf(" -- %d\t", i);
    for(i = 0; i < tot ; i += 2)
        if((vis[e[i].u] && !vis[e[i].v])&& e[i].id != -1)
            E.insert(e[i].id);
}



int main()
{
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    int T, cas, n, m, i, j, u, v, c, f, ans;
    scanf("%d",&T);
//    T = 1;
    for(cas = 1; cas <= T; cas ++)
    {
        scanf("%d%d%d", &n, &m, &f);
        init(); t = n + 1;  s = 1;
        for(i = 1; i <= m; i ++)
        {
            scanf("%d%d%d", &u, &v, &c);
            insert(u, v, c, i);
        }
        ans = 0;
        for(; i <= f + m; i ++)
        {
            scanf("%d%d", &u, &c);
            insert(u, t, c, -1);
            ans += c;
        }
        ans = ans - maxflow();
//        check();
        getEdge();
        printf("Case %d: %d\n%d", cas, ans, E.size());
        for(set<int>::iterator it = E.begin(); it != E.end(); it ++)
        {
            printf(" %d", *it);
        }
        puts("");
    }
    return 0;
}
