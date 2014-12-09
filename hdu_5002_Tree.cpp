#include <cstdio>
#include <algorithm>
const int N = 100010;
const int inf = ~0u >> 2;
struct Node* null;
struct Node
{
    Node* ch[2];
    Node* fa;
    int val;
    int mx[2];
    int cnt[2];
    int add;
    int same;
    int rev;
    int sz;
    inline bool isroot(){return fa==null||fa->ch[0]!=this&&fa->ch[1]!=this;}
    inline bool d(){return fa->ch[1]==this;}
    inline void setc(int s, Node* who){who->fa=this;ch[s]=who;}
    inline void rotate() {
        bool f=d();
        Node* y=fa; y->setc(f,ch[!f]),fa=y->fa;
        if(!y->isroot()) fa->ch[y->d()]=this;
        this->setc(!f,y),y->up();
    }
    void splay() {
        for(go();!isroot();rotate())
            if(!fa->isroot())
                (fa->d()^d())?rotate():fa->rotate();
        up();
    }
    inline void up() ;
    void init(int v) {
        sz = 1;
        mx[1] = v; cnt[1] = 1;
        mx[0] = -inf; cnt[0] = 0;
        val = v;
        fa = ch[0] = ch[1] = null;
        rev = 0;
        same = -inf;
        add = 0;
    }
    void flip() {
        std::swap(ch[0], ch[1]);
        rev ^= 1;
    }
    void addv(int v) {
        if(this == null) return ;
        if(same != -inf) {
            ch[0]->make(same);
            ch[1]->make(same);
            same = -inf;
        }
        mx[1] += v;
        if(mx[0] != -inf)mx[0] += v;
        val += v;
        add += v;
    }
    void make(int sa) {
        if(this == null) return ;
        val = sa;
        mx[1] = sa;
        mx[0] = -inf;
        cnt[1] = sz;
        cnt[0] = 0;
        add = 0;
        same = sa;
    }
    void push() {
        if(rev) {
            ch[0]->flip(), ch[1]->flip(), rev = 0;
        }
        if(same != -inf) {
            ch[0]->make(same), ch[1]->make(same), same = -inf;
        }
        if(add) {
            ch[0]->addv(add), ch[1]->addv(add), add = 0;
        }
    }
    void print() {
        push();
        if(this != null) {
            if(ch[0] != null) ch[0]->print();
            printf("%d %d %d %d %d \n", val, mx[1], cnt[1], mx[0], cnt[0]);
            if(ch[1] != null) ch[1]->print();
        }
    }
    void go() {
        if(!isroot()) fa->go();
        push();
    }
};

struct PP
{
    int val, cnt;
    inline bool operator < (const PP& cmp) const {
        return val < cmp.val;
    }
    PP(int v = 0, int c = 0) : val(v), cnt(c) {
    }
}p[10];
void Node::up()
{
sz = ch[0]->sz + 1 + ch[1]->sz;
    int tot = 0;
    p[tot++] = PP(val, 1);
    for(int i = 0; i < 2; i++) {
        if(ch[0]->mx[i] != -inf) {
            p[tot++] = PP(ch[0]->mx[i], ch[0]->cnt[i]);
        }
    }
    for(int i = 0; i < 2; i++) {
        if(ch[1]->mx[i] != -inf) {
            p[tot++] = PP(ch[1]->mx[i], ch[1]->cnt[i]);
        }
    }
    std::sort(p, p + tot);
    int top = 1;
    for(int i = 1; i < tot; i++) {
        if(p[i].val == p[i - 1].val) {
            p[top - 1].cnt += p[i].cnt;
        } else {
            p[top++] = p[i];
        }
    }
    if(top == 1) {
        mx[1] = p[0].val;
        cnt[1] = p[0].cnt;
        mx[0] = -inf;
        cnt[0] = 0;
    } else {
        mx[1] = p[top - 1].val;
        cnt[1] = p[top - 1].cnt;
        mx[0] = p[top - 2].val;
        cnt[0] = p[top - 2].cnt;
    }
}
struct Link_Cut_Tree
{
    Node node[N];
    Node* access(Node* u) {
        Node* v = null;
        for(; u != null; v = u, u = u->fa) {
            u->splay();
            u->ch[1] = v;
            u->up();
        }
        return v;
    }
    void make_same(int a, int b, int c) {
        Node* u = node + a;
        Node* v = node + b;
        make_root(u);
        access(v);  u->splay();
        u->make(c);
    }
    void add_value(int a, int b, int c) {
        Node* u = node + a;
        Node* v = node + b;
        make_root(u);
        access(v); u->splay();
        u->addv(c);
    }
    void solve(int a, int b) {
        Node* u = node + a;
        Node* v = node + b;
       /* Node *tmp = access(v);
        tmp->print();
        */
        make_root(u);
        u = access(v);
        if(u->mx[0] == -inf) {
            puts("ALL SAME");
        } else {
            printf("%d %d\n", u->mx[0], u->cnt[0]);
        }
    }
    void cut(int a, int b)   {
        Node* u = node + a;
        Node* v = node + b;
        access(u), v->splay();
        if(v->fa == u) {
            v->fa = null;
        } else {
            access(v), u->splay(), u->fa = null;
        }
    }
    void link(int a, int b) {
        Node* u = node + a;
        Node* v = node + b;
        make_root(u);
        u->fa = v;
    }
    void make_root(Node* u) {
        Node* tmp = access(u);
        tmp->flip();
        u->splay();
    }
}lct;
int val[N];
int head[N];
int pnt[N * 2];
int nxt[N * 2];
int E;
void add_edge(int a, int b)
{
    pnt[E] = b;
    nxt[E] = head[a];
    head[a] = E++;
}
void dfs(int u, int f)
{
    for(int i = head[u]; i != -1; i = nxt[i]) {
        int v = pnt[i];
        if(v == f) {
            continue;
        }
        dfs(v, u);
        lct.node[v].fa = (lct.node + u);
    }
}
int main()
{
    null = new Node(); null->sz = 0;
    null->cnt[0] = null->cnt[1] = 0;
    null->val = null->mx[0] = null->mx[1] = null->same = -inf;
    null->rev = null->add = 0;
    null->ch[0] = null->ch[1] = null->fa = null;
    int t, ca = 1, a, b, n, m;
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d", &n, &m);
        E = 0;
        std::fill(head, head + n + 1, -1);
        for(int i = 1; i <= n; i++) {
            scanf("%d", &val[i]);
            lct.node[i].init(val[i]);
        }
        for(int i = 0; i < n - 1; i++) {
            scanf("%d%d", &a, &b);
            add_edge(a, b);
            add_edge(b, a);
        }
        dfs(1, -1);
        int c,d,x,y;
        printf("Case #%d:\n", ca++);
        while(m --) {
            scanf("%d", &c);
            if(c == 1) {
                scanf("%d%d%d%d", &x, &y, &a, &b);
                lct.cut(x, y);
                lct.link(a, b);
            } else if(c == 2) {
                scanf("%d%d%d", &a, &b, &x);
                lct.make_same(a, b, x);
            } else if(c == 3) {
                scanf("%d%d%d", &a, &b, &d);
                lct.add_value(a, b, d);
            } else {
                scanf("%d%d", &a, &b);
                lct.solve(a, b);
            }
        }
    }
    return 0;
}
/*
 * 444
7 7
5 3 2 1 7 3 6
1 2
1 3
3 4
3 5
4 6
4 7
4 2 6
*/
