#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<set>
#include<queue>
#include<cmath>
using namespace std;
#define nMax 100010
#define ll long long
struct Point{
    int id;
    ll d,x,y;
    Point(ll _x=0,ll _y=0,ll _d=0,int _id=0):x(_x),y(_y),d(_d),id(_id){}
    bool operator<(const Point & pp)const{
        if( y == pp.y)    return id<pp.id;
        return y<pp.y;
    }
}p[nMax];
set< Point >v[nMax];
bool cmp(int x,int y){    return p[x].x<p[y].x;    }
int ord[nMax],dis[nMax];
ll pos[nMax];
int n,tot;
bool vis[nMax];
void make_dis()
{
    ll pre=-1;    int i;    tot=0;
    for(i=0;i<n;i++)    if(p[ord[i]].x!=pre)    dis[ord[i]]=tot++,pre=p[ord[i]].x;
        else dis[ord[i]]=tot-1;
    for(i=0;i<n;i++)    pos[dis[i]] = p[i].x;
    //for(i=0;i<tot;i++)    printf("pos[%d]=%d\n",i,pos[i]);
    for(i=0;i<tot;i++)    v[i].clear();
    for(i=0;i<n;i++)    v[dis[i]].insert(p[i]);
}

int half(ll d)
{
    int mid,he=0,ta=tot;
    //printf("\nd=%d\n",d);
    while(he<ta){
        mid = (he+ta)>>1;
    //    printf("pos[%d]=%d\n",mid,pos[mid]);
        if( pos[ mid ] >= d)    ta = mid;
        else he = mid + 1;
    }
    return he;
}

int bfs(int u)
{
    if(vis[u])    return 0;
    int res=0,i,x1,x2;
    ll dd,xx,yy,y,x,cha;
    queue<int>Q;    while(!Q.empty())    Q.pop();    Q.push(u);
    set<Point>::iterator y1,y2,y3;
    v[dis[u]].erase( v[dis[u]].find(p[u]) );    vis[u]=true;
    while(!Q.empty()){
        u=Q.front();    Q.pop();    res++;
        x1 = half( p[u].x - p[u].d );
        x2 = half( p[u].x + p[u].d +1 );
        //printf("u=%d\tx1=%d\tx2=%d\n",u,x1,x2);
        for( i = x1; i < x2; i ++ ){
            x = p[u].x - pos[i];    if( x < 0 )     x = -x;
            y = p[u].d - x;
            //printf("dd = %I64d\ti = %d\tx = %I64d\t y = %I64d\n",dd,i,x,y);
            y1 = v[i].lower_bound( Point(0,p[u].y-y,-1,-1) ) ;
            y2 = v[i].upper_bound( Point(0,p[u].y+y+1,-1,-1) );
//            y1 = v[i].begin();    y2 = v[i].end();
            //if( y2 != v[i].end() )    printf("y2 : id=%d\n",(*y2).id);
            while(y1 != y2){
                //printf("y1: id= %d\n",(*y1).id);
                Q.push((*y1).id);
                vis[(*y1).id]=true;
                y3 = y1++;
                v[i].erase(*y3);
            }
        }
    }
    return res;
}

int main()
{
    int i,j,k,d,m,ca=1;
    while(scanf("%d",&n)!=EOF && n){
        for(i=0;i<n;i++)    scanf("%I64d%I64d%I64d",&p[i].x,&p[i].y,&p[i].d);
        for(i=0;i<n;i++)    ord[i]=i,vis[i]=false,p[i].id=i;
        sort(ord,ord+n,cmp);    make_dis();
        scanf("%d",&m);
        printf("Case #%d:\n",ca++);
        while(m--){
            scanf("%d",&d);
            printf("%d\n",bfs(--d));
        }
    }
    return 0;
}
