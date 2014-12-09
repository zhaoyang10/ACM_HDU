// 裸平面图网络流  没有下界  求最大流  10000个点  10000条边  第一句开内存

#pragma comment(linker, "/STACK:102400000,1024000")
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
const int maxn = 100010;
const int maxm = 100010;
const double inf = 1 << 28;
struct node {
    int be, ne;
    double val;
    void init(int b, int e, double v) {
        be = b;
        ne = e;
        val = v;
    }
};

int cmp(double a, double b) {
    double eps = 1e-8;
    if (a - b > eps)
        return 1;
    else if (a - b >= -eps)
        return 0;
    else
        return -1;
}
struct SPFA {
    node buf[maxm * 2];
    int len, E[maxn], queue[maxn];
    double d[maxn];
    void init() {
        memset(E, -1, sizeof(E));
        len = 0;
    }
    void add(int a, int b, double v) {
        if (a == b)
            return;
        buf[len].init(b, E[a], v);
        E[a] = len++;
    }
    int vis[maxn];
    double solve(int s, int t) {
        int head = 0, tail = 0;
        memset(vis, 0, sizeof(vis));
        memset(d, 255, sizeof(d));
        d[s] = 0;
        queue[(tail++) % maxn] = s;
        vis[s] = true;
        int a, b;
        while (head != tail) {
            a = queue[(head++) % maxn];
            vis[a] = 0;
            for (int i = E[a]; i != -1; i = buf[i].ne) {
                b = buf[i].be;
                if (cmp(d[a] + buf[i].val, d[b]) == -1) {
                    d[b] = d[a] + buf[i].val;
                    if (!vis[b]) {
                        vis[b] = 1;
                        queue[(tail++) % maxn] = b;
                    }
                }
            }
        }
        return d[t];
    }
} sp;
struct arch {
    int in, out;
    double angle;
    arch(int a, int b, double c) {
        in = a;
        out = b;
        angle = c;
    }
    bool operator <(const arch& oth) const {
        return cmp(angle, oth.angle) == -1;
    }
};
int n, m;
double px[maxn], py[maxn], cap[maxm];
vector<arch> vertex[maxn];
void init() {
    scanf("%d%d", &n, &m);
    double left = inf, right = -inf;
    int s = 0, t = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%lf%lf", &px[i], &py[i]);
        vertex[i].clear();
        if (px[i] < left) {
            s = i;
            left = px[i];
        }
        if (px[i] > right) {
            right = px[i];
            t = i;
        }
    }
    int a, b;
    for (int i = 0; i < m; i++) {
        scanf("%d%d%lf", &a, &b, cap + i);
        if (a == b) {
            m--;
            i--;
            continue;
        }
        //①把所有的边都拆成两条有向边，自环删掉(有影响吗？)。
        double agab = atan2(py[b] - py[a], px[b] - px[a]);
        double agba = atan2(py[a] - py[b], px[a] - px[b]);
        //②将每条有向边在另一个图G‘中用一个点表示。
        vertex[a].push_back(arch(i << 1, i << 1 | 1, agab));
        vertex[b].push_back(arch(i << 1 | 1, i << 1, agba));
    }
    a = m << 1, b = a | 1;
    //注意(S, T)的那条新加边要特殊处理。
    vertex[s].push_back(arch(a, b, acos(-1.0)));
    vertex[t].push_back(arch(b, a, 0));
}
int nxt[maxm * 2], belong[maxm * 2], cnt;
void find(int x, int root) {
    if (nxt[x] != root)
        find(nxt[x], root);
    belong[x] = cnt;
}
void build() {
    //③将所有的与之相连的边极角排序。
    for (int i = 1; i <= n; i++) {
        sort(vertex[i].begin(), vertex[i].end());
        int ms = vertex[i].size();
    //④遍历每条入边。将其后继设为与之顺时针相邻的出边。也就是在G’中连一条从这个入边的点到其后继的有向边。
        for (int j = 0; j < ms - 1; j++)
            nxt[vertex[i][j].in] = vertex[i][j + 1].out;
        nxt[vertex[i][ms - 1].in] = vertex[i][0].out;
    }
    int ms = m << 1 | 1;
    memset(belong, -1, sizeof(belong));
    cnt = 0;
    //⑤在G'中就是一些不相交的有向环。每个有向环就对应一个区域。找出了所有的区域，我们要的那张图就简单了。
    for (int i = 0; i <= ms; i++)
        if (belong[i] == -1 && ++cnt > 0)
            find(i, i);
    //构不成平面的边,会形成一个特殊的区域，相当于进去死胡同再出来。但是答案不会受到影响，所以直接忽略。
}
double work() {
    int a, b;
    sp.init();
    //⑥根据对偶图构图，求得s-t之间最短路即是对应的最小割
    for (int i = 0; i < m; i++) {
        a = belong[i << 1];
        b = belong[i << 1 | 1];
        sp.add(a, b, cap[i]);
        sp.add(b, a, cap[i]);
    }
    a = belong[m << 1];
    b = belong[m << 1 | 1];
    return sp.solve(a, b);
}
int main() {
    int cas;
    scanf("%d", &cas);
    while (cas--) {
        init();
        build();
        printf("%.0f\n", work());
    }
    return 0;
}
