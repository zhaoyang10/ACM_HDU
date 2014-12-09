#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long int64;
const int MOD=1000000007;
const int64 LIMIT = (int64)MOD*MOD;
const int MAX_N = 410;
int64 mp[MAX_N],res[MAX_N],f[MAX_N],ff[MAX_N],aa[MAX_N],bb[MAX_N],ans,n;
int u,d,a[MAX_N],b[MAX_N],L;
void mul(int64 a[MAX_N],int64 sb[MAX_N])
{
//    for(int i=0;i<L;++i) cout<<a[i]<<' '; cout<<endl;
//    for(int i=0;i<L;++i) cout<<sb[i]<<' '; cout<<endl;
    for(int i=0;i<2*L;++i) aa[i]=a[i],bb[i]=sb[i],a[i]=0;
    for(int i=0;i<L;++i)
      for(int j=0;j<L;++j)
        a[i+j]=(a[i+j]+aa[i]*bb[j])%MOD;
    for(int i=2*L-1;i>=L;--i)
    {
        for(int j=1;j<=d;++j)
          a[i-b[j]]=(a[i-b[j]]+a[i]*f[b[j]])%MOD;
        a[i]=0;
    }
//    for(int i=0;i<L;++i) cout<<a[i]<<' '; cout<<endl;
}
void spow(int64 n)
{
    memset(res,0,sizeof(res)); res[0]=1;
    memset(mp,0,sizeof(mp)); mp[1]=1;
    for(;n;n>>=1,mul(mp,mp))
      if(n&1) mul(res,mp);
    ans=0; for(int i=0;i<L;++i) ans=(ans+res[i]*ff[i])%MOD;
}
int main()
{
//    freopen("in.txt","r",stdin);
    while(scanf("%I64d",&n)!=EOF)
    {
        L=2;
        scanf("%d",&u); for(int i=1;i<=u;++i) scanf("%d",&a[i]);
        scanf("%d",&d); for(int i=1;i<=d;++i) scanf("%d",&b[i]),L=max(L,b[i]);
        memset(f,0,sizeof(f)); f[0]=1;
        for(int i=1;i<=L;++i)
          for(int j=1;j<=u;++j)
            if(i>=a[j])
              f[i]=(f[i]+f[i-a[j]])%MOD;
        memset(ff,0,sizeof(ff)); ff[0]=1;
        for(int i=1;i<L;++i)
        {
            for(int j=1;j<=d;++j)
              if(i>=b[j]) ff[i]=(ff[i]+ff[i-b[j]]*f[b[j]])%MOD;
        }
        spow(n);
        printf("%I64d\n",ans);
    }
    return 0;
}
