#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
#define ll long long
#define Mod  100
ll Pow(ll x,ll t){
    if(t==0)  return 1ll;
    if(t==1)  return x%Mod;
    ll temp=Pow(x,t>>1);
    if(t&1)  return ((temp*x)%Mod*temp)%Mod;
    else return temp*temp%Mod;
}


int main()
{
    int T,i,j,k;
    ll ans,n;
    while(scanf("%d",&T)!=EOF && T){
        for(k=1;k<=T;k++){
            scanf("%I64d",&n);
            ans=(Pow(2,n-1)+Pow(4,n-1))%Mod;
            printf("Case %d: %I64d\n",k,ans);
        }
        printf("\n");
    }
    return 0;
}
