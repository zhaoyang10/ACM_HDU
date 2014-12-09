#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;

int main()
{
    int n,x;
    while(~scanf("%d",&n), n){
        int res = 0;
        while(n--){
            scanf("%d",&x);
            res^=x;
        }
        printf("%d\n",res);
    }
    return 0;
}
