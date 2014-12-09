#include<iostream>   
#include<cstdio>   
#include<cstring>   
#include<cmath>   
#include<algorithm>   
#include<queue>   
using namespace std;  
#define maxn 1010   
#define maxm 20010   
const int inf = 0x3f3f3f3f;  
struct Nod {  
    int b, nxt;  
    int cap, cst;  
    void init(int b, int nxt, int cap, int cst) {  
        this->b = b;  
        this->nxt = nxt;  
        this->cap = cap;  
        this->cst = cst;  
    }  
};  
struct MinCost {  
    int E[maxn];  
    Nod buf[maxm * 2];  
    int len;  
    int p[maxn];  
    void init(int n) {  
        memset(E, 255, sizeof(E));  
        len = 0;  
    }  
    void addCap(int a, int b, int cap, int cst) {  
        buf[len].init(b, E[a], cap, cst);  
        E[a] = len++;  
        buf[len].init(a, E[b], 0, -cst);  
        E[b] = len++;  
    }  
    bool spfa(int source, int sink) {  
        static queue<int> q;  
        static int d[maxn];  
        memset(d, 63, sizeof(d));  
        memset(p, 255, sizeof(p));  
        d[source] = 0;  
        q.push(source);  
        int u, v;  
        while (!q.empty()) {  
            u = q.front();  
            q.pop();  
            for (int i = E[u]; i != -1; i = buf[i].nxt) {  
                v = buf[i].b;  
                if (buf[i].cap > 0 && d[u] + buf[i].cst < d[v]) {  
                    d[v] = d[u] + buf[i].cst;  
                    p[v] = i;  
                    q.push(v);  
                }  
            }  
        }  
        return d[sink] != inf;  
    }  
    int solve(int source, int sink) {  
        int minCost = 0, maxFlow = 0;//需要maxFlow的话,想办法返回   
        while (spfa(source, sink)) {  
            int neck = inf;  
            for (int t = p[sink]; t != -1; t = p[buf[t ^ 1].b])//buf[t^壹].b是父节点   
                neck = min(neck, buf[t].cap);  
            maxFlow += neck;  
            for (int t = p[sink]; t != -1; t = p[buf[t ^ 1].b]) {  
                buf[t].cap -= neck;  
                buf[t ^ 1].cap += neck;  
                minCost += buf[t].cst * neck;  
            }  
        }  
        return minCost;  
    }  
} mc;  
int map[110][110],n;  
void floyd() {  
    for (int k =0; k <= n; k++)  
        for (int i =0; i <= n; i++)  
            for (int j=0; j <= n; j++){  
                if (map[i][k] + map[k][j] < map[i][j])  
                    map[i][j] = map[i][k]+map[k][j];  
            }  
}  
int main() {  
    int m, k, a, b, c;  
    while (scanf("%d%d%d",&n,&m,&k)&&n) {  
        for (int i = 0; i <= n; i++)  
            for (int j = 0;j<= n; j++)  
                map[i][j] = inf;  
        while (m--) {  
            scanf("%d%d%d", &a, &b, &c);  
            map[b][a]=map[a][b] = min(map[a][b],c);  
        }  
        floyd();  
        mc.init(n * 2 + 3);  
        mc.addCap(0, n * 2 + 1, k, 0);  
        mc.addCap(n*2+1,n*2+2,k,0);  
        int temp=1<<23;  
        for (int i = 1; i <= n; i++) {  
            mc.addCap(i, i + n,1,-temp);  
            mc.addCap(n*2+1,i,1,map[i][0]);  
            mc.addCap(i+n, n*2+2,1,map[i][0]);  
            for (int j = i+1;j<=n;j++)  
                mc.addCap(i+n,j,1,map[i][j]);  
        }  
        printf("%d\n",mc.solve(0,n*2+2)+temp*n);  
    }  
    return 0;  
}  
