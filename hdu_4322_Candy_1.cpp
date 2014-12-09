#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
#define sz 15005
#define inf 0x7fffffff
struct node{
    int s, t, v, len, nxt;
} e[sz * 40 + 20];
int hd[sz], cnt, pre[sz] , pos[sz], dis[sz], vis[sz];
void insert(int s, int t, int v, int len){
    e[cnt].s = s;e[cnt].t = t;e[cnt].v = v;e[cnt].len = len;
    e[cnt].nxt = hd[s];hd[s] = cnt++;
    e[cnt].s = t;e[cnt].t = s;e[cnt].v = 0;e[cnt].len = -len;
    e[cnt].nxt = hd[t];hd[t] = cnt++;
}
bool spfa(int s, int t, int n){
    for(int i = 0; i < n; i++){
        dis[i]=inf;
        vis[i]=0;
        pre[i]=-1;
    }
    queue<int>q;
    while(!q.empty())q.pop();
    q.push(s);
    pre[s] = s;
    dis[s] = 0;
    while( !q.empty() ){
        int u = q.front();
        q.pop();
        vis[u] = 0;
        for(int i = hd[u]; i!=-1; i=e[i].nxt){
            int v = e[i].t;
            if (e[i].v > 0 && dis[u] + e[i].len < dis[v]){
                dis[v] = dis[u] + e[i].len;
                pre[v] = u;
                pos[v] = i;
                if (!vis[v]){
                    vis[v] = 1;
                    q.push(v);
                }
            }
        }
    }
    return pre[t] != -1 && dis[t] < inf;
}
int mcf(int s, int t, int n){
    int fw = 0, ct = 0;
    while(spfa(s,t,n)){
        int v = inf;
        for(int i = t; i != s; i = pre[i])
            v = min(v, e[pos[i]].v);
        fw += v;
        ct += dis[t] * v;
        for(int i = t; i != s; i = pre[i]){
            e[pos[i]].v -= v;
            e[pos[i] ^ 1].v += v;
        }
    }
    return ct; // ct是费用
    //return fw; // fw是最大流值
}

int b[300];
int g[300][300];
int main()
{
    int fcas=1;
    int n,m,k,sum,a,T;
   // freopen("1003.in", "r", stdin);
  //  freopen("out.txt","w",stdout);
    scanf("%d",&T);
    for(int cas=1;cas<=T;cas++)
    {
        scanf("%d%d%d",&n,&m,&k);
        sum=0;
        for(int i=0;i<m;i++)
            scanf("%d",&b[i]),sum+=b[i];
        for(int i=0;i<m;i++)
            for(int j=0;j<n;j++)
                scanf("%d",&g[i][j]);
        int S=n+m,T=n+m+1;
        memset(hd,-1,sizeof(hd));
        cnt=0;
        for(int i=0;i<n;i++)
            insert(S,i,1,0);
        for(int i=0;i<m;i++)
            for(int j=0;j<n;j++)
                if(g[i][j])
                    insert(j,i+n,1,0);
        for(int i=0;i<m;i++)
        {
            insert(i+n,T,b[i]/k,-(k-1));
            if(b[i]%k>1)
                insert(i+n,T,1,-((b[i]%k)-1));
        }
        int ans = mcf(S,T,T+1);
        printf("Case #%d: ",cas);
        if(n-ans>=sum)
            puts("YES");
        else puts("NO");

    }
    return 0;
    /* printf("%d\n",fcas);*/
}
