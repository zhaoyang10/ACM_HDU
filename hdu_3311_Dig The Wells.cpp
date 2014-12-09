#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
#define nMax 1010
#define mMax 13000
#define STA  1<<6

int n,s,tot,m;
int dp1[STA],dp[nMax][STA],first[nMax],next[mMax],st[nMax];
bool in[nMax][STA];


void init()
{
    int i,j;
    tot=0;    s=(1<<(n+1));
    for(i=0;i<=n+m;i++)    first[i]=-1;
    for(i=0;i<s;i++)
        for(j=0;j<=n+m;j++)
            dp[j][i]=-1,in[j][i]=false;
    for(i=n+1;i<=m;i++)    st[i]=0;
    for(i=0;i<=n;i++)    st[i]=(1<<i);
    for(i=0;i<=n;i++)    dp[i][st[i]]=0;
}

struct Edge{
    int v,w;
}E[mMax];

inline void insert(int u,int v,int w){    E[tot].v=v;    E[tot].w=w;    next[tot]=first[u];    first[u]=tot++;    }

queue<int>Q;

void SPFA()
{
    int i,tmp,u,v,st1,st2,w;
    while(!Q.empty()){
        tmp=Q.front();    Q.pop();
        u = tmp%nMax;     st1 = tmp/nMax;    in[u][st1]=false;
        for(i=first[u];i!=-1;i=next[i]){
            v=E[i].v;    w=E[i].w;    st2=(st1|st[v]);
            if(dp[v][st2]==-1 || dp[v][st2]>dp[u][st1]+w){
                dp[v][st2] = dp[u][st1] + w;
                if(st1==st2 && !in[v][st2])    in[v][st2]=true,Q.push(st2*nMax+v);
            }
        }
    }
}

void Steiner_Tree()
{
    int i,j,t;
    while(!Q.empty())    Q.pop();
    for(i=0;i<s;i++){
        for(j=0;j<=n+m;j++){
            if(st[j] && !(st[j]&i))    continue;
            for(t=(i-1)&i; t; t=(t-1)&i){
                if(dp[j][t|st[j]]==-1 || dp[j][(i-t)|st[j]]==-1)    continue;
                if(dp[j][i]==-1 || dp[j][i]>dp[j][t|st[j]]+dp[j][(i-t)|st[j]])
                    dp[j][i] = dp[j][t|st[j]] + dp[j][(i-t)|st[j]];
            }
            if(dp[j][i]!=-1)    in[j][i]=true,Q.push(i*nMax+j);
            //printf("dp[%d][%d]=%d\n",j,i,dp[j][i]);
        }
        SPFA();
    }
}

void DP()
{
    int i,j,t;
    for(i=0;i<s;i++){
        dp1[i]=-1;
        for(j=0;j<=n+m;j++){
            if(st[j] && !(st[j] & i))    continue;
            if(dp[j][i]==-1)    continue;
            if(dp1[i]==-1 || dp1[i]>dp[j][i])    dp1[i] = dp[j][i];
        }
        //printf("dp1[%d]=%d\n",i,dp1[i]);
    }


    for(i=0;i<s;i++)    if( i&1 ){
        for(j=0;j<=n+m;j++){
            if( st[j] && !(i&st[j]) )    continue;
            for( t=(i-1)&i;    t; t=(t-1)&i ){
                if(dp1[t|1]==-1 || dp1[(i-t)|1]==-1)    continue;
                if(dp1[i]==-1 || dp1[i]>dp1[i|1]+dp1[(i-t)|1])    dp1[i] = dp1[t|1]+dp1[(i-t)|1];
            }
        }
    }
    printf("%d\n",dp1[s-1]);
}

int main()
{
    int p,u,v,w,i;
    while(scanf("%d%d%d",&n,&m,&p)!=EOF){
        init();
        for(i=1;i<=n+m;i++){
            scanf("%d",&w);
            insert(0,i,w);
            insert(i,0,w);
        }
        while(p--){
            scanf("%d%d%d",&u,&v,&w);
            insert(u,v,w);
            insert(v,u,w);
        }
        Steiner_Tree();
        DP();
    }
    return 0;
}
