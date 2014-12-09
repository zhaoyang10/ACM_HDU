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
#define N 1000010
ll p,phi;
int pri[N];
bool vis[N];
int tot;

struct Matrix{
    ll m[2][2];
    void init()
    {
        m[0][0] = 1;
        m[1][0] = 1;
        m[0][1] = 1;
        m[1][1] = 0;
    }
    void E()
    {
        for(int i=0; i<2; i++)
            for(int j=0; j<2; j++)
                m[i][j] = (i == j);
    }
};

void init()
{
    int i,j;    tot = 0;
    memset(vis,0,sizeof(vis));
    for(i=2; i<N; i++)
    {
        if(vis[i])  continue;
        pri[tot++] = i;
        for(j=2*i; j<N; j+=i)
            vis[j]=true;
    }
}

ll eular(ll p)
{
    int i;
    ll t = p;
    for(i=0; pri[i] * pri[i] <= t & i < tot; i++)
    {
        if(t % pri[i] == 0)
        {
            p = p - p / pri[i];
            while(t % pri[i] == 0)  t /= pri[i];
        }
    }
    if(t > 1)   p = p - p / t;
    return p;

/*
    ll i,t = p;
    for(i = 2; i * i <= t; i ++)
    {
        if(t % i == 0)
        {
            while(t % i == 0)   t /= i;
            p = p - p / i;
        }
    }
    if(t > 1)   p = p - p / t;
    return p;
    */
}

void MatMul(Matrix &mat0, Matrix mat1, ll mod)
{
    Matrix mat2;
    for(int i=0; i<2; i++)
        for(int j=0; j<2; j++)
        {
            mat2.m[i][j] = 0;
            for(int k=0; k<2; k++)
            {
                mat2.m[i][j] += mat0.m[i][k] * mat1.m[k][j];
                if(mat2.m[i][j] >= mod)
                    mat2.m[i][j] = mat2.m[i][j] % mod + mod;
            }
        }
    mat0 = mat2;
}

Matrix MatPow(Matrix mat0, ll p, ll mod)
{
    Matrix mat,mat1 = mat0;
    mat.E();
    while(p)
    {
        if(p & 1)   MatMul(mat,mat1,mod);
        MatMul(mat1,mat1,mod);
        p >>= 1;
    }
    return mat;
}

ll qpow(ll a, ll b, ll mod)
{
    ll res = 1;
    //cout<<a<<"^"<<b<<" % "<<mod<<" : ";
    while(b)
    {
        if(b & 1)   res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    //res = (res % mod + mod) % mod;
    //cout<<res<<endl;
    return res;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
    freopen("out-2.txt","w",stdout);
#endif

    int T,i,j,cas;
    ll a,b,n,p;
    init();
    scanf("%d",&T);
    for(cas = 1; cas <= T; cas ++)
    {
        cin>>a>>b>>p>>n;
        cout<<"Case #"<<cas<<": ";
        if(n == 1)
        {
            cout<<a%p<<endl;
            continue;
        }
        if(n == 2)
        {
            cout<<b%p<<endl;
            continue;
        }
        phi = eular(p);

        //cout<<"phi = "<<phi<<endl;

        Matrix mat;
        mat.init();

        mat = MatPow(mat,n-2,phi);

        ll pa = mat.m[0][1], pb = mat.m[0][0];

        //cout<<"pa = "<<pa<<"\tpb = "<<pb<<endl;

        a = qpow(a,pa,p);
        b = qpow(b,pb,p);



        cout<<(a * b) % p<<endl;

    }
    return 0;
}
