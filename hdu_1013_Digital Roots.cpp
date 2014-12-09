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
    int n,ans,i;
    string str;
    string std = "0";
    while(cin >> str){
        if(str == std) break;
        n = 0;  ans = 0;
        for(i = 0; i < str.length(); i++)   n += str[i] - '0';
        while(n) {
            ans = (ans + n % 10); n/=10;
            if(ans > 9) ans = ( ans - 1 ) % 9 + 1;
        }
        printf("%d\n",ans);
    }
    return 0;
}
