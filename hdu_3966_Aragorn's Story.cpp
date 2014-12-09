#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
const int nMax = 100010;
int n,tot;
int fa[nMax],sze[nMax],top[nMax],son[nMax],w[nMax],dep[nMax],a[nMax];
vector<int>E[nMax];

#define L( x )  ( x<< 1 )
#define R( x )    ( x<<1|1 )
#define MID(x,y)( (x+y)>>1 )

struct Tree{
    int l,r,s,pl;
    void init(int _l,int _r){
        l=_l;    r=_r;    s=pl=0;
    }
}t[nMax*3];


void init()
{
    int i;
    for(i=1;i<=n;i++)    E[i].clear();
    memset(fa,0,sizeof(fa));
    memset(son,0,sizeof(son));
    memset(top,0,sizeof(top));
    tot=1;
}

void build(int l,int r,int p)
{
    t[p].init(l,r);
    if(l==r)    return;
    int mid=MID(l,r);
    build(l,mid,L(p));
    build(mid+1,r,R(p));
}

void dfs1(int u,int dp)
{
    dep[u]=dp;    sze[u]=1;
    int Max=-1,i,sz=E[u].size(),v;
    for(i=0;i<sz;i++){
        v=E[u][i];
        if(v==fa[u])    continue;
        fa[v]=u;
        dfs1(v,dp+1);
        if(Max<sze[v])    Max=sze[v],son[u]=v;
        sze[u]+=sze[v];
    }
}

void dfs2(int u,int tp)
{
    top[u]=tp;        w[u]=tot++;
    if(!son[u])        return;
    int i,sz=E[u].size(),v;
    dfs2(son[u],tp);
    for(i=0;i<sz;i++){
        v=E[u][i];
        if(v==fa[u] || v==son[u])    continue;
        dfs2(v,v);
    }
}

void insert(int ls,int lt,int pl,int p)
{
    int l,r;
    l=t[p].l;    r=t[p].r;
    //printf("l=%d\tr=%d\tls=%d\tlt=%d\tpl=%d\tp=%d\n",l,r,ls,lt,pl,p);
    if(l==ls && r==lt){
        t[p].pl+=pl;
        return;
    }
    int mid=MID(l,r);
    if(mid<ls)    insert(ls,lt,pl,R(p));
    else    if(mid>=lt)    insert(ls,lt,pl,L(p));
    else{
        insert(ls,mid,pl,L(p));
        insert(mid+1,lt,pl,R(p));
    }
}

inline void pushdown(int x)
{
    t[L(x)].pl+=t[x].pl;
    t[R(x)].pl+=t[x].pl;
    t[x].pl=0;
}

int query(int x,int p)
{
    //printf("x=%d\tl=%d\tr=%d\tp=%d\n",x,t[p].l,t[p].r,p);
    if(t[p].l==x && t[p].r==x)    return t[p].pl+t[p].s;
    pushdown(p);
    int mid=MID(t[p].l,t[p].r);
    if(mid<x)    return query(x,R(p));
    return query(x,L(p));
}

void conv(int u,int v,int pl)
{
    int f1,f2;
    f1=top[u];    f2=top[v];
    if(dep[f1]<dep[f2])    swap(u,v),swap(f1,f2);
    while(f1!=f2){
        insert(w[f1],w[u],pl,1);
        u=fa[f1];    f1=top[u];
        if(dep[f1]<dep[f2])    swap(u,v),swap(f1,f2);
    }
    if(dep[u]<dep[v])    swap(u,v);
    insert(w[v],w[u],pl,1);
}

int main()
{
    int m,p,pl,u,v,i;
    char str[5];
    while(scanf("%d%d%d",&n,&m,&p)!=EOF){
        init();
        for(i=1;i<=n;i++)    scanf("%d",a+i);
        while(m--){
            scanf("%d%d",&u,&v);
            E[u].push_back(v);
            E[v].push_back(u);
        }
        dfs1(1,1);    //    puts("dfs1");
        dfs2(1,0);    //    puts("dfs2");
        build(1,tot-1,1);//    puts("build");
        for(i=1;i<=n;i++)    insert(w[i],w[i],a[i],1);
        //puts("insert");
        while(p--){
            scanf("%s",str);
            if(str[0]=='Q'){
                scanf("%d",&u);
                printf("%d\n",query(w[u],1));
            }else{
                scanf("%d%d%d",&u,&v,&pl);
                if(str[0]=='D')    pl*=-1;
                conv(u,v,pl);
            }
        }
    }
    return 0;
}
