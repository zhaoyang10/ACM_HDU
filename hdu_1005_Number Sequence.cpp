#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
#define N 3
#define ll int
#define MOD 7
ll Mat[N][N],a[N];
ll A,B;


void Multi(ll Mul[N][N],ll b[N],ll x)
{
    ll tmp[N][N],t1,t2;
    int i,j,k;
    while(x){
        if( x&1 ){
            t1 = Mul[0][0] * b[0] + Mul[0][1] * b[1];
            t2 = Mul[1][0] * b[0] + Mul[1][1] * b[1];
            b[0] = t1%MOD;    b[1] = t2%MOD;
        }
        for(i=0; i<2; i++)
            for(j=0; j<2; j++){
                tmp[i][j] = 0;
                for(k=0; k<2; k++)
                    tmp[i][j] = (tmp[i][j] + Mul[i][k]*Mul[k][j])%MOD;
            }
        for(i=0; i<2; i++)
            for(j=0; j<2; j++)
                Mul[i][j] = tmp[i][j];
        x >>= 1;
    }
}

ll get(ll n)
{
    if(n == 1LL)    return 1LL;
    if(n == 2LL)    return 1LL;
    n -= 2;
    a[0] = 1;    a[1] = 1;
    Mat[0][0] = A;        Mat[0][1] = B;
    Mat[1][0] = 1LL;    Mat[1][1] = 0LL;
    Multi(Mat,a,n);
    return a[0];
}

int main()
{
    ll n;
    while(~scanf("%d%d%d",&A,&B,&n),(A||B||n)){
        printf("%d\n",get(n));
    }
    return 0;
}
