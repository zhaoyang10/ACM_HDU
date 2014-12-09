// hdu    4411 最小费用最大流
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int mm=666666;
const int mn=222;
const int oo=1e6;
const int mMax = 25;
int src,dest,node,edge;
int ver[mm],cost[mm],flow[mm],next[mm],iflow[mm];
int head[mn],dis[mn],p[mn],q[mn];
int w[mMax],score[mMax];
bool vis[mn]={0};
void prepare(int _node,int _src,int _dest)
{
    node=_node,src=_src,dest=_dest;
    for(int i=0;i<node;++i)head[i]=-1;
    edge=0;
}
void addedge(int u,int v,int f,int c)
{
    iflow[edge]=f,ver[edge]=v,flow[edge]=f,cost[edge]=c,next[edge]=head[u],head[u]=edge++;
    iflow[edge]=0,ver[edge]=u,flow[edge]=0,cost[edge]=-c,next[edge]=head[v],head[v]=edge++;
}
bool Spfa()
{
    int i,u,v,l,r=0,tmp;
    for(i=0;i<node;++i)dis[i]=oo;
    dis[q[r++]=src]=0;
    p[src]=p[dest]=-1;
    for(l=0;l!=r;(++l==mn)?l=0:l)
        for(i=head[u=q[l]],vis[u]=0;i>=0;i=next[i])
            if(flow[i]&&dis[v=ver[i]]>(tmp=dis[u]+cost[i]))
            {
                dis[v]=tmp;
                p[v]=i^1;
                if(vis[v])continue;
                vis[q[r++]=v]=1;
                if(r==mn)r=0;
            }
    return p[dest]>-1;
}
int Spfaflow()
{
    int i,delta,ret=0;
    while(Spfa())
    {
        for(i=p[dest],delta=oo;i>=0;i=p[ver[i]])
            if(flow[i^1]<delta)delta=flow[i^1];
        for(i=p[dest];i>=0;i=p[ver[i]])
            flow[i]+=delta,flow[i^1]-=delta;
        ret+=delta*dis[dest];
     //   printf("ret = %d\n",ret);
    }
    return ret;
}
int main()
{
    int i,j,K,n,m,ok;
    while(scanf("%d%d%d",&n,&K,&m),n+K+m)
    {
        prepare(n+m+2,0,n+m+1);
        for(i=1;i<=m;i++)    scanf("%d",w+i);
        for(i=1;i<=m;i++)    scanf("%d",score+i);
        for(i=1;i<=n;i++)    addedge(src,i,K,0);


        for(i=1;i<=n;i++)
            for(j=1;j<=m;j++){
                scanf("%d",&ok);
                if(ok)    addedge(i,n+j,K,0);
            }

        for(i=1;i<=m;i++){
            int f=0;
            if(score[i]<60){
                f = 60 - score[i];
                addedge(n+i,dest,f,-oo);
            }
            while(score[i] + f < 100){
                addedge(n+i,dest,1,w[i]*(2*(score[i]+f)-199));
                f++;
            }
            //printf("score[%d]=%d\tf=%d\n",i,score[i],f);
        }
        //system("pause");
        Spfaflow();
        //system("pause");
        for(i=1; i<=m; i++)    p[i]=0;
        for(i=1; i<=m; i++)
            for(j=head[i+n];j!=-1;j = next[j])
                if(iflow[j]  && iflow[j]>flow[j]){
                    //printf("i=%d\tiflow[%d]=%d\tflow[%d]=%d\n",i,j,iflow[j],j,flow[j]);
                    p[i]+=iflow[j]-flow[j];
                }
        bool flag=false;
        for(i=1;i<=m;i++){    score[i]+=p[i];    if(score[i]<60)    flag=true;
            //printf("score[%d]=%d\n",i,score[i]);
        }
        if(flag)    puts("0.000000");
        else{
            double ans1 = 0 ,ans2 = 0 ,tmp = 4.0*1600;
            for(i=1;i<=m;i++)    ans2+=w[i];    ans2*=1600;
            for(i=1;i<=m;i++)    ans1+=w[i]*( tmp - 3*(100 - score[i])*(100 - score[i]) );
            printf("%.6lf\n",ans1/ans2);
        }
    }
    return 0;
}
