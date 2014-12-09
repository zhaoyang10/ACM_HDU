#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<set>
#include<map>
using namespace std;
#define eps 1e-8



int main()
{
    int i,n,h,t,d,ans;
    while(scanf("%d",&n) && n){
        h = 0; ans = 0;
        for(i=0; i<n; i++){
            scanf("%d",&t);
            d = t - h;
            if(d > 0)   ans += d*6 + 5;
            else        ans += d*(-4) + 5;
            h = t;
        }
        printf("%d\n",ans);
    }

    return 0;
}
