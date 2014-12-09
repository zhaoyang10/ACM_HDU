#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
#include <cmath>
#include <ctime>
#define INF 1<<29
#define MAXN 3003
#define MAXM 3000000
using namespace std;
struct node
{
    int ver;    // vertex
    int cap;    // capacity
    int flow;   // current flow in this arc
    int next, rev;
}edge[MAXM];
int dist[MAXN];
int numbs[MAXN], src, des, n, m;
int head[MAXN], e;
void add(int x, int y, int  c)
{       //e记录边的总数
    edge[e].ver = y;
    edge[e].cap = c;
    edge[e].flow = 0;
    edge[e].rev = e + 1;        //反向边在edge中的下标位置
    edge[e].next = head[x];   //记录以x为起点的上一条边在edge中的下标位置
    head[x] = e++;           //以x为起点的边的位置
    //反向边
    edge[e].ver = x;
    edge[e].cap = 0;  //反向边的初始网络流为0
    edge[e].flow = 0;
    edge[e].rev = e - 1;
    edge[e].next = head[y];
    head[y] = e++;
}
int Q[MAXN];
void rev_BFS()
{
    int qhead = 0, qtail = 0;
    for(int i = 1; i <= n; ++i)
    {
        dist[i] = MAXN;
        numbs[i] = 0;
    }
    Q[qtail++] = des;
    dist[des] = 0;
    numbs[0] = 1;
    while(qhead != qtail)
    {
        int v = Q[qhead++];
        for(int i = head[v]; i != -1; i = edge[i].next)
        {
            if(edge[edge[i].rev].cap == 0 || dist[edge[i].ver] < MAXN)continue;
            dist[edge[i].ver] = dist[v] + 1;
            ++numbs[dist[edge[i].ver]];
            Q[qtail++] = edge[i].ver;
        }
    }
}
int Curhead[MAXN], revpath[MAXN];
int  maxflow()
{
    int u;
    int totalflow = 0;

    for(int i = 1; i <= n; ++i)Curhead[i] = head[i];
    u = src;

   // printf("src = %d\n",src);
    while(dist[src] < n)
    {
        if(u == des)     // find an augmenting path
        {
            int  augflow = INF;
            for(int i = src; i != des; i = edge[Curhead[i]].ver)
                augflow = min(augflow, edge[Curhead[i]].cap);
            for(int i = src; i != des; i = edge[Curhead[i]].ver)
            {
                edge[Curhead[i]].cap -= augflow;
                edge[edge[Curhead[i]].rev].cap += augflow;
                edge[Curhead[i]].flow += augflow;
                edge[edge[Curhead[i]].rev].flow -= augflow;
            }
            totalflow += augflow;    //printf("totalflow = %d\n",totalflow);
            u = src;
        }
        int i;
        for(i = Curhead[u]; i != -1; i = edge[i].next)
            if(edge[i].cap > 0 && dist[u] == dist[edge[i].ver] + 1)break;
        if(i != -1)     // find an admissible arc, then Advance
        {
            Curhead[u] = i;
            revpath[edge[i].ver] = edge[i].rev;
            u = edge[i].ver;
        }
        else        // no admissible arc, then relabel this vertex
        {
            if(0 == (--numbs[dist[u]]))break;    // GAP cut, Important!
            Curhead[u] = head[u];
            int  mindist = n;
            for(int j = head[u]; j != -1; j = edge[j].next)
                if(edge[j].cap > 0)mindist = min(mindist, dist[edge[j].ver]);
            dist[u] = mindist + 1;
            ++numbs[dist[u]];
            if(u != src)
                u = edge[revpath[u]].ver;    // Backtrack
        }
    }
    return totalflow;
}
void init()
{
    e = 0;
    //memset(head, -1, sizeof(head));
    for( int i = 0; i <= n*2 + 2; i ++ )    head[i]=-1;
}
int b[1010][1010],sum[1010],c[1010];

int main()
{
    int T;
    scanf("%d", &T);
    int x, y, z, i, j, s;
    int cas = 0;
    while(T--)
    {
        scanf("%d", &n);
        init();                 s=0;
        src = n + 1;       des = n + 2;
        for( i = 1; i <= n; i ++ ){
            sum[i]=0;
            for(  j = 1; j <= n; j ++){
                scanf("%d",&b[i][j]);
                sum[i]+=b[i][j];
                add(i,j,b[i][j]);
            }
            s += sum[i];
        }
        for( i = 1; i <= n; i ++ )    scanf("%d",c+i);
        for( i = 1; i <= n; i ++ )    add(src,i,sum[i]);
        for( i = 1; i <= n; i ++ )    add(i,des,c[i]);
        n = des;


        rev_BFS();
        int  ans = maxflow();
     //   printf("s = %d\t ans = %d\n",s,ans);
        printf("%d\n",s-ans);
    }
    return 0;
}
