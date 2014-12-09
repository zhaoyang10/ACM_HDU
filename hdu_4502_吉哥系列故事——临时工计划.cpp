#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<map>
#include<vector>
#include<queue>
#include<cmath>
using namespace std;
#define ll long long
const int N = 1010;
int dp[N];
struct Work{
    int s,e,c;
    bool operator < (const Work & w) const{
        if(e == w.e)    return s<w.s;
        return e<w.e;
    }
}w[N];


int main()
{
    int n,m,T,i,j;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&m,&n);
        for(i=1; i<=n; i++) scanf("%d%d%d",&w[i].s,&w[i].e,&w[i].c);
        sort(w+1,w+n+1);
        while(n>0 && w[n].e > m) n--;
        memset(dp,0,sizeof(dp));
        w[0].e=0;   w[0].c=0;
        for(i=1; i<=n; i++){
            int h,t,mid;
            h=0;    t=i;
            while(h<t){
                mid = (h+t)>>1;
                if(w[mid].e >= w[i].s)  t=mid;
                else    h = mid+1;
            }
            h--;
            dp[i] = dp[h]+w[i].c;
            if(i>0) dp[i] = max(dp[i],dp[i-1]);
        }
        printf("%d\n",dp[n]);
    }
    return 0;
}
