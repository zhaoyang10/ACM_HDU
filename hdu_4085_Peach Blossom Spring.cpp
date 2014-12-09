#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;
#define nMax  55
#define mMax 2100
#define STA  1<<10
int n,K,s,tot;
int dp1[STA],dp[nMax][STA],st[nMax],Must[nMax],first[nMax],next[mMax];
bool in[nMax][STA];
struct Edge{
    int v,w;
}E[mMax];

void init()
{
    int i,j;
    s=(1<<(2*K));    tot=0;
    for(i=0;i<n;i++)    st[i]=0;
    for(i=0;i<K;i++)    st[i]=(1<<i),Must[i]=i;
    for(j=n-1;i<2*K;j--,i++)    st[j]=(1<<i),Must[i]=j;

    for(i=0;i<s;i++)
        for(j=0;j<n;j++)
            dp[j][i]=-1,in[j][i]=false;

    for(i=0;i<2*K;i++)    dp[ Must[i] ][ st[ Must[i] ] ] = 0 ;

    for(i=0;i<n;i++)    first[i]=-1;
}

inline void insert(int u,int v,int w)
{
    E[tot].v=v;    E[tot].w=w;    next[tot]=first[u];    first[u]=tot++;
}

queue<int>Q;

void SPFA()
{
    register int i,tmp,u,v,st1,st2,w;
    while(!Q.empty()){
        tmp = Q.front();    Q.pop();
        u = tmp%nMax;    st1 = tmp/nMax;    in[u][st1]=false;
        for(i=first[u]; i!=-1; i=next[i]){
            v=E[i].v;    w=E[i].w;    st2 = st1|st[v];
            if(dp[v][st2]>dp[u][st1]+w || dp[v][st2]==-1){
                dp[v][st2] = dp[u][st1]+w;
                if(st1 == st2 && !in[v][st2])    Q.push(st2*nMax+v),in[v][st2]=true;
            }
        }
    }
}

void Steiner_Tree()
{
    int i,j,t;
    while(!Q.empty())    Q.pop();
    for( i=0; i<s; i++){
        for( j=0; j<n; j++){
            if(st[j] && !(st[j] && i))    continue;
            for(t=(i-1)&i; t; t=(t-1)&i){
                if(dp[j][t|st[j]]==-1)    continue;
                if(dp[j][(i-t)|st[j]]==-1)    continue;
                if(dp[j][i]==-1 || dp[j][i]>dp[j][t|st[j]]+dp[j][(i-t)|st[j]])
                    dp[j][i] = dp[j][t|st[j]]+dp[j][(i-t)|st[j]];
            }
            if(dp[j][i]!=-1)    Q.push(i*nMax+j),in[j][i]=true;
        }
        SPFA();
    }
}

bool check(int st)
{
    int i,sa=0,sb=0;
    for(i=0;i<K;i++)    if((st>>i)&1)    sa++;
    for(i=K;i<2*K;i++)    if((st>>i)&1)    sb++;
    return sa==sb;
}

void DP()
{
    int i,j,k,t;
    for(i=0;i<s;i++){
        dp1[i]=-1;
        for(j=0;j<n;j++){
            if(dp[j][i]==-1)    continue;
            if(dp1[i]==-1 || dp1[i] > dp[j][i])    dp1[i]=dp[j][i];
        }
    }
    for(i=0; i<s; i++)    if(check(i)){
        for(t=(i-1)&i; t; t=(t-1)&i)
            if(check(t) && check(i-t)){
                if(dp1[t]==-1 || dp1[i-t]==-1)    continue;
                if(dp1[i]==-1 || dp1[i]>dp1[t]+dp1[i-t])    dp1[i]=dp1[t]+dp1[i-t];
            }
    }
    if(dp1[s-1]==-1)    printf("No solution\n");
    else printf("%d\n",dp1[s-1]);
}

int main()
{
    int T,i,j,k,u,v,w,m;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d%d",&n,&m,&K);
        init();
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            u--,v--;
            insert(u,v,w);
            insert(v,u,w);
        }
        Steiner_Tree();
        DP();
    }
    return 0;
}
