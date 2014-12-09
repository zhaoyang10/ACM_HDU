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
#define N 1000
ll a[N];
int n;
ll mod,Mod;
vector<ll>ans[2];

bool check(ll x)
{
    int i,j;
    ll res = 0;
    ll t;
    //printf("x = %I64d\n",x);
    for(i=n; i>=0; i--)
    {
        t = a[i];
       // printf("t = %I64d\n",t);
        for(j=1; j<=i; j++) t*=x,t%=(Mod*mod);

        res += t;
       // printf("t = %I64d\tres = %I64d\n",t,res);
        res %= (Mod*mod);
    }
    bool flag = (res == 0);
    //if(flag)    printf("x = %I64d\tres = %I64d\n",x,res);
    return flag;
}

int main()
{
    int cas,T,i,now,p,sz,j,k;

    scanf("%d",&T);
    for(cas = 1; cas <= T; cas ++)
    {
        scanf("%d",&n);
        for(i=n; i>=0; i--) scanf("%I64d",a+i);
        scanf("%I64d",&mod);
        for(i=0; i<2; i++)  ans[i].clear();
        ans[0].push_back(0);
        Mod = 1;
        for(i=1; i<=2; i++)
        {
           // printf("Mod = %I64d\n",Mod*mod);

            now = i&1;  p = now^1;
            ans[now].clear();
            sz = ans[p].size();
            if(sz == 0)
            {
                ans[now].clear();
                break;
            }
            for(j=0; j<sz; j++)
                for(k=0; k<mod; k++)
                    if(check( (ans[p][j] + k * Mod)  ))
                        ans[now].push_back(ans[p][j]+k*Mod);

            Mod *= mod;



        }
        printf("Case #%d: ",cas);

        if(ans[0].size()==0)    puts("No solution!");
        else                    printf("%I64d\n",ans[0][0]);
    }
    return 0;
}
