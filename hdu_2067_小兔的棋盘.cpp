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
#define N 37
ll c[N];

int main()
{
    int i,j,n;
    memset(c,0,sizeof(c));
    c[1]=1;
    for(i=2; i<N; i++)
        for(j=1; j<i; j++)
            c[i] += c[i-j]*c[j];
    i = 1;
    while(cin>>n)
    {
        if(n == -1) break;
        cout<<i++<<" "<<n<<" "<<c[n+1]*2<<endl;
    }

    return 0;
}
