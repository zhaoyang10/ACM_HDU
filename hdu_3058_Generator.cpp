#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<set>
#include<map>
#include<cmath>
using namespace std;
#define eps 1e-11
#define ll long long
#define ull unsigned long long
#define MOD 1000000007
#define M 15

const int CHARSET = 8;
const int MAX_N_NODES = 110;
int n,m;
int pos[M];
double px[M];
bool vis[MAX_N_NODES];

struct Matrix{
    double m[MAX_N_NODES][MAX_N_NODES];
    int matn;
    void init(int _matn)
    {
        matn = _matn;
        int i, j;
        for(i = 0; i < matn; i ++)
            for(j = 0; j <= matn; j ++)
                m[i][j] = 0.0;
    }
    void check()
    {
        puts("check matrix :");
        int i, j;
        for(i = 0; i < matn; i ++)
        {
            for(j = 0; j <= matn; j ++)
            {
                printf("%.11lf\t",m[i][j]);
            }
            puts("");
        }
        puts("end check !");
    }

}Mat;

struct Node {
    Node*ch[CHARSET], *fail;
    bool flag;
    Node() {
        memset(ch, 0, sizeof ch);
        fail = 0;
        flag = false;
    }
    Node*go(int w);
}*root;

Node nodePool[MAX_N_NODES], *cur;

Node*newNode() {
    Node*t = cur++;
    memset(t->ch, 0, sizeof t->ch);
    t->fail = 0;
    t->flag = false;
    return t;
}

Node* Node::go(int w) {
    if (ch[w] == 0) {
        ch[w] = newNode();
    }
    return ch[w];
}

void init() {
    cur = nodePool;
    root = newNode();
}

void build() {
    static Node*que[MAX_N_NODES];
    int qh = 0, qt = 0;
    que[qt++] = root;
    while (qh < qt) {
        Node*t = que[qh++];
        for (int c = 0; c < n; ++c) {
            Node*v = t->ch[c];
            if (!v)
            {
                Node*f = t->fail;
                Node*son;
                while(f && f->ch[c] == 0)
                    f = f->fail;
                if(!f)
                    son = root;
                else
                    son = f->ch[c];
                t->ch[c] = son;
                continue;
            }
            Node*f = t->fail;
            while (f && f->ch[c] == 0)
                f = f->fail;
            if (f == 0)
                v->fail = root;
            else
                v->fail = f->ch[c];
            v->flag |= v->fail->flag;
            que[qt++] = v;
        }
    }
}

void insert(char* s,int pid)
{
    int i, l = strlen(s);
    Node *node = root;
    for(i = 0; i < l; i ++)
        node = node->go( s[i] - 'A' );
    node->flag = true;
    pos[pid] = node - root;
}

void dfs(Node *node)
{
    int idx = node - root;
    if(vis[idx])    return;
    vis[idx] = true;

    Node *fNode, *tNode;
    int i, j, idy;
    for(i = 0; i < n; i ++)
    {
        tNode = node->ch[i];
        idy = tNode - root;
        if(tNode->flag) continue;
        Mat.m[idx][idy] -= 1.0;
        dfs(tNode);
    }
}



double gauss()
{
    int i, j, k, g, idm, tot = cur - nodePool;
    double m1, m2;
    for(i = 0; i < tot; i ++)
    {
        idm = i;    m1 = fabs(Mat.m[i][i]);
        for(j = i + 1; j < tot; j ++)
            if(fabs(Mat.m[j][i]) > eps && fabs(Mat.m[j][i]) - m1 > eps)
            {
                idm = j;
                m1 = fabs(Mat.m[j][i]);
            }
        if(m1 < eps)    continue;

        if(idm != i)
            for(j = i; j <= tot; j ++)
                swap(Mat.m[i][j], Mat.m[idm][j]);


        for(j = i + 1; j < tot; j ++)
            if(fabs(Mat.m[j][i]) > eps)
                for(k = tot; k >= i; k --)
                    Mat.m[j][k] = Mat.m[j][k] - Mat.m[j][i] / Mat.m[i][i] * Mat.m[i][k];

//        printf("gauss : i = %d\n",i);
//        Mat.check();
   }

    memset(px, 0, sizeof(px));

    for(i = tot - 1; i >= 0; i --)
    {
        if(fabs(Mat.m[i][i]) < eps)
        {
            px[i] = 0;
            continue;
        }
        m2 = 0.0;
        for(j = i + 1; j < tot; j ++)
            m2 += px[j] * Mat.m[i][j];
        m2 = Mat.m[i][tot] -  m2;
        px[i] = m2 / Mat.m[i][i];
    }


    m1 = px[0];
    return m1;
}

double Expect()
{
    int i, j, tot = cur - root;
    Mat.init(tot);
    memset(vis,0,sizeof(vis));

//    puts("before dfs:");
//    Mat.check();

    dfs(root);

//    puts("after dfs:");
//    Mat.check();

    for(i = 0; i < tot; i ++)
    {
        Mat.m[i][i] += n;
        Mat.m[i][tot] += n;
    }
    for(i = 0; i < m; i ++)
    {
        j = pos[i];
        Mat.m[j][tot] = 0;
        Mat.m[j][j] = 0;
    }

//    puts("final :");
//    Mat.check();

    return gauss();
}

int main()
{
#ifndef ONLINE_JUDGE
//    freopen("in-2.txt","r",stdin);
//    freopen("out-4.txt","w",stdout);
#endif
    int T, i, cas = 1;
    char s[11];
    double ans;
    scanf("%d", &T);
    while(T--)
    {
        memset(pos, -1, sizeof(pos));
        init();
        scanf("%d%d",&n,&m);
//        printf("\nCase %d : %d %d\n",cas++,n,m);
        for(i = 0; i < m; i ++)
        {
            scanf("%s", s);
            insert(s, i);
//            puts(s);
        }
        build();
        ans = Expect();
        printf("%.2lf\n", ans);
    }
    return 0;
}
