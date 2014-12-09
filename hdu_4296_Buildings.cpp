#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
#define nMax 100010
struct Person
{
    long long w,s;
    bool operator< (const Person & pp)const{
        return w+s < pp.w+pp.s;
    }
}p[nMax];
int main()
{
    long long n,Max,i,sum;
    while(~scanf("%I64d",&n)){
        for(i=0; i<n; i++)    scanf("%I64d%I64d",&p[i].w,&p[i].s);
        sort(p,p+n);    sum = 0;    Max = 0;
        for(i=0; i<n; i++){
            Max = max(Max, sum-p[i].s);
            sum += p[i].w;
        }
        printf("%I64d\n",Max);
    }
    return 0;
}
