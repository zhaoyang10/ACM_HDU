#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<map>
using namespace std;

map<string,int>mp;
string str,ballon[1010];
int n,i,j,Max,mark,tot;
int num[1010];
int main()
{
    while(~scanf("%d",&n),n){
        mp.clear();    tot =0;
        memset(num,0,sizeof(num));
        for(i=1; i<=n; i++){
            cin >> str;
            if(mp[str] == 0){
                mp[str] = ++tot;
                num[tot] = 1;
                ballon[tot] = str;
            }else    num[ mp[str] ]++;
        }
        Max = -1;    mark = -1;
        for(i=1; i<=n; i++)
            if(num[i] > Max){
                Max = num[i];
                mark = i;
            }
        cout << ballon[mark] << endl;
    }
    return 0;
}
