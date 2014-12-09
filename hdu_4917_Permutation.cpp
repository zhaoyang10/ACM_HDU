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
#define ll long long
#define ull unsigned long long
#define MOD 1000000007
#define N 100
#define STATE (1<<21)
int c[N][N];
int dp[STATE];
int u[N],v[N],fa[N],p[N],idx[N];
bool vp[N],vis[N];
int n,m;

void init()
{
    int i,j;
    for(i=0; i<N; i++)   c[i][0]=1,c[i][i]=1;
    for(i=2; i<N; i++)
        for(j=1; j<i; j++)
            c[i][j] = (c[i-1][j-1] + c[i-1][j]) % MOD;
}

int getfa(int u){   return fa[u]==u? u: (fa[u]=getfa(fa[u])); }

int dfs(int nu)
{
    if(vp[nu])   return p[idx[nu]];
    int i;
    for(i=0; i<m; i++)
        if(u[i] == nu)
            p[idx[nu]] |= dfs(v[i]);
    vp[nu]=true;

    //printf("dfs: nu = %d\tp[%d] = %d\n",nu,idx[nu],p[idx[nu]]);

    return p[idx[nu]];
}

void update(int& x,int y)
{
    x += y;
    if(x >= MOD)    x -= MOD;
}

int main()
{
    register int i,j,num,tot,k;
    init();
    int ans,cas=1;
   // freopen("1007.in","r",stdin);
   // freopen("1007-3.out","w",stdout);
    while(~scanf("%d%d",&n,&m))
    {
        for(i=0; i<n; i++)  fa[i]=i;
        for(i=0; i<m; i++)
        {
            scanf("%d%d",u+i,v+i);
            u[i]--;     v[i]--;
            if(getfa(u[i]) != getfa(v[i]))  fa[fa[u[i]]] = getfa(v[i]);
        }

      /*  printf("Case %d: \n",cas++);
        printf("%d\t%d\n",n,m);
        for(i=0; i<m; i++)
        {
            printf("%d %d\n",u[i],v[i]);
        }
*/
        memset(vis,0,sizeof(vis));
        ans = 1;  num = n;

        for(i=0; i<n; i++)
            if(!vis[i])
            {
                tot = 0;
                memset(idx,-1,sizeof(idx));
                memset(p,0,sizeof(p));
                for(j=0; j<n; j++)
                    if(!vis[j] && getfa(i) == getfa(j))
                    {
                        idx[j] = tot++;
                        vis[j] = true;

                       // printf(" j = %d\t tot = %d\n",j,tot);
                    }
                for(j=0; j<m; j++)
                    if(idx[u[j]]!=-1 && idx[v[j]]!=-1)
                    {
                        p[idx[u[j]]] |= (1 << idx[v[j]]);
                    }

               // for(i=0; i<tot; i++)    printf("--p[%d] = %d\n",i,p[i]);

                memset(vp,0,sizeof(vp));
                for(j=0; j<n; j++)
                    if(!vp[j]  && idx[j]!=-1)
                    {
                        dfs(j);
                    }

              //  for(i=0; i<tot; i++)    printf("++p[%d] = %d\n",i,p[i]);

                memset(dp,0,sizeof(dp));
                dp[0]=1;
                int state = 1<<tot;
               // printf("tot = %d\tstate-1 = %d\n",tot,state-1);
                for(j=0; j<state; j++)
                    for(k=0; k<tot; k++)
                    {
                 //       printf("p[%d] = %d\n",k,p[k]);
                        if( ( (j>>k) & 1 ) == 0 && (j | p[k]) == j && dp[j])
                        {
                   //         printf("-dp[%d] = %d\n",j,dp[j]);
                            update(dp[j|(1<<k)],dp[j]);
                            //dp[j | (1 << k)] = ( dp[j | (1 << k)] + dp[j] ) % MOD;
                   //         printf("-dp[%d] = %d\n",j|(1<<k),dp[j|(1<<k)]);
                        }
                    }
              //  printf("dp[%d] = %d\n",state-1,dp[state-1]);
                ans = (ll)c[num][tot] * ans % MOD * dp[state-1] % MOD;
              //  printf("ans = %d\n",ans);
                num -= tot;
            }
        printf("%d\n",ans);
    }
    return 0;
}
