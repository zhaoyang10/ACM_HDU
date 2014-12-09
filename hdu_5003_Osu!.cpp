#include<cmath>
#include<cstring>
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int nMax = 110;
int a[nMax];
int main()
{
    //freopen("1","r",stdin);
    int t;
    scanf("%d",&t);
    while( t-- ){
        int n;
        scanf("%d",&n);
        for(int i = 1;i <= n;i++)
            scanf("%d",&a[i]);
        sort(a+1,a+1+n);
        double ans = 0;
        for(int i = n;i >= 1;i--)
            ans += (double)a[i]*exp(log(0.95)*(double)(n-i));
        printf("%.6lf\n",ans);
    }
    return 0;
}
