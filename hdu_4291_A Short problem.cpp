#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
#define nMax 5
#define ll long long
#define MOD0 1000000007
#define MOD1 222222224
#define MOD2 183120
#define MOD3 240
ll g[nMax];
ll Mat[nMax][nMax],a[nMax];

void Multi(ll b[nMax],ll Mul[nMax][nMax],ll x,int mod)
{
    ll tmp[nMax][nMax],i,j,k;
    while(x)
    {
        if(x&1){
            ll t0= Mul[0][0] * b[0] + Mul[0][1] * b[1];
            ll t1 = Mul[1][0] * b[0] + Mul[1][1] * b[1]; b[1] = t1 % mod;b[0] = t0 % mod;

        }
        for(i=0; i<2; i++)
            for(j=0; j<2; j++){
                tmp[i][j] = 0;
                for(k=0; k<2; k++){
                    tmp[i][j] += Mul[i][k] * Mul[k][j];
                    tmp[i][j] %= mod;
                }
            }
        for(i=0; i<2; i++)
            for(j=0; j<2; j++){
                Mul[i][j] = tmp[i][j];
//                printf("%I64d ",Mul[i][j]);
            }
        //printf("x = %I64d\tb[0] = %I64d\tb[1] = %I64d\n",x,b[0],b[1]);
        x >>= 1;
    }

}

ll get(ll x,int mod)
{
    if( x <= 1 )    return x;
    a[0] = 1;    a[1] = 0;
    Mat[0][0] = 3;    Mat[0][1] = 1;
    Mat[1][0] = 1;    Mat[1][1] = 0;
    //printf("x = %I64d\n",x);
    Multi(a,Mat,x-1,mod);
    //printf("a[%I64d] = %I64d\n",x,a[0]);
    return a[0];
}

int main()
{
    ll i,n,k1=0,k2=1,k3;
    //printf("10 = %I64d\n",k3);
    while(~scanf("%I64d",&n)){
        n %= MOD3;
        n = get(n, MOD2);
        //printf("n = %I64d\n",n);
        n = get(n, MOD1);
        //printf("n = %I64d\n",n);
        n = get(n, MOD0);
        printf("%I64d\n",n);
    }

}
