#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;

#define nMax 1000010
#define ll long long

ll dp[nMax];
int num[nMax],pre[nMax],now[nMax],w[nMax],a[nMax];

int main()
{
    int n,m,tmp,i,j;
    while(~scanf("%d",&n),n){
        for(i=1; i<=n; i++)    scanf("%d",a+i);
        memset(now,0,sizeof(now));
        memset(num,0,sizeof(num));
        for(i=1; i<=n; i++){
            pre[i] = i - now[a[i]];
            now[a[i]] = i;
            num[pre[i]]++;
        }
        memset(w,0,sizeof(w));
        memset(now,0,sizeof(now));
        int tmp = 0;
        for(i=n; i>=1; i--){
            if(now[a[i]] == 0)    tmp++;
            now[a[i]] = i;
            w[n-i+1] = tmp;
        }
        dp[1] = n;    tmp = n;
        for(i=2; i<=n; i++){
            dp[i] = dp[i-1] - w[i-1];
            tmp -= num[i-1];
            dp[i] += tmp;
        }
        scanf("%d",&n);
        while(n--){
            scanf("%d",&m);
            printf("%I64d\n",dp[m]);
        }
    }
    return 0;
}
