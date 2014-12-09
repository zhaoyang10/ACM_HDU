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
#define eps 1e-8
#define ll long long
#define ull unsigned long long
#define MOD 1000000007

const int CHARSET = 4;
const int MAX_N_NODES = 10010;
const int NSTRING = 10;
const int STATE = 1 << NSTRING;
int pointer;
int value[NSTRING];
bool dp[2][MAX_N_NODES][STATE];
struct Node {
    Node*ch[CHARSET], *fail;
    int state;
    Node() {
        memset(ch, 0, sizeof ch);
        fail = 0;
        state = 0;
    }
    Node*go(int w);
}*root;

Node nodePool[MAX_N_NODES], *cur;

Node*newNode() {
    Node*t = cur++;
    memset(t->ch, 0, sizeof t->ch);
    t->fail = 0;
    t->state = 0;
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
        for (int c = 0; c < CHARSET; ++c) {
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
                //if(!son)    while(1);
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
            v->state |= v->fail->state;
            que[qt++] = v;
        }
    }
}

int gchar(char c)
{
    if(c == 'A')    return 0;
    else    if(c == 'T')    return 1;
    else    if(c == 'G')    return 2;
    else    if(c == 'C')    return 3;
    return -1;
}

void insert(char* s, int pid)
{
    int i, l = strlen(s);
    Node *node = root;
    for(i = 0; i < l; i ++)
        node = node->go( gchar(s[i]) );
    node->state |= (1 << pid);
}

int gvalue(int x)
{
    int i, res = 0;
    for(i = 0; i < NSTRING; i ++)
    {
        if(x & 1)  res += value[i];
        x >>= 1;
    }
    return res;
}

int AC(int n, int State)
{
    register int i, j, k, c, now, pre, state, jy, ky, y;
    int tot = cur - nodePool;
    Node *node,*tNode;
    for(i = 0; i < tot; i ++)
        for(j = 0; j < State; j ++)
            dp[1][i][j] = false;
    dp[1][0][0] = true;
    for(i = 0; i < n; i ++)
    {
        now = i & 1;    pre = now ^ 1;
        for(j = 0; j < tot; j ++)
            for(k = 0; k < State; k ++)
                dp[now][j][k] = false;
        for(j = 0; j < tot; j ++)
        {
            node = nodePool + j;
            for(k = 0; k < State; k ++)
            {
                if(!dp[pre][j][k])
                    continue;
                for(c = 0; c < CHARSET; c ++)
                {
                    tNode = node->ch[c];
//                    if(!tNode)  while(1);
                    jy = tNode - root;
                    y = k | tNode->state;
                    dp[now][jy][y] = true;
                }
            }
        }
    }
    int ans = -100000;
    now = (n - 1) & 1;
    for(i = 0; i < tot; i ++)
        for(j = 0; j < State; j ++)
        {
            if(dp[now][i][j])
            {
                ans = max(ans,gvalue(j));
            }
        }
    return ans;
}

int main()
{
#ifndef ONLINE_JUDGE

    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);

#endif
    int i,n,m,v,ans;
    char s[105];
    while(~scanf("%d%d",&m,&n))
    {
        memset(value,0,sizeof(value));
        init();
        for(i = 0; i < m; i ++)
        {
            scanf("%s%d", s, &v);
            insert(s, i);
            value[i] = v;
        }
        build();
        ans = AC(n, 1 << m);
        if(ans >= 0)    printf("%d\n",ans);
        else            puts("No Rabbit after 2012!");
    }
    return 0;
}
