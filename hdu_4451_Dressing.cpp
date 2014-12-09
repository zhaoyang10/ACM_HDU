#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;

long long c[1010],s[1010];
char str1[50],str2[50];
int main()
{
    long long n,m,k,i,j,p,x,y,ans;
    while(~scanf("%I64d%I64d%I64d",&n,&m,&k),n||m||k){
        memset(c,0,sizeof(c));
        memset(s,0,sizeof(s));
        ans = n*m*k;
        scanf("%I64d",&p);
        while(p--){
            scanf("%s%I64d%s%I64d",str1,&x,str2,&y);
            if(str1[0] == 'c'){
                c[y]++;
            }else{
                s[x]++;
            }
        }
        for(i=1;i<=m;i++)    ans -= c[i]*k + s[i]*n - c[i]*s[i];
        printf("%I64d\n",ans);
    }
    return 0;
}
