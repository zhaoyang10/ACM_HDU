#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
using namespace std;
const int nMax = 55;
const int tMax = 8;
int mp[nMax][nMax],f[tMax],sl[tMax],Pas[nMax],Att[nMax];
int dp[1<<tMax][1<<tMax][nMax];
bool in[1<<tMax][1<<tMax][nMax];

struct Triple{
    int att,pas,u;
    Triple(int a=0,int p=0,int t=0):att(a),pas(p),u(t){}
}tri;

queue<Triple> Q;

int main()
{
    int T,ca,i,j,k,u,v,w,att,pas,K,n,m,temp;
    scanf("%d",&T);
    for(ca=1;ca<=T;ca++){
        scanf("%d%d%d",&n,&m,&K);
        memset(mp,127,sizeof(mp));
        memset(Pas,0,sizeof(Pas));
        memset(Att,0,sizeof(Att));
        temp=mp[0][0];
        while(m--){
            scanf("%d%d%d",&u,&v,&w);    u--,v--;
            mp[u][v]=mp[v][u]=min(mp[u][v],w);
        }
        for(k=0;k<n;k++)    for(i=0;i<n;i++)    for(j=0;j<n;j++)    
        if(mp[i][k]!=temp && mp[k][j]!=temp && mp[i][j]>mp[i][k]+mp[k][j])    mp[i][j]=mp[i][k]+mp[k][j];
        for(i=0;i<n;i++)    mp[i][i]=0;
/*        
        for(i=0;i<n;i++){
            for(j=0;j<n;j++)    printf(" %d ",mp[i][j]);
            puts("");
        }
*/        
        for(i=0;i<K;i++){
            scanf("%d%d%d%d",&u,sl+i,f+i,&m);    u--;    //printf("sl[%d]=%d\tf[%d]=%d\n",i,sl[i],i,f[i]);
            Att[u]|=(1<<i);    
            while(m--){        scanf("%d",&u);    u--;    Pas[u]|=(1<<i);    }
        }
        
//        for(i=0;i<n;i++)    printf("Att[%d]=%d\tPas[%d]=%d\n",i,Att[i],i,Pas[i]);
        
        memset(dp,127,sizeof(dp));
        memset(in,0,sizeof(in));
        dp[0][0][0]=0;
        int att1,pas1,tmp,att2,pas2,tmp2;
        while(!Q.empty())    Q.pop();
        Q.push(Triple(0,0,0));
        while(!Q.empty()){
            tri=Q.front();    Q.pop();
            u=tri.u;    att=tri.att;    pas=tri.pas;    in[att][pas][u]=false;
    //        printf("\ndp[%d][%d][%d]=%d\t",att,pas,u,dp[att][pas][u]);
            for(v=0;v<n;v++){
                tmp=dp[att][pas][u]+mp[u][v];
                if(  (Att[v]&(~att)) || ( (Pas[v]|pas)&(~att) ) ){
                    pas1=(Pas[v]|pas);    att1=(Att[v] & (~att));
                    if(dp[att][pas1&(~att)][v]>tmp){
                        dp[att][pas1&(~att)][v]=tmp;
                        if(!in[att][pas1&(~att)][v]){
        //                    printf("queue1:dp[%d][%d][%d]=%d\t",att,pas1&(~att),v,dp[att][pas1&(~att)][v]);
                            in[att][pas1&(~att)][v]=true;
                            Q.push(Triple(att,pas1&(~att),v));
                        }
                    }
                    if(att1){    
                        for(i=0;i<K;i++){    
                            if( (att1>>i)&1 & ((~att)>>i) ){
                                att2=att|(1<<i);    pas2=pas1&(~att2);    
                                tmp2=tmp+ ( ( ( ( pas1>>i ) & 1 ) == 1 )?f[i]:sl[i] );
                //                printf("tmp2=%d\ttmp=%d\tf[%d]=%d\tsl[%d]=%d\n",tmp2,tmp,i,f[i],i,sl[i]);
                                if(dp[att2][pas2][v]>tmp2){
                                    dp[att2][pas2][v]=tmp2;
                            
                                    if(!in[att2][pas2][v]){
                    //                    printf("queue2:dp[%d][%d][%d]=%d\t",att2,pas2,v,dp[att2][pas2][v]);
                                        Q.push(Triple(att2,pas2,v));
                                        in[att1][pas1][v]=true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        for(i=1;i<n;i++)    dp[(1<<K)-1][0][0]=min(dp[(1<<K)-1][0][0],dp[(1<<K)-1][0][i]+mp[i][0]);
        printf("Case #%d: %d\n",ca,dp[(1<<K)-1][0][0]);
    }
    system("pause");
    return 0;
}
