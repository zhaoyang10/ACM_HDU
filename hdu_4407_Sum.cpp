#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<queue>
#include<set>
#include<map>
#include<cstring>
#include<vector>
#include<string>
#define MAXN 800
#define LL long long
using namespace std;

int N, M, rec[50];
map<int,int>mp;
bool p[805];
int pri[805], idx;

inline int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

inline void Getprime() {
    idx = -1;
    for (int i = 2; i <= MAXN; ++i) {
        if (!p[i]) {
            pri[++idx] = i;
        }
        for (int j = 0; i * pri[j] <= MAXN; ++j) {
            p[i*pri[j]] = 1;
            if (i % pri[j] == 0) break;
        }
    }
}

inline long long cal(int num, int x) {
    if (x == 0) return 0;
    long long ret = 0;
    int cnt = 0, mask;
    int LIM = (int)sqrt(double(num));
    for (int i = 0; pri[i] <= LIM; ++i) {
        if (num % pri[i] == 0) {
            rec[++cnt] = pri[i];
            while (num % pri[i] == 0) {
                num /= pri[i];
            }
        }
        if (num == 1) break;
    }
    if (num != 1) {
        rec[++cnt] = num;
    }
    mask = 1 << cnt;
    for (int i = 1; i < mask; ++i) {
        int tsum = 0;
        long long yinzi = 1;
        for (int j = 0; j < cnt; ++j) {
            if (i & (1 << j)) {
                ++tsum;
                yinzi *= rec[j+1];
            }
        }
        if (tsum & 1) {
            long long k = x / yinzi;
            ret += ((yinzi + k * yinzi) * k) >> 1;
        } else {
            int k = x / yinzi;
            ret -= ((yinzi + k * yinzi) * k) >> 1;
        }
    }
    return ret;
}

inline long long SUM(int x) {
    return ((1 + 1LL * x) * 1LL * x) >> 1;
}

int main()
{
    Getprime();
     int T, op, a, b, p;
     map<int,int>::iterator it;
     long long ret;
     scanf("%d", &T);
     while (T--) {
        mp.clear();
        scanf("%d %d", &N, &M);
        for (int i = 1; i <= M; ++i) {
            scanf("%d", &op);
            if (op == 1) {
                ret = 0;
                scanf("%d %d %d", &a, &b, &p);
                for (it = mp.begin(); it != mp.end(); ++it) {
                    if (it->first != it->second && it->first >= a && it->first <= b) {
                        ret -= gcd(it->first, p) == 1 ? it->first : 0;
                        ret += gcd(it->second, p) == 1 ? it->second : 0;
                    }
                }
                ret += SUM(b) - SUM(a-1) - (cal(p, b) - cal(p, a-1));
                printf("%I64d\n", ret);
            } else {
                scanf("%d %d", &a, &b);
                mp[a] = b;
            }
        }
    }
    return 0;
}
