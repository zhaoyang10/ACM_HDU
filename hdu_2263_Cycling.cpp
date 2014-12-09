#include"iostream"
#include"queue"
#include"algorithm"
#include"cstdio"
#include"string.h"
#define MAXN 105
#define MAXM 10005
#define inf 0x3f3f3f3f
using namespace std;
struct ee{
    int u,v,c;
}edge[MAXM];
struct edges{
    int u,c,next;
}e[MAXM]; 
int N,M,idx;
int p[MAXN],dist[MAXN];
bool used[MAXN];
queue<int>q;
void init(){
    idx=0;
    memset(p,0xff,sizeof(p));
}
void addedge(int u,int v,int c){
    e[idx].u=v;
    e[idx].c=c;
    e[idx].next=p[u];
    p[u]=idx++;
}
void spfa(int s){
    int t,u,w;
    while(!q.empty())q.pop();
    memset(used,false,sizeof(used));
    for(int i=0;i<N;i++)dist[i]=inf;
    dist[s]=0;
    q.push(s);
    while(!q.empty()){
        t=q.front();
        q.pop();
        used[t]=false;
        for(int i=p[t];i!=-1;i=e[i].next){
            u=e[i].u;
            w=e[i].c;
            if(dist[t]+w<dist[u]){
                dist[u]=dist[t]+w;
                if(!used[u]){
                    used[u]=true;
                    q.push(u);
                }
            }
        }
    }
}
int hash[MAXN];
struct node{
    int id,height;
    friend bool operator<(node a,node b){
        return a.height<b.height;
    }
}nod[MAXN];
int main(){
    int T,a,b,K,l,h,ll,hh,mid,low,mh,lh;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&N,&M);
        mh=inf;
        lh=0;
        for(int i=0;i<N;i++){
            scanf("%d",&nod[i].height);
            if(nod[i].height<mh)mh=nod[i].height;
            if(nod[i].height>=lh)lh=nod[i].height;
            nod[i].id=i;
        }
        sort(nod,nod+N);
        for(int i=0;i<N;i++){
            hash[nod[i].id]=i;
        }
        for(int i=0;i<M;i++){
            scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].c);
            edge[i].u--;
            edge[i].v--;
        }
        bool flag=false;
        int res=-1;
        h=lh-mh;
        l=0;
        res=inf;
        int rd=inf;
        while(l<=h){
            flag=false;
            mid=(l+h)>>1;
            for(int i=0;i<N;i++){
                 low=nod[i].height;
                 init();
                 for(int j=0;j<M;j++){
                     if(nod[hash[edge[j].u]].height<low || 
                        nod[hash[edge[j].u]].height>low+mid ||
                        nod[hash[edge[j].v]].height<low ||
                        nod[hash[edge[j].v]].height>low+mid)continue;
                     addedge(edge[j].u,edge[j].v,edge[j].c);
                     addedge(edge[j].v,edge[j].u,edge[j].c);
                 }
                 spfa(0);
                 if(dist[N-1]!=inf){
                     if(mid==res){
                         if(dist[N-1]<rd)rd=dist[N-1];
                     }
                     else if(mid<res){
                         res=mid;
                         rd=dist[N-1];
                     }
                     flag=true;
                 }
             }
             if(flag){
                 h=mid-1;             
             }
             else{
                 l=mid+1;
             }
         }
         printf("%d %d\n",res,rd);
    }
//   system("pause");
    return 0;
}
