#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
#define N 33010
#define ll long long
#define MOD 119
const int maxn=N;

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

/*求卷积 */
void Conv(comp *a,comp *b,int len){
    // 傅里叶正变换  分别对相乘的两个系数进行运算
    FFT(a,len,1);
    FFT(b,len,1);
    for (int i=0;i<len;i++)
        a[i]=a[i]*b[i];

    //已得到 点值表示法，  转化为系数表示法
    FFT(a,len,-1);
}


comp f1[maxn],f2[maxn];
char s1[maxn],s2[maxn];
int l, a, b, q, p, L;

void run(int *s1, int *s2){
    l = 1;
    int i;
    while (l < L*2) l = l<<1;       //printf("l = %d\n", l);
    for (i=0;i<L;i++) f1[i]=comp(s1[i],0.0);
    for (i=L;i<l;i++) f1[i]=comp(0.0,0.0);
    for (i=0;i<L;i++) f2[i]=comp(s2[i],0.0);
    for (i=L;i<l;i++) f2[i]=comp(0.0,0.0);
    Conv(f1,f2,l);    //FFT卷积相当于不进位乘法
    for (i = 0; i < l; i++)
            s1[i] = f1[i].r+0.5;
    for (i = 0; i < l; i ++)    s1[i] %= MOD;
    //for(i = 0; i < l; i ++)
    //    if(s1[i] < 0)   printf("fft : s1[%d] = %d\n", i, s1[i]);
    //for(i = 0; i < l; i ++)
    //    printf("%d :%d  ", i, s1[i]);
    //puts("");
}

void mul(int *s1, int *s2)
{
    run(s1, s2);

    int i;
    //for(i = 0; i < l; i ++)    printf("%d :%d  ", i, s1[i]);puts("");
    for(i = 2 * L - 1; i >= L; i --)
    {
        if(!s1[i])  continue;
      //  if(s1[i] < 0)   printf("!!s1[%d] = %d\n", i, s1[i]);
        s1[i - p] = (s1[i - p] + a * s1[i]) % MOD;
        s1[i - q] = (s1[i - q] + b * s1[i]) % MOD;
        s1[i] = 0;
    }
    for(i = 0; i < L; i ++) s1[i] %= MOD;

}

int res[N], mat[N], mati[N];
void qpow(int n)
{
    memset(res, 0, sizeof(res));    res[0] = 1;
    memset(mat, 0, sizeof(mat));    mat[1] = 1;
    while(n)
    {
        if(n & 1)   mul(res, mat);
        mul(mat, mat);
        n >>= 1;
    }
    //puts("haha");
}

int main()
{
    int n, ans, i;
   // freopen("1004.in", "r", stdin);
    //freopen("1004_2.out", "w", stdout);
    while(~scanf("%d%d%d%d%d", &n, &a, &b, &p, &q))
    {
        L = max(p, q) + 1;
        a %= MOD;   b %= MOD;
        //printf("\na = %d\tb = %d\n", a, b);
        qpow(n);


        mati[0] = 1;
        for(i = 1; i < L; i ++)
        {
            mati[i] = 0;
            if(i > p)   mati[i] += a * mati[i - p];
            else        mati[i] += a;
            if(i > q)   mati[i] += b * mati[i - q];
            else        mati[i] += b;
            mati[i] %= MOD;
        }
        ans = 0;
        for(i = 0; i < L; i ++) ans = (ans + mati[i] * res[i]) % MOD;
        printf("%d\n", ans);
    }
    return 0;
}
