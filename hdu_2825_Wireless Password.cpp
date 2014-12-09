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
#define MOD 20090717


const int STATE = 1<<10;
const int CHARSET = 26;
const int MAX_N_NODES = 251;

int pointer;
int dp[2][MAX_N_NODES][STATE];
int num[STATE];
struct Node {
    Node*ch[CHARSET], *fail;
    int state;
    Node() {
        memset(ch, 0, sizeof ch);
        fail = 0;
    }
    Node*go(int w);
}*root;
Node nodePool[MAX_N_NODES], *cur;

inline Node*newNode() {
    Node*t = cur++;
    memset(t->ch, 0, sizeof t->ch);
    t->fail = 0;
    t->state = 0;
    return t;
}

inline Node* Node::go(int w) {
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
void insert(char* s, int pid)
{
    int i, l = strlen(s);
    Node *node = root;
    for(i = 0; i < l; i ++)
    {
        node = node->go( s[i] - 'a' );
    }
    node->state |= (1 << pid);
}


int AC(int n, int K, int State)
{
    register int i, j, k, state, ystate, yid, now, pre;
    int tot = cur - nodePool;
    Node *node, *tNode, *fNode;


    for(j = 0; j < tot; j ++)
        for(k = 0; k < State; k ++)
            dp[1][j][k] = 0;

    dp[1][0][0] = 1;
    for(i = 0; i < n; i ++)
    {
        now = i & 1;    pre = now ^ 1;

        for(j = 0; j < tot; j ++)
            for(k = 0; k < State; k ++)
                dp[now][j][k] = 0;

        for(j = 0; j < tot; j ++)
        {
            for(state = 0; state < State; state ++)
            {
                if(dp[pre][j][state] == 0)  continue;
                for(k = 0; k < CHARSET; k ++)
                {
                    node = root + j;
                    tNode = node->ch[k];
                    yid = tNode - root;
                    ystate = tNode->state | state;
                    dp[now][yid][ystate] = (dp[now][yid][ystate] + dp[pre][j][state]) % MOD;
                }
            }
        }
    }
    register int ans = 0, tn;
    now = (n - 1) & 1;
    for(i = 0; i < tot; i ++)
    {
        for(state = 0; state < State; state ++)
        {
            tn = num[state];
            if(tn < K)  continue;
                ans = (ans + dp[now][i][state]) % MOD;
        }
    }
    return ans;
}

void gNum()
{
    int i,j,t;
    for(i = 0; i < STATE; i ++)
    {
        t = 0;
        j = i;
        while(j){
            t += (j & 1);
            j >>= 1;
        }
        num[i] = t;
    }
}

int main()
{
#ifndef ONLINE_JUDGE

    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);

#endif
    int i,ans,n,m,k,cas = 1;
    char s[26];
    gNum();

    while(~scanf("%d%d%d",&n,&m,&k) && (n || m || k))
    {
        init();
        for(i = 0; i < m; i ++)
        {
            scanf("%s",s);
            insert(s,i);
        }
        build();

        /*if(cur - nodePool >= 63)
            return 0;
        */
        ans = AC(n,k,(1 << m));
        printf("%d\n",ans);
    }
    return 0;
}
