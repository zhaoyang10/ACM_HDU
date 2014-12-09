#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;
#define ll long long
const int nMax = 10000;
const int mMax = 30010;

struct Edge{
    int v;    ll w;
}e[mMax];
int first[nMax],next[mMax];
int tot,n,s;
ll d[nMax],L[nMax];
bool in[nMax];

void insert(int u,int v,ll w){
    e[tot].v=v;    e[tot].w=w;    next[tot]=first[u];    first[u]=tot;    tot++;
}

void makeEdge(int u,int v,ll w,char* str)
{
    int i,j;
    if(str[0]=='L')    i=0;
    else if(str[0]=='O')    i=1;
    else if(str[0]=='V')    i=2;
    else if(str[0]=='E')    i=3;
    
    j=(i+3)%4;
    
    insert(u*4+j,v*4+i,w);
    insert(v*4+j,u*4+i,w);
}

void spfa()
{
//    memset(d,-1,sizeof(d));
    memset(L,0,sizeof(L));
    memset(in,0,sizeof(in));
    d[s]=0;
    queue<int>Q;
    while(!Q.empty())    Q.pop();
    Q.push(s);
    int u,v,l;
    ll w;
    while(!Q.empty()){
        u=Q.front();    Q.pop();    in[u]=false;
        for(int i=first[u];i!=-1;i=next[i]){
            v=e[i].v;    w=e[i].w;
            if( d[v]==-1 ||(s==v && L[v]==0) || d[v]>d[u]+w){
                d[v]=d[u]+w;    L[v]=L[u]+(v%4==3);
                if(!in[v]){        in[v]=true;        Q.push(v);    }
            }else    if(d[v]==d[u]+w && L[v]<L[u]+(v%4==3)){
                L[v]=L[u]+(v%4==3);
                if(!in[v]){        in[v]=true;        Q.push(v);    }
            }
        }
    }
}

int main()
{
    int T,ca,u,v,m,t;
    ll w;
    char str[10];
    scanf("%d",&T);
    for(ca=1;ca<=T;ca++){
        memset(first,-1,sizeof(first));
        scanf("%d%d",&n,&m);    
        for(int i=0;i<n*4+4;i++)    d[i]=-1;
        s=7;    t=n*4+3;    tot=0;
        while(m--){
            scanf("%d%d%I64d%s",&u,&v,&w,str);
            makeEdge(u,v,w,str);
        }
        spfa();
        printf("Case %d: ",ca);
        if(L[t]==0)    printf("Binbin you disappoint Sangsang again, damn it!\n");    
        else printf("Cute Sangsang, Binbin will come with a donkey after travelling %I64d meters and finding %I64d LOVE strings at last.\n",d[t],L[t]);
    }    
    system("pause");
    return 0;
}
