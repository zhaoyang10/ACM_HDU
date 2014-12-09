#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<set>
#include<map>
#include<cmath>
using namespace std;
#define eps 1e-8
#define N 7
#define M 7


int d[N][M],e[N][M],vis[N][M];
int x[4] = {0,0,1,-1};
int y[4] = {1,-1,0,0};
int n,m,t;

char s[M];
queue<int>qx,qy;


bool outbd(int tx,int ty)
{
    if(tx < 0 || tx >= n)   return true;
    if(ty < 0 || ty >= m)   return true;
    return false;
}

void spfa(int sx,int sy,int ex,int ey){
    memset(vis,0,sizeof(vis));
    memset(d,-1,sizeof(d));
    d[sx][sy] = 0;
    qx.push(sx);   qy.push(sy);
    int tx[2],ty[2],i,td;
    while(!qx.empty()){
        tx[0] = qx.front();  qx.pop();
        ty[0] = qy.front();  qy.pop();
        vis[tx[0]][ty[0]] = 0;
        td = d[tx[0]][ty[0]] + 1;
        for(i=0; i<4; i++){
            tx[1] = tx[0] + x[i];
            ty[1] = ty[0] + y[i];
            if(outbd(tx[1],ty[1]) || e[tx[1]][ty[1]])   continue;
            if(td < d[tx[1]][ty[1]] || d[tx[1]][ty[1]] == -1){
                d[tx[1]][ty[1]] = td;
                if(!vis[tx[1]][ty[1]]){
                    qx.push(tx[1]);
                    qy.push(ty[1]);
                    vis[tx[1]][ty[1]]=1;
                }
            }
        }
    }
}

bool dfs(int now,int nx,int ny,int tx,int ty){
    if(now == t && nx == tx && ny == ty)    return true;
    if(nx == tx && ny == ty)    return false;
    int i,tmx,tmy;
    for(i=0; i<4; i++){
        tmx = nx + x[i];
        tmy = ny + y[i];
        if(outbd(tmx,tmy) || e[tmx][tmy] || vis[tmx][tmy])  continue;
        vis[tmx][tmy] = 1;
        if(dfs(now+1,tmx,tmy,tx,ty))    return true;
        vis[tmx][tmy] = 0;
    }
    return false;
}

int main()
{
    int st,en,i,j;
    while(~scanf("%d%d%d",&n,&m,&t)){
        if(!(n || m || t))  break;
        memset(e,0,sizeof(e));
        for(i=0; i<n; i++){
            scanf("%s",s);
            for(j=0; j<m; j++)
                if(s[j] == 'X') e[i][j]=1;
                else   if(s[j] == 'S')  st = i*m+j;
                else   if(s[j] == 'D')  en = i*m+j;
        }
        spfa(st/m,st%m,en/m,en%m);
        if(d[en/m][en%m] == -1 || ((d[en/m][en%m] ^ t) & 1) || d[en/m][en%m] > t){
            puts("NO");
            continue;
        }
        if(d[en/m][en%m] == t){
            puts("YES");
            continue;
        }
        memset(vis,0,sizeof(vis));
        vis[st/m][st%m] = 1;
        if(dfs(0,st/m,st%m,en/m,en%m))  puts("YES");
        else puts("NO");
    }

    return 0;
}
