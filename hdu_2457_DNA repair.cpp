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

const int CHARSET = 26;
const int MAX_N_NODES = 50005;
int dp[2][MAX_N_NODES];
int pointer;

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
        for (int c = 0; c < CHARSET; ++c) {
            Node*v = t->ch[c];
            if (!v)
                continue;
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

int gchar(char c)
{
    if(c == 'A')    return 0;
    else    if(c == 'T')    return 1;
    else    if(c == 'G')    return 2;
    else    if(c == 'C')    return 3;
    return -1;
}

void insert(char* s)
{
    int i, l = strlen(s);
    Node *node = root;
    for(i = 0; i < l; i ++)
        node = node->go( gchar(s[i]) );//,\
//        printf("%d :% c\n",node - nodePool, s[i]);

    node->flag = true;
}

queue<Node*>q[2];

int AC(char* s)
{
    int i, j, l = strlen(s), now, pre, t, idx, id, cost, tot = cur - nodePool;
    Node *node = root, *tNode, *fNode;
    while(!q[0].empty())  q[0].pop();
    while(!q[1].empty())  q[1].pop();
    q[0].push(node);
    now = 1;    pre = 0;
    memset(dp,-1,sizeof(dp));
    dp[0][0] = 0;
    for(i = 0; i < l; i ++)
    {
//        printf("s[%d] = %c\n",i,s[i]);
        pre = i & 1;
        now = pre ^ 1;
        while(!q[now].empty())  q[now].pop();
        memset(dp[now],-1,sizeof(dp[now]));
        while(!q[pre].empty())
        {
            node = q[pre].front();
            q[pre].pop();   id = node - root;
//            printf("dp[%d][%d] = %d\n",pre,id,dp[pre][id]);
            for(j = 0; j < 4; j ++)
            {
                cost = (j != gchar(s[i]));
                //printf("char : %c\tj = %d\tcost = %d\n",s[i],j,cost);
                tNode = node->ch[j];
                //printf("tNode = %d\n",tNode - root);
                if(!tNode)
                {
                    //puts("null");
                    fNode = node->fail;
                    //printf("fNode = %d\n",fNode - root);
                    while(fNode && !(fNode->ch[j]))
                    {
                        fNode = fNode->fail;
                    }
                    //printf("fNode = %d\t = %d\n",fNode - root,fNode);
                    if(!fNode)
                        tNode = root;
                    else
                        tNode = fNode->ch[j];
                }
                if(tNode->flag) continue;

                idx = tNode - root;
                //printf("idx = %d\n",idx);

                if(dp[now][idx] == -1 || dp[now][idx] > dp[pre][id] + cost){
                    dp[now][idx] = dp[pre][id] + cost;
                    q[now].push(tNode);
//                    printf("update : dp[%d][%d] = %d\n",now,idx,dp[now][idx]);
                }

                //system("pause");
                //puts("yes");
            }
            //system("pause");
        }
    }
    now = l & 1;
    int res = -1;
    for(i = 0; i < tot; i ++)
        if(dp[now][i] != -1 && !nodePool[i].flag)
        {
            if(res == -1 || res > dp[now][i])
                res = dp[now][i];
        }
    return res;
}

int main()
{
#ifndef ONLINE_JUDGE

    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);

#endif
    int cas = 0,n,i,ans;
    char s[1005];
    while(~scanf("%d",&n) && n)
    {
        //cout<<n<<endl;
        cas++;
        init();
        for(i = 0; i < n; i ++)
        {
            scanf("%s",s);      //cout<<s<<endl;
            insert(s);

        }
        build();
        scanf("%s",s);
        //cout<<s<<endl;
        ans = AC(s);
        printf("Case %d: %d\n",cas,ans);
        //puts("");
    }
    return 0;
}
