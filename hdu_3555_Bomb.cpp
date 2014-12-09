#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <stack>
#include <queue>
#include <cmath>
#include <algorithm>
#define lson l, m, rt<<1
#define rson m+1, r, rt<<1|1
using namespace std;
typedef long long int LL;
const int MAXN =  0x3f3f3f3f;
const int  MIN =  -0x3f3f3f3f;
const double eps = 1e-9;
const int dir[8][2] = {{0,1},{1,0},{0,-1},{-1,0},{-1,1},
  {1,1},{1,-1},{-1,-1}};
LL dp[21][3]; unsigned long long int n; int a[25];
int main(){
#ifndef ONLINE_JUDGE
  freopen("in.txt", "r", stdin);
#endif
  int t; scanf("%d", &t);
  memset(dp, 0, sizeof(dp));
  dp[0][0] = 1;
  for (int i = 1; i < 21; ++i){
    dp[i][0] = dp[i-1][0] * 10 - dp[i-1][1];
    dp[i][1] = dp[i-1][0];
    dp[i][2] = dp[i-1][2] * 10 + dp[i-1][1];
  }
  while (t--){
    //cin >> n;
    scanf("%I64d", &n);
    int len = 0; memset(a, 0, sizeof(a));
    n++;
    while (n){
      a[++len] = n % 10; n /= 10;
    } LL ans = 0; int last = 0; bool flag = false;
    for (int i = len; i >= 1; --i){
      ans += (dp[i-1][2] * a[i]);
      if (flag) ans += dp[i-1][0] * a[i];
      if (!flag && a[i] > 4) {ans += dp[i-1][1];}
      if (last == 4 && a[i] == 9) {flag = true;}
      last = a[i];
    }
    //cout << ans << endl;
    printf("%I64d\n", ans);
  }

  return 0;
}
