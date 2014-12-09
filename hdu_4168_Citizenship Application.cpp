#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<map>
using namespace std;
#define dMax  1000010

int sum[dMax],a[dMax],Mon[3],Dat[3],Yea[3];
bool is_1[dMax];
int tot=1;
int St[3];
struct Triple{
    int M,D,Y;
    Triple(int _M=0,int _D=0,int _Y=0):M(_M),D(_D),Y(_Y){};
    bool operator<(const Triple & T)const{
        if(M!=T.M)  return M<T.M;
        if(D!=T.D)  return D<T.D;
        return Y<T.Y;
    }
}Find[dMax];

map<Triple,int>mp;

void init()
{
    int i,j,k;
    for(i=1900;i<=3000;i++)
        for(j=1;j<=12;j++){
            if(j==1 || j==3 || j==5|| j==7 || j==8 || j==10 || j==12){
                for(k=1;k<=31;k++){
                    mp[Triple(j,k,i)]=tot;
                    Find[tot]=Triple(j,k,i);
                    tot++;
                }
            }else if( j==4 || j==6 || j==9 || j==11 ){
                for(k=1;k<=30;k++){
                    mp[Triple(j,k,i)]=tot;
                    Find[tot]=Triple(j,k,i);
                    tot++;
                }
            }else{
                if((i%400==0) || (  i%100!=0 && i%4==0) ){
                    for(k=1;k<=29;k++){
                        mp[Triple(j,k,i)]=tot;
                        Find[tot]=Triple(j,k,i);
                        tot++;
                    }
                }else{
                    for(k=1;k<=28;k++){
                        mp[Triple(j,k,i)]=tot;
                        Find[tot]=Triple(j,k,i);
                        tot++;
                    }
                }
            }
        }
}

void Deal()
{
    int he = St[0] , ta , i , j , End = St[1]+100000 , m ;
    memset(a,0,sizeof(a));
    for( i = St[0]; i<St[1]; i++)   a[i]=1;
    for( i = St[1]; i<End; i++)   a[i]=2;
    scanf("%d",&m);
    while(m--){
        scanf("%d/%d/%d%d/%d/%d",Mon,Dat,Yea,Mon+1,Dat+1,Yea+1);
        he = mp[Triple(Mon[0],Dat[0],Yea[0])];
        ta = mp[Triple(Mon[1],Dat[1],Yea[1])];
        for(i=he; i<=ta; i++)    a[i] = 0;
    }
    sum[St[1]-1460-1]=0;
    for(i=St[1]-1460;i<End;i++)    sum[i] = sum[i-1] + a[i];
    for(i=St[1]-1460;;i++){
        if((sum[i+1460-1]-sum[i-1])/2>= 1095) break;
    }
    Triple ans = Find[i+1460];
    printf("%d/%d/%d\n",ans.M,ans.D,ans.Y);
}



int main()
{
    init();
    //printf("tot=%d\n",tot);
    while(scanf("%d/%d/%d",Mon,Dat,Yea)!=EOF){
        scanf("%d/%d/%d",Mon+1,Dat+1,Yea+1);
        St[0] = mp[Triple(Mon[0],Dat[0],Yea[0])];
        St[1] = mp[Triple(Mon[1],Dat[1],Yea[1])];
        Deal();
    }
    return 0;
}
