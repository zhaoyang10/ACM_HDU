#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
#define nMax 100010
#define cMax 35
bool vis[nMax],leaf[nMax];
vector<int> C;
vector<int> E[nMax];
queue<int> Q;
vector<double> ans;
double Left[cMax][cMax],Right[cMax][cMax];
double up[nMax],down[nMax],nlr[nMax];
int n;
double nn;
int in[nMax];

void init()
{
    int i,j;
    C.clear();    while(!Q.empty())    Q.pop();    ans.clear();
    for( i=1; i<=n; i++ )    E[i].clear(),leaf[i]=false,up[i]=0,down[i]=0,vis[i]=false,in[i]=0;
    memset( Right, 0, sizeof(Right) );
    memset( Left, 0, sizeof(Left) );
}

bool cmp( double p1, double p2 )    {    return p1>p2;    }

void dfs(int u,int fa)
{
    int i,sz=E[u].size(),v;
    for( i=0; i<sz; i++ ){
        v = E[u][i];
        if( !vis[v]  ||  fa == v )    continue;
        up[v] = up[u]/( 1.0 * ( sz - 1 ) ) + 1.0/ ( nn * sz );

        if( !vis[u] ){
        //    printf("loop:E[%d].sz = %d\tv = %d\n",u,sz,v);
        //    printf("up[%d] = %lf\tnlr[%d] = %lf\n",u,up[u],u,nlr[u]);
            up[v] += nlr[u]/( ( sz - 2 ) * 1.0 );
        }

        if( E[v].size() != 1 )    up[v] += ( down[u] - down[v] / ( 1.0 * ( E[v].size() - 1 ) ) - 1.0 / ( nn * E[v].size() ) ) / ( 1.0 * ( E[u].size() - 1 ) );
        else up[v] += ( down[u] - 1.0/nn ) / ( 1.0 * ( E[u].size() - 1 ) );
        //printf("up[%d] = %lf\n",v,up[v]);
        dfs( v, u );
    }
}

void dfs_circle(int u,int fa)
{
    //if( !C.empty() && u == C[0] )    return ;
    //printf("u = %d\n",u);
    int i,v,sz = E[u].size(), j, sz1 = C.size();
    C.push_back(u);
    for( i=0; i<sz; i++ ){
        v = E[u][i];
    //    printf("v = %d\n",v);
        if( vis[v] || v == fa )    continue;
        bool flag = false;
        for( j=0; j<sz1; j++)    if( C[j] == v ) {flag=true;    break;}
        if(flag)    continue;
    //    printf("v = %d\n",v);
        dfs_circle( v, u );
        return;
    }
}

int main()
{
    int u,v,sz,i,j;
    while(~scanf("%d",&n),n){
        init();        nn = 1.0*n;
        for( i=0; i<n; i++ ){
            scanf("%d%d",&u,&v);
            E[u].push_back(v);
            E[v].push_back(u);
            in[u] ++;     in[v] ++;
        }
        for( i=1; i<=n; i++ )        if( in[i] == 1 )    Q.push(i),leaf[i]=true;

        while(!Q.empty()){
            u = Q.front();    Q.pop();    vis[u] = true;
            if( leaf[u] ){
                down[u] = 0;    v = E[u][0];
                down[v] += 1.0/nn;
                in[v] --;
            }else{
                for( i=0,sz=E[u].size(); i<sz; i++ )    if(!vis[ E[u][i] ])    break;
                v = E[u][i];
                down[v] += down[u]/( 1.0 * ( E[u].size() - 1 ) ) + 1.0/( nn * E[u].size() ) ;
                in[v] --;
            }
            if( in[v] == 1 )    Q.push(v);
        }

        for( i=1; i<=n; i++ )    if( !vis[i] ){    dfs_circle(i, 0);    break;    }

        //for( i=1; i<=n; i++ )    printf("down[%d] = %lf\n",i,down[i]);

        for( i=0,sz=C.size(); i<sz; i++ ){
            Right[i][ (i+1)%sz ] = 1.0/( nn * E[ C[i] ].size() ) + down[ C[i] ] / ( 1.0 * ( E[ C[i] ].size() - 1 ) );
            for( j=2; j<sz; j++ )
                Right[i][ (i+j)%sz ] = Right[i][ (i+j-1)%sz ] /( 1.0 * ( E[ C[ (i+j-1)%sz ] ].size() - 1 ) );
            Left[i][ (i-1+sz)%sz ] = 1.0/( nn * E[ C[i] ].size() ) + down[ C[i] ] / ( 1.0 * ( E[ C[i] ].size() - 1 ) );
            for( j=2; j<sz; j++ )
                Left[i][ (i-j+sz)%sz ] = Left[i][ (i-j+1+sz)%sz ] /( 1.0 * ( E[ C[ (i-j+1+sz)%sz ] ].size() - 1 ) );
        }

/*        for( i=0; i<sz; i++ )
            for( j=0; j<sz; j++ )
                if( i != j )    printf("Left[%d][%d] = %lf\tRight[%d][%d] = %lf\n", C[i], C[j], Left[i][j], C[i], C[j], Right[i][j]);
*/
        for( i=0; i<sz; i++ ){
            //printf("up[%d] = %lf\n",C[i], up[ C[i] ]);
            for( j=0; j<sz; j++ )
                if( i!=j )    up[ C[i] ] += Right[j][i] + Left[j][i];
        //    printf(" up[%d] = %lf\n",C[i],up[C[i]]);
            up[ C[i] ] -= Right[ (i+1)%sz ][i] + Left[ (i-1+sz)%sz ][i];
            nlr[ C[i] ] = Right[ (i+1)%sz ][i] + Left[ (i-1+sz)%sz ][i];
            if( E[ C[i] ].size() == 2 )        ans.push_back( nlr[ C[i] ] );//printf("nlr[%d] = %lf\tup[%d] = %lf\n", C[i], nlr[C[i]], C[i], up[C[i]] );
            else    dfs( C[i], 0 );
        }

        for( i=1; i<=n; i++ )    if(leaf[i])    ans.push_back( up[i] );//printf("up[%d] = %lf\n",i,up[i]);
        sort( ans.begin(), ans.end(), cmp );
        double out = 0.0;
        for( i=0,sz=ans.size(); i<5 && i<sz; i++ )        out += ans[i];

        //for( i=0; i<sz; i++ )    printf("ans[%d] = %lf\n",i,ans[i]);
        printf("%.5lf\n",out);
    }
    return 0;
}
