#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
using namespace std;
#define INF  5010
int lx[INF],ly[INF],match[INF];
int slack,n,m,tot1,tot2;
bool visx[INF],visy[INF];
int w[INF][INF];
struct House
{
    int x,y;
    void init(int xx,int yy){
        x=xx;  y=yy;
    }
}H[INF];

struct Man
{
    int x,y;
    void init(int xx,int yy){
        x=xx;   y=yy;
    }
}M[INF];

int getdis(int i,int j)
{
    return -(abs(M[i].x-H[j].x)+abs(M[i].y-H[j].y));
}

bool dfs(int u)
{
    visx[u]=true;
    int v;
    for(v=0;v<tot2;v++)
        if(visy[v])  continue;
        else{
           // visy[v]=true;
            int temp=(lx[u]+ly[v])-w[u][v];
            if(temp==0){
                visy[v]=true;
                if(match[v]==-1 || dfs(match[v])){
                    match[v]=u;
                    return true;
                }
            }else if(slack>temp || slack==0)  slack=temp;
        }
    return false;
}

void KM()
{
    memset(match,-1,sizeof(match));
    memset(lx,0,sizeof(lx));
    memset(ly,0,sizeof(ly));
    int i,j,k;
    for(i=0;i<tot1;i++)
        for(j=0;j<tot2;j++)
            if(w[i][j]>lx[i] || lx[i]==0)  lx[i]=w[i][j];
    for(i=0;i<tot1;i++){
        while(1){
            memset(visx,false,sizeof(visx));
            memset(visy,false,sizeof(visy));
            slack=0;
            if(dfs(i))  break;
            for(j=0;j<tot1;j++)
                if(visx[j])   lx[j]-=slack;
            for(j=0;j<tot2;j++)
                if(visy[j])   ly[j]+=slack;
     /*       printf("slack=%d\n",slack);
            if(slack==1){
                for(int k=0;k<tot1;k++)  printf("lx[%d]=%d\n",k,lx[k]);
                for(int k=0;k<tot2;k++)  printf("ly[%d]=%d\n",k,ly[k]);
                for(int k=0;k<tot2;k++)  printf("match[%d]=%d\n",k,match[k]);
                system("pause");

            }
 */
        }
    }
    int ans=0;
    for(i=0;i<tot1;i++)  ans+=lx[i];
    for(i=0;i<tot2;i++)  ans+=ly[i];
    ans*=-1;
    printf("%d\n",ans);
}

int main()
{
    int i,j,k;
    char s[110];
    while(scanf("%d%d",&n,&m)!=EOF && (n || m)){
        tot1=0;   tot2=0;
        for(i=0;i<n;i++){
            scanf("%s",s);
            for(j=0;j<m;j++)
                if(s[j]=='.')  continue;
                else if(s[j]=='H')   H[tot2++].init(i,j);
                else if(s[j]=='m')   M[tot1++].init(i,j);
        }
        for(i=0;i<tot1;i++)
            for(j=0;j<tot2;j++)
                w[i][j]=getdis(i,j);
        KM();
    }
    return 0;
}
