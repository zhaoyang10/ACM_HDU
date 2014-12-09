#include<iostream>
#include<string>
#include<cstdio>
#include<cstring>
using namespace std;
#define nMax 101000
#define MAX 1<<29
int dp[nMax],path[nMax],s[nMax],a[nMax];
int main()
{
    int T,cas,i,j,k,Max,he,ta,n;
    scanf("%d",&T);
    for(cas = 1; cas <=T; cas ++){
        scanf("%d",&n);
        for(i = 1; i <= n; i++)    scanf("%d",a+i);
        s[0] = 0;    dp[0] = MAX;
        for(i=1; i<=n; i++){
            s[i] = s[i-1] + a[i];
            if(dp[i-1] > s[i-1]){
                path[i] = i-1;
                dp[i] = s[i-1];
            }else{
                path[i] = path[i-1];
                dp[i] = dp[i-1];
            }
        }
        Max = -(MAX);
        for(i=1; i<=n; i++){
            if(s[i] - dp[i] > Max || ( s[i] - dp[i] == Max && path[i] + 1 < he)){
                Max = s[i] - dp[i];
                he = path[i] + 1;
                ta = i;
            }
        }

        printf("Case %d:\n%d %d %d\n",cas,Max,he,ta);
        if(cas != T)    puts("");
    }
    return 0;
}
