#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <climits>
#include <numeric>
using namespace std;

const int CHARSET = 26;
//const int MAX_N_NODES = 500005;
const int MAX_N_NODES = 250005;
const int L = 1000005;
const int N = 10001;
int pointer, n;
char s[L];
struct Node {
    Node *ch[CHARSET], *fail;
    int value;  bool flag;
    Node() {
        memset(ch, 0, sizeof ch);
        fail = 0;
        value = 0;
        flag = false;
    }
    Node*go(int w);
}*root;

Node nodePool[MAX_N_NODES], *cur;
Node *que[MAX_N_NODES];
Node* newNode() {
    Node*t = cur++;
    memset(t->ch, 0, sizeof t->ch);
    t->fail = 0;
    t->flag = false;
    t->value = 0;
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
            que[qt++] = v;
        }
    }
}

void insert(char *str,int value)
{
    int i, j, l = strlen(str);
    Node *node = root;
    for(i = 0; i < l; i ++)
        node = node->go(str[i] - 'a');
    node->value += 1;
}

int AC(char* str)
{
    int i, j, l = strlen(str), res = 0, state = 0;
    Node *node = root, *tNode, *fNode;
    for(i = 0; i < l; i ++)
    {
        tNode = node->ch[ str[i] - 'a' ];
        if(!tNode)
        {
            fNode = node->fail;
            while(fNode && fNode->ch[str[i] -'a'] == 0)
                fNode = fNode->fail;
            if(!fNode)
                tNode = root;
            else
                tNode = fNode->ch[ str[i] - 'a' ];
        }
        node = tNode;
        while(tNode)
        {
            if(tNode->flag == false)
                res += tNode->value, tNode->flag = true;
            tNode = tNode->fail;
        }

    }
    return res;
}

int main()
{
    int T,i,j,ans;
    scanf("%d",&T);
    while(T--)
    {
        init();
        scanf("%d",&n);
        for(i = 1; i <= n; i ++)
        {
            scanf("%s",s);
            insert(s, i);
        }
        build();
        scanf("%s",s);
        ans = AC(s);
        printf("%d\n",ans);
    }
    return 0;
}
