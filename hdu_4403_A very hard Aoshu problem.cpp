#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
#define nMax 100
char str[nMax],a[nMax];
int n,ans;

int get_left(int begin,int end)
{
    int i,res=0,tmp=0;
    for(i=begin;i<=end;i++){
        tmp = tmp*10 + str[i] - '0';
        if(a[i]){    res+=tmp;    tmp = 0;    }
    }
    return res;
}


void dfs(int now ,int equ){
    if(now == n-1 ){
        int a = get_left(0,equ);
        int b = get_left(equ+1,n-1);
        if(a == b)    ans++;
        return ;
    }
    if(now == equ)    dfs(now + 1, equ);
    else{
        a[now]=0;
        dfs(now+1, equ);
        a[now]=1;
        dfs(now+1, equ);
    }
}

int main()
{
    int i,j;
    while(scanf("%s",str)!=EOF){
        if(str[0]=='E')    break;
        n = strlen(str);
        ans = 0;    a[n-1] = 1;
        for(i=0;i<n-1;i++)        a[i]=1,dfs(0,i);
        printf("%d\n",ans);
    }
    return 0;
}
