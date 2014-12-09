#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<map>
using namespace std;
#define nMax 510
struct Group{
    int he,ta;
    Group(int _he=0,int _ta=0):he(_he),ta(_ta){}
    bool operator < (const Group & g)const{
        if(ta == g.ta)    return he < g.he;
        return ta < g.ta;
    }
}G[nMax];
map<Group,int>mp;
int tot;
int ord[nMax],dp[nMax],num[nMax];
bool cmp(int x,int y)    {return G[x]<G[y];}
int main()
{
    int n,i,j,x,y;
    while(~scanf("%d",&n)){
        mp.clear();    tot = 0;
        memset(num,0,sizeof(num));
        for(i=0; i<n; i++){
            scanf("%d%d",&x,&y);
            x++;    y=n-y;
            if(x > y)    continue;
            G[0] = Group(x,y);
            if(mp[G[0]] == 0){
                G[++tot] = G[0];
                mp[G[tot]] = tot;
                num[tot] = 1;
            }else    num[ mp[G[0]] ]++;
        }
        for(i=1; i<=tot; i++)    num[i] = min(num[i], G[i].ta-G[i].he+1);
        for(i=1; i<=tot; i++)    ord[i] = i;
        sort(ord+1,ord+tot+1,cmp);
        G[0].ta = -1;
        dp[0] = 0;    ord[0] = 0;
        for(i=1; i<=tot; i++){
            dp[i] = dp[i-1];
            for(j=0; j<i; j++){
                if(G[ord[j]].ta >= G[ord[i]].he)    break;
                dp[i] = max(dp[i], dp[j]+num[ord[i]]);
            }
        }
        printf("%d\n",dp[tot]);
    }
    return 0;
}
