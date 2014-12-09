#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int LEN = 150;
const int NUM = 20;
const int MAX = 0x7fffffff;

int mx[]={-1,-1,-1,0,0,0,1,1,1};
int my[]={-1,0,1,-1,0,1,-1,0,1};
int st[LEN];
int dp[LEN][NUM][NUM];
bool vis[LEN][NUM][NUM];
struct Triple{
    int l,x,y;
    Triple(int l1=0,int x1=0,int y1=0):l(l1),x(x1),y(y1){}
}tr1;
queue<Triple>Q;

void check(int l1,int x1,int y1,int l2,int x2,int y2)
{
    if(x2<1 || x2>10 || y2<1 || y2>10 || x2>=y2)    return;
    if(dp[l2][x2][y2]==-1 || dp[l2][x2][y2]>dp[l1][x1][y1]+1){
        dp[l2][x2][y2]=dp[l1][x1][y1]+1;
        if(!vis[l2][x2][y2]){
            vis[l2][x2][y2]=true;
            Q.push(Triple(l2,x2,y2));
        }
    }
}

char str[LEN];

int init()
{
    memset(dp,-1,sizeof(dp));
    memset(vis,0,sizeof(vis));
    while(!Q.empty())   Q.pop();
    Q.push(Triple(0,5,6));
    dp[0][5][6]=0;
    int n,i,j;
    n=strlen(str);
    int l1,x1,y1,l2,x2,y2;
    while(!Q.empty()){
        tr1=Q.front();  Q.pop();
        l1=tr1.l;    x1=tr1.x;   y1=tr1.y;
        vis[l1][x1][y1]=false;
        if(l1==n)   continue;
        l2=l1;
        for(i=0;i<9;i++){
            x2=x1+mx[i];    y2=y1+my[i];
            check(l1,x1,y1,l2,x2,y2);
        }
        if(x1==st[l1]){
            l2=l1+1;    x2=x1;
            for(i=-1;i<=1;i++){
                y2=y1+i;
                check(l1,x1,y1,l2,x2,y2);
            }
        }
        if(y1==st[l1]){
            l2=l1+1;    y2=y1;
            for(i=-1;i<=1;i++){
                x2=x1+i;
                check(l1,x1,y1,l2,x2,y2);
            }
        }
    }
    int res=-1;
    for(i=1;i<=10;i++)
        for(j=1;j<=10;j++)
            if(dp[n][i][j]!=-1 &&( dp[n][i][j]<res || res==-1 ))
                res=dp[n][i][j];
    return res;
}


int main()
{
    while(scanf("%s",str)!=EOF){
        for(int i=0,sz=strlen(str);i<sz;i++)    st[i]=( (str[i]=='0') ? 10 : (str[i]-'0') );
        printf("%d\n",init());
    }
    return 0;
}
