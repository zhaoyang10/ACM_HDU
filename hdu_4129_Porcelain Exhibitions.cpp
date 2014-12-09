//平面图网络流  100个点 100000条边 每个点有下界

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;
struct Point
{
         int x,y;
};
const int maxP=1000 + 1;
int map[maxP][maxP];
Point p[maxP];
int bili;
int MIN_K,MAX_K;
int np;
int workP;
int next[maxP][maxP];
int l[maxP][maxP],ll[maxP];
bool cmp(int a,int b)
{
         return atan2((double)p[a].y-p[workP].y,p[a].x-p[workP].x) <atan2((double)p[b].y-p[workP].y,p[b].x-p[workP].x);
}
bool init()
{
         int m;
         int i;
         scanf("%d%d%d%d%d",&np,&m,&MIN_K,&MAX_K,&bili);
         if(np==0)        return false;
         bili/=2;
         for(i=0;i<np;i++)        scanf("%d%d",&p[i].x,&p[i].y);
         memset(map,-1,sizeof(map));
         memset(ll,0,sizeof(ll));
         while(m--)
         {
            int u,v,w;
            scanf("%d%d%d",&u,&v,&w);
            map[u][v]=map[v][u]=w;
            l[u][ll[u]++]=v;
            l[v][ll[v]++]=u;
         }
         for(workP=0;workP<np;workP++)
         {
            sort(l[workP],l[workP]+ll[workP],cmp);
            l[workP][ll[workP]]=l[workP][0];
            for(i=1;i<=ll[workP];i++)
                next[l[workP][i]][workP]=l[workP][i-1];
         }
         return true;
}
int visit[maxP][maxP];
const int maxn=2000+10;
int n;
int area[maxn];
int addw[maxn][maxn];
int dfs(int u,int v)
{
    if(visit[u][v]>=0)        return 0;
    visit[u][v]=n;
    return p[u].x*p[v].y-p[u].y*p[v].x+dfs(v,next[u][v]);
}
//------------------------------------------------------------
const int maxm=maxn*maxn;
typedef int lld;
struct Edge
{
    int y,f,ne;
} e[maxm];
int ee;
int st[maxn];
void addedge(int x,int y,int f,int ff)//x->y增加一条容量f的正向边和容量ff的反向边
{
         e[ee].y=y;e[ee].f=f;e[ee].ne=st[x];st[x]=ee++;
         e[ee].y=x;e[ee].f=ff;e[ee].ne=st[y];st[y]=ee++;
}
#define INF (lld)1<<30
int h[maxn],vh[maxn];
lld flow;
lld aug(const int sx,const int m,const int ex,const lld t,int n)//目标ex t是流量 m是当前所在节点
{
   int i,minh;
   lld l,d;
   if(m== ex) return t;
    l= t;
   minh = n - 1;
   for(i=st[m];i!=-1;i=e[i].ne) if(e[i].f>0){
       if(h[e[i].y]+1==h[m]){
           if(l<e[i].f) d=l; else d=e[i].f;
           d = aug(sx,e[i].y,ex,d,n);
           e[i].f-=d;
           e[i^1].f+=d;
           l-=d;
           if(h[sx]>=n) return t-l;
           if (l==0) break;
       }
       if(minh>h[e[i].y]) minh=h[e[i].y];
    }
   if(l==t)
    {
       vh[h[m]]--;
       if(vh[h[m]]==0) h[sx]=n;
       h[m] = minh + 1;
       vh[h[m]]++;
    }
   return t-l;
}

lld maxflow(int sx,int ex,int n)
{
   memset(h,0,sizeof(int)*n);
   memset(vh,0,sizeof(int)*n);
   vh[sx] = n;    flow=0;
   while( h[sx]<n )
       flow += aug(sx,sx,ex,INF,n);
    return flow;
}

//------------------------------------------------------------

#define _DEBUG 123
int main()
{
         while(init())
         {
            int i,j;
            memset(visit,-1,sizeof(visit));
            n=0;
            for(i=0;i<np;i++)
                for(j=0;j<np;j++) if (j!=i)
                    if(map[i][j]>=0 && visit[i][j]==-1)
                    {
                        area[n]=dfs(i,j);
                        if(area[n]>=0)        n++;
                    }
            memset(addw,0,sizeof(addw));
            for(i=0;i<np;i++)
            for(j=i+1;j<np;j++)
            if(map[i][j]>=0)
            {
                addw[visit[i][j]][visit[j][i]]+=map[i][j];
                addw[visit[j][i]][visit[i][j]]+=map[i][j];
            }
            memset(st,-1,sizeof(st));
            ee=0;
            for(i=0;i<n;i++)
                for(j=i+1;j<n;j++)
                    if(addw[i][j]>0)
                        addedge(i,j,addw[i][j],addw[j][i]);
            for(i=0;i<n;i++){
                addedge(n,i,bili*area[i],0);
                addedge(i,n+1,MIN_K,0);
            }
            int maxf=maxflow(n,n+1,n+2);
            if(maxf<MIN_K*n){
                puts("-1");
                continue;
            }
            for(i=st[n+1];i!=-1;i=e[i].ne)        e[i^1].f+=MAX_K-MIN_K;
            maxf+=maxflow(n,n+1,n+2);
            printf("%d\n",maxf);
         }
         return 0;
}
