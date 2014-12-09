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
#define INF 11111111111111LL
#define MAXN 40005
#define MAXM 320000
#define PI acos(-1.0)
using namespace std;
struct node
{
    int ver;    // vertex
    long long cap;    // capacity
    long long flow;   // current flow in this arc
    int next, rev;
}edge[MAXM];
long long dist[MAXN];
int numbs[MAXN], src, des, n, m;
int head[MAXN], e;
void add(int x, int y, long long  c)
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
void rev_BFS()
{
    int Q[MAXN], qhead = 0, qtail = 0;
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

long long  maxflow()
{
    int u;
    long long totalflow = 0;
    int Curhead[MAXN], revpath[MAXN];
    for(int i = 1; i <= n; ++i)Curhead[i] = head[i];
    u = src;
    while(dist[src] < n)
    {
        if(u == des)     // find an augmenting path
        {
            long long  augflow = INF;
            for(int i = src; i != des; i = edge[Curhead[i]].ver)
                augflow = min(augflow, edge[Curhead[i]].cap);
            for(int i = src; i != des; i = edge[Curhead[i]].ver)
            {
                edge[Curhead[i]].cap -= augflow;
                edge[edge[Curhead[i]].rev].cap += augflow;
                edge[Curhead[i]].flow += augflow;
                edge[edge[Curhead[i]].rev].flow -= augflow;
            }
            totalflow += augflow;
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
            long long  mindist = n;
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
    memset(head, -1, sizeof(head));
}
int mx[]={-1,1,0,0};
int my[]={0,0,-1,1};

int main()
{
    int T;
    int x, y, fg, i, j, k;
    int cas = 0;
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        init();
        src = n*m+1;
        des = n*m+2;
        for( i = 1; i <= n; i ++ )
            for( j = 1; j <= m; j ++ ){
                scanf("%d",&fg);
                if(fg == 1)    add( (i-1)*m+j, des, INF );
                if(fg == 2)    add( src, (i-1)*m+j, INF );
                for(k = 0; k < 4; k ++){
                    int tx,ty;
                    tx = i + mx[k];     ty = j + my[k];
                    if( tx >n || tx < 1  || ty > m || ty < 1 )    continue;
                    add( (i-1)*m+j, (tx-1)*m+ty, 1);
                }
            }
        n = des;
        rev_BFS();
        long long  ans = maxflow();
        printf("Case %d:\n%I64d\n", ++cas, ans);
    }
    return 0;
}
