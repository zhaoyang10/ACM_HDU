#pragma comment(linker, "/STACK:1024000000,1024000000")
 #include <stdio.h>
 #include <string.h>
 #include <math.h>
 #include <algorithm>
 #define MAXN 500005
 using namespace std;

 struct edge{
     int v,e,n;
 }e[MAXN];
 int n, q, tu, tv, fa[MAXN], next[MAXN], p[MAXN];
 int first[MAXN], es;
 void addedge(int u,int v) {
     e[es].v = v, e[es].n = first[u], first[u] = es++;
 }
 //LCA+RMQ
 struct lcast{int dep, id;}list[MAXN*2], r[30][MAXN];
 int mm[MAXN*2], pos[MAXN], dis[MAXN], rid;
 void dfs(int u, int dep) {
     pos[u] = ++rid, list[rid].id = u, list[rid].dep = dep;
     dis[u] = dep;
     for (int i = first[u]; i != -1; i = e[i].n) {
         dfs(e[i].v, dep + 1);
         ++rid, list[rid].id = u, list[rid].dep = dep;
     }
 }
 void makermq() {
     rid = 0;
     dfs(0, 0);
     mm[1] = 0, r[0][1] = list[1];
     for(int i = 2; i <= rid; i ++) {
         mm[i] = (i&i-1) ? mm[i-1] : mm[i-1]+1;
         r[0][i] = list[i];
     }
     for (int i = 0; i < mm[rid]; i ++)
         for (int j = 1; j+(1<<i+1)-1 <= rid; j ++)
             r[i+1][j] = r[i][j].dep < r[i][j+(1<<i)].dep ? r[i][j] : r[i][j+(1<<i)];
 }
 int lca(int x, int y) {
     if(pos[x] > pos[y]) return lca(y, x);
     x = pos[x], y = pos[y];
     int k = mm[y - x + 1];
     y -= (1 << k) - 1;
     return r[k][x].dep < r[k][y].dep ? r[k][x].id : r[k][y].id;
 }
 //缩点构图
 int id[MAXN], cid[MAXN], cids, ids;
 //cirn 该环上点的个数,cirdis,环上两点的相对距离,cirin,进入环中的点
 int cirn[MAXN], cirdis[MAXN], cirin[MAXN];
 int dfsin(int u) {
     return cirin[u] ? cirin[u] : cirin[u] = dfsin(fa[u]);
 }
 void makegraph() {
     memset(cirn, 0 ,sizeof cirn);
     memset(cirin, 0, sizeof cirin);
     memset(id, 0, sizeof id); ids = cids = 0;
     for (int i = 1, j; i <= n; i++) {
         if (id[i]) continue;
         int sid = ids;
         for (j = i; !id[j]; j = fa[j]) id[j] = ++ids;
         //如果遇到的节点标记是这次一路找过来的,说明生成了一个环
         if (id[j] > sid || fa[i] == i) {
             //将该环中的点ID统一,并统计环中点的个数,以及环上两点的相对距离
             int cd = 1;
             ids = id[j], cid[++cids] = id[j], cirn[ids] = 1, cirdis[j] = cd, cirin[j] = j;
             for (int k = fa[j]; k != j; k = fa[k])
                 id[k] = ids, cirn[ids]++, cirdis[k] = ++cd, cirin[k] = k;
         }
     }
     //处理非环点进入环中的第一个点
     for (int i = 1; i <= n; i++) {
         if (cirin[i]) continue;
         else cirin[i] = dfsin(i);
     }
     memset(first, -1, sizeof first); es=0;
     for (int i = 1; i <= n; i++)
         if(id[i] != id[fa[i]]) addedge(id[fa[i]], id[i]);
     for (int i = 1; i <= cids; i++)
         addedge(0, cid[i]);
     makermq();
 }
 int main() {
     //freopen("test.in", "r", stdin);
     while (scanf("%d%d", &n, &q) != EOF) {
         for (int i = 1; i <= n; i++) p[i] = i;
         for (int i = 1; i <= n; i++)
             scanf("%d", &tu), fa[i] = tu;
         makegraph();
         while (q-- ) {
             scanf("%d%d", &tu, &tv);
             int lc = lca (id[tu],id[tv]);
             //LCA是虚拟根节点,说明不在一颗子树上
             if(lc == 0) printf("-1 -1\n");
             //LCA不是环,一般的LCA问题
             else if (cirn[lc] == 0){
                 printf("%d %d\n", dis[id[tu]] - dis[lc], dis[id[tv]] - dis[lc]);
             } else {
                 //uin和vin是u和v进入环的顶点,disu和disv是到环距离,det1和det2是u和v在环上要走的距离
                 int uin = cirin[tu], vin = cirin[tv];
                 int disu = dis[id[tu]] - dis[lc], disv = dis[id[tv]] - dis[lc];
                 int det1 = (cirdis[vin] - cirdis[uin] + cirn[id[uin]]) % cirn[id[uin]];
                 int det2 = (cirn[id[uin]] - cirdis[vin] + cirdis[uin]) % cirn[id[uin]];
                 //保证解满足题意,最大值最小,然后是最小值最大,然后是A>=B
                 int ansu = disu + det1, ansv = disv;
                 if (max(disu+det1, disv) > max(disu, disv+det2))ansu = disu, ansv = disv+det2;
                 else if(max(disu+det1, disv) < max(disu, disv+det2))ansu = disu+det1, ansv = disv;
                 else if(min(disu+det1, disv) < min(disu, disv+det2))ansu = disu+det1, ansv = disv;
                 else if(min(disu+det1, disv) > min(disu, disv+det2))ansu = disu, ansv = disv+det2;
                 printf("%d %d\n", ansu, ansv);
             }
         }
     }
     return 0;
 }
