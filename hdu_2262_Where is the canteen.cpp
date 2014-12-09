#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cmath>
using namespace std;
#define nMax 300
#define LEN 20
#define eps 1e-15
#define zero(a)  fabs(a)<eps
double a[nMax][nMax];
char str[LEN][LEN];
bool flag[LEN][LEN];
queue<int>Qx,Qy;
int mx[] = {0,0,-1,1};
int my[] = {-1,1,0,0};
int s,e,n,m;
void bfs()
{
    //printf("bfs\n");
    while(!Qx.empty())    Qx.pop();
    while(!Qy.empty())    Qy.pop();
    memset(flag,0,sizeof(flag));
    int i,j,x1,x2,y1,y2;
    for(i=0; i<n; i++)
        for(j=0; j<m; j++)
            if(str[i][j] == '$'){
                flag[i][j] = true;    //printf("i = %d\tj = %d\n",i,j);
                Qx.push(i);    Qy.push(j);
            }
    while(!Qx.empty()){
        x1 = Qx.front();    y1 = Qy.front();    Qx.pop();    Qy.pop();
        for(i=0; i<4; i++){
            x2 = x1 + mx[i];    y2 = y1 + my[i];    //printf("%d %d\n",x2,y2);
            if(x2 >= 0 && x2 < n && y2 >= 0 && y2 < m && !flag[x2][y2] && str[x2][y2] != '#'){
                flag[x2][y2] = true;
                Qx.push(x2);    Qy.push(y2);
            }
        }
    }
}



/*
bool gauss(int n){
    int i,j,k;
  //  printf("n = %d\n",n);
    for(i=0,j=0;i<n&&j<n;j++){
        for(k=i;k<n;k++)
            if(!zero(a[k][j]))
                break;
        if(k<n){
            if(i!=k)
            for(int r=j;r<=n;r++) swap(a[i][r],a[k][r]);
            double tt=1/a[i][j];
            for(int r=j;r<=n;r++)
                a[i][r]*=tt;
            for(int r=0;r<n;r++)
                if(r!=i){
                    for(int t=n;t>=j;t--)
                        a[r][t]-=a[r][j]*a[i][t];
                }
            i++;
        }
    }
    for(int r=i;r<n;r++)
        if(!zero(a[r][n]))
            return false;
    return true;
}
*/

bool gauss(int n)
{
    int i,j,k,mark,g;
    for(i=0,j=0; i<n && j<n; i++){
        mark = j;
        for(k=j+1; k<n; k++)    if(fabs(a[k][i]) > fabs(a[mark][i]))    mark = k;
        if(fabs(a[mark][i]) > eps){
            if(mark != j)    for(k=i; k<=n; k++)    swap(a[mark][k],a[j][k]);
            double tt = 1.0/a[j][i];
            for(k=i; k<=n; k++)    a[j][k]*=tt;
            for(k=0; k<n; k++)
                if(j != k  && fabs(a[k][i]) >= eps ){
                    for(g = n; g >= i; g--)    a[k][g] -= a[j][g] * a[k][i];
                }
            j++;
        }
    }
    for(; j<n; j++)    if( fabs(a[j][n]) > eps )    return false;
    return true;
}

int main()
{
    int i,j,id1,id2,cnt,x,y,k;
    //freopen("output.txt","w",stdout);
    while(~scanf("%d%d",&n,&m)){
        for(i=0; i<n; i++)    scanf("%s",str[i]);
        bfs();
        for(i=0; i<=n*m; i++)
            for(j=0; j<=n*m; j++)
                a[i][j] = 0;

        for(i=0; i<n; i++)
            for(j=0; j<m; j++){
                id1 = i*m+j;
                if(str[i][j] == '#')    continue;

                if(str[i][j] == '$'){
                    a[id1][id1] = 1;
                    a[id1][n*m] = 0;
                    continue;
                }

                if(str[i][j] == '@'){s = i;    e = j;}

                cnt = 0;

                for(k=0; k<4; k++){
                    x = i + mx[k];
                    y = j + my[k];
                    if(x>=0 && x<n && y>=0 && y<m && flag[x][y] && str[x][y] != '#'){
                        cnt ++;    id2 = x*m+y;
                        a[id1][id2] = 1;
                    }
                }

                a[id1][id1] = -1*cnt;
                a[id1][n*m] = -1*cnt;
            }

            if(flag[s][e] && gauss(n*m)){
                for(i=0; i<n*m; i++)
                    if(zero(a[i][s*m+e] - 1)){
                        printf("%.6f\n",a[i][n*m]);
                        break;
                    }
            }else puts("-1");

    }
    return 0;
}
