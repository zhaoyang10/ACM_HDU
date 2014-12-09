#include <stdio.h>  
#include <cstring>  
using namespace std;  
struct gtype {  
       int y,next;  
}g[1000100];  
int first[20010],tt,n,m,tot,a[10010],x,y,k;  
int low[20010],dfn[20010],stk[20010],cnt[20010],id,idx,end;  
void add(int x,int y) {  
    tot++;  
    g[tot].y=y;  
    g[tot].next=first[x];  
    first[x]=tot;  
}  
void tarjan(int u) {  
    low[u]=dfn[u]=++idx;  
    stk[++end]=u;  
    for(int x=first[u];x!=-1;x=g[x].next) {  
        int v=g[x].y;  
        if (!dfn[v]) {  
            tarjan(v);  
            if (low[u]>low[v]) low[u]=low[v];  
        }  
        else if (cnt[v]==0 && low[u]>dfn[v]) low[u]=dfn[v];  
    }  
    if(low[u]==dfn[u]) {  
        ++id;  
        do {  
           cnt[stk[end]]=id;  
        }while(u!=stk[end--]);  
    }  
}  
void did(int x,int y,int k) {  
     int a1=a[x],a2=(a[x]+1)%3;  
     if (a2==0) a2=3;  
     int b1=a[y],b2=(a[y]+1)%3;  
     if (b2==0) b2=3;  
       
     if (k==0) {  
               if (a1==b1) add(x,y),add(y,x),add(x+n,y+n),add(y+n,x+n);  
               else if (a2==b1) add(x+n,y),add(y,x+n),add(x,x+n),add(y+n,y);  
               else add(x,y+n),add(y+n,x),add(x+n,x),add(y,y+n);  
     }  
     else {  
               if (a1==b1) add(x,y+n),add(y+n,x),add(y,x+n),add(x+n,y);  
               else if (a2==b1) add(y,x),add(x+n,y+n);  
               else add(x,y),add(y+n,x+n);  
     }  
}  
int main() {  
    scanf("%d",&tt);  
    for (int cas=1;cas<=tt;cas++) {  
        scanf("%d%d",&n,&m);  
        tot=0;  
        memset(g,0,sizeof(g));  
        memset(first,-1,sizeof(first));  
          
        for (int i=1;i<=n;i++)  
            scanf("%d",&a[i]);  
        for (int i=1;i<=m;i++) {  
                 scanf("%d%d%d",&x,&y,&k);  
                 if (k==1) did(x,y,1);  
                 else did(x,y,0);  
        }  
          
        memset(dfn,0,sizeof(dfn));  
        memset(low,0,sizeof(low));  
        memset(cnt,0,sizeof(cnt));         
        id=idx=end=0;  
        for (int i=1;i<=2*n;i++)  
            if (!dfn[i]) tarjan(i);  
        bool yes=true;  
        for (int i=1;i<=n;i++)  
            if (cnt[i]==cnt[i+n]) {  
               yes=false;  
               break;  
            }  
        printf("Case #%d: ",cas);  
        if (yes) printf("yes\n");  
        else printf("no\n");  
    }  
    return 0;  
}      
