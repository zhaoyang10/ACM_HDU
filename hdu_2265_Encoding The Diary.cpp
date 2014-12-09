#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdio>
using namespace std;
#define nMax 5000000
bool vis[nMax];
char str[nMax],s[nMax];
int l,len,i;
int main()
{
    //freopen("input.txt","r",stdin);
    while(gets(str)){
        len = strlen(str);
        memset(vis,0,sizeof(vis));
        for(i=0,l=1; i<len; i++)    if(str[i] != ' ')    s[l++] = str[i];
        for(i=3; i<l; i+=3){
            putchar(s[i]);
            vis[i] = true;
        }
        for(i=2; i<l; i+=2){
            if(vis[i])    continue;
            putchar(s[i]);
            vis[i] = true;
        }
        for(i=1; i<l; i++){
            if(vis[i])    continue;
            putchar(s[i]);
        }
        puts("");
    }
    return 0;
}
