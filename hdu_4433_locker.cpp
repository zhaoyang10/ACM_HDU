#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
#define nMax 1010
#define BIT    10

int dp[nMax][BIT][BIT];
bool vis[nMax][BIT][BIT];
char s1[nMax],s2[nMax];
int n1[nMax],n2[nMax];
int len;
queue<int>Q1,Q2,Q3;

void Relax(int tmp, int llen, int m, int x1, int x2)
{
    int i,j,tx1,tx2;
    for(i=0;i<=m;i++)
        for(j=0;j<=i;j++){
            tx1  = (x1 + i) % 10;    tx2 = (x2 + j) % 10;
            //printf("len = %d\ttx1 = %d\ttx2 = %d\n",llen,tx1,tx2);
            if(dp[llen][tx1][tx2] == -1 || dp[llen][tx1][tx2] > tmp + m){
                dp[llen][tx1][tx2] = tmp + m;
                if(!vis[llen][tx1][tx2]){
                    vis[llen][tx1][tx2]    = true;
                    Q1.push(llen);    Q2.push(tx1);    Q3.push(tx2);
                }
            }
        }
    m = (10 - m)%10;
    for(i=0;i<=m;i++)
        for(j=0;j<=i;j++){
            tx1 = (x1 - i + 10) % 10;    tx2 = (x2 - j + 10) % 10;
            if(dp[llen][tx1][tx2] == -1 || dp[llen][tx1][tx2] > tmp + m){
                dp[llen][tx1][tx2] = tmp + m;
                if(!vis[llen][tx1][tx2]){
                    vis[llen][tx1][tx2]    = true;
                    Q1.push(llen);    Q2.push(tx1);    Q3.push(tx2);
                }
            }
        }
}

int DP()
{
    memset(dp,-1,sizeof(dp));
    memset(vis,false,sizeof(false));
    while(!Q1.empty())    Q1.pop(),Q2.pop(),Q3.pop();

    Relax(0,0,(n2[0] - n1[0] + 10)% 10,n1[1],n1[2]);
    int x1,x2,x3,ans = -1;
    while(!Q1.empty()){
        x1 = Q1.front();    Q1.pop();
        x2 = Q2.front();    Q2.pop();
        x3 = Q3.front();    Q3.pop();
        vis[x1][x2][x3] = false;
        //if(dp[x1][x2][x3] <= 4)    printf("dp[%d][%d][%d] = %d\n",x1,x2,x3,dp[x1][x2][x3]);
        //system("pause");
        if(x1 == len - 1){
            if(ans == -1 || ans > dp[x1][x2][x3])    ans = dp[x1][x2][x3];
        }else    Relax(dp[x1][x2][x3],x1+1,(n2[x1+1] - x2 + 10) % 10,x3,n1[x1+3]);
    }
    return ans;
}

int main()
{
    int i;
    while(~scanf("%s%s",s1,s2)){
        len = strlen(s1);
        for(i=0;i<len;i++){    n1[i] = s1[i] - '0';    n2[i] = s2[i] - '0';}
        n1[len] = n2[len] = 0;
        if(len>1)    printf("%d\n",DP());
        else    printf("%d\n",min((n2[0] - n1[0] + 10) % 10, (n1[0] - n2[0] + 10) % 10));
    }
    return 0;
}
