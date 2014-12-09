#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
const int nMax = 8;
typedef unsigned long long ull;
int a[nMax][nMax];
bool vis[nMax][nMax];
int n,dep;
int mx[]={0,0,-1,1};
int my[]={-1,1,0,0};
typedef pair<int, int> PII;
PII Q[nMax * nMax];


inline bool fit(int x, int y)
{
    return x>=0 && y>=0 && x<n && y<n && (!vis[x][y]);
}

inline void bfs(int x,int y)
{
    register int x1,y1,x2,y2,i;
    Q[0]= make_pair(x,y) ;
    int head=0,    tail=1;
    vis[x][y]=1;
    while(head ^ tail){
        PII u=Q[head++];
        x1=u.first;    y1=u.second;
        for(i=0;i<4;i++){
            x2=x1+mx[i];    y2=y1+my[i];
            if(fit(x2,y2) && a[x2][y2]==a[x][y]){
                vis[x2][y2]=1;
                Q[tail++] = make_pair(x2,y2) ;
            }
        }
    }
}
/*
ull hash()
{
    ull res=0;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            res|=vis[i][j],res<<=1;
    return res;
}

void rehash(ull tmp)
{
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            tmp>>=1,vis[i][j]=(tmp&1);
}
*/
inline int cal()
{
    register int tmp=0,i,j,res=0;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            if(!vis[i][j])    tmp|=(1<<a[i][j]);
    for(i=0;i<6;i++)    res+=((tmp>>i)&1);
    return res;
}

bool dfs(int now)
{

    if(now==dep)    return cal()==0;
    if(cal()+now>dep)    return false;

    int i,j,k,c,x1,y1;
    bool tvis[nMax][nMax];
    bool flag=false;
    memcpy(tvis,vis,sizeof(vis));
/*
    printf("now=%d\n",now);
    for(i=0;i<n;i++,puts(""))    for(j=0;j<n;j++)    printf("%d\t",tvis[i][j]);
*/
    for(c=0;c<6;c++){
        for(i=0;i<n;i++)        for(j=0;j<n;j++)
            if(vis[i][j]){
                for(k=0;k<4;k++){
                    x1=i+mx[k],y1=j+my[k];
                    if(fit(x1,y1) && a[x1][y1]==c){
                        bfs(x1,y1);
                        flag=true;
                    }
                }
            }
        if( !flag )    continue;
        if( dfs(now+1))    return true;
        flag=false;
        memcpy(vis,tvis,sizeof(vis));
    }
    return false;
}

int main()
{
    int i,j;
    ull tmp;
    bool tvis[nMax][nMax];
    while(~scanf("%d",&n) && n){
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                scanf("%d",&a[i][j]);
        memset(vis,0,sizeof(vis));
        bfs(0,0);
//        tmp=hash();
        memcpy(tvis,vis,sizeof(vis));
    //    for(i=0;i<n;i++,puts(""))    for(j=0;j<n;j++)    printf("%d\t",tvis[i][j]);
        for(dep=cal();;dep++){
            if(dfs(0))    break;
            memcpy(vis,tvis,sizeof(vis));
        }
        printf("%d\n",dep);
    }
    return 0;
}
