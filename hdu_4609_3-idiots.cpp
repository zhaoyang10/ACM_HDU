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
#define eps 1e-11
#define ll long long
#define ull unsigned long long
#define MOD 1000000007
#define N 300000
const double PI=acos(-1.0);

struct comp{
    double r,i;
    comp(double _r=0,double _i=0){
        r=_r;
        i=_i;
    }
    comp operator + (const comp &x){
        return comp(r+x.r,i+x.i);
    }
    comp operator - (const comp &x){
        return comp(r-x.r,i-x.i);
    }

    comp operator * (const comp &x){
        return comp(r*x.r-i*x.i,r*x.i+i*x.r);
    }
};

/*雷德算法--倒位序*/
void Rader(comp *F,int len){
    int i,j,k;
    for(i=1,j=len/2;i<len-1;i++){
        if(i<j) swap(F[i],F[j]);
        k=len/2;
        while(j>=k){
            j-=k;
            k>>=1;
        }
        if(j<k) j+=k;
    }
}

/*FFT实现*/
void FFT(comp *f,int len,int on){
    Rader(f,len);
    for(int h=2;h<=len;h<<=1) {   /*分治后计算长度为h的DFT*/
        comp wn(cos(-on*2*PI/h),sin(-on*2*PI/h));    /*单位复根 e^(2*pi/m) 用欧拉公式展开*/
        for(int j=0;j<len;j+=h){
            comp w(1,0);
            for(int k=j;k<j+h/2;k++){/*旋转因子*/
                comp u=f[k];
                comp t=w*f[k+h/2];
                f[k]=u+t; /*蝴蝶操作合并*/
                f[k+h/2]=u-t;
                w=w*wn;   /*更新旋转因子*/
            }
        }
    }
    if(on==-1) for(int i=0;i<len;i++)
        f[i].r/=len;
}

comp f1[N],f2[N];
ll ans[N], sum[N];
int l[N], num[N];


int main(){
    int T, n, i, j, k, t, m, len;
    ll tans, tot;
    scanf("%d", &T);
    while(T --)
    {
        scanf("%d", &n);
        m = 0;
        memset(num, 0, sizeof(num));
        for(i = 0; i < n; i ++)
        {
            scanf("%d", l + i);
            num[l[i]] ++;
            m = max(m, l[i]);
        }
        sort(l, l + n);
        for(i = 0; i <= m; i ++)
        {
            f1[i] = comp(num[i]*1.0, 0.0);
        }
        m <<= 1;
        m ++;
        len = 1;
        while(len < m)  len <<= 1;

        for(; i < len; i ++)
        {
            f1[i] = comp(0.0, 0.0);
        }
        FFT(f1, len, 1);
        for(i = 0; i < len; i ++)
            f1[i] = f1[i] * f1[i];
        FFT(f1, len, -1);
        memset(ans, 0, sizeof(ans));
        for(i = 0; i < len; i ++)
            ans[i] = f1[i].r + 0.5;
        for(i = 0; i < n; i ++)
            ans[l[i] + l[i]] --;
        for(i = 0; i < m; i ++)
            ans[i] >>= 1;
        sum[0] = ans[0];
        for(i = 1; i < m; i ++)
            sum[i] = sum[i - 1] + ans[i];
        m --;
        tans = 0;
        for(i = 0; i < n; i ++)
        {
            tans += sum[m] - sum[l[i]];
            tans -= n - 1;
            tans -= (ll)(n - i - 1) * i;
            tans -= (ll)(n - i - 1) * (n - i - 2) / 2;
        }
        tot = (ll) n * (n - 1) * (n - 2) / 6;

        printf("%.7lf\n", 1.0 * tans / tot);
    }
    return 0;
}
