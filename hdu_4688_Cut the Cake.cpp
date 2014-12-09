#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include <stdlib.h>
using namespace std;
#define eps 1e-8
#define zero(x) (((x)>0?(x):-(x))<eps)
#define N 110
#define inf 1e10
struct point{double x,y;};
struct line{point a,b;};

//计算cross product (P1-P0)x(P2-P0)
double xmult(point p1,point p2,point p0){
    return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}
//graham算法顺时针构造包含所有共线点的凸包,O(nlogn)
point p1,p2;
int graham_cp(const void* a,const void* b){
    double ret=xmult(*((point*)a),*((point*)b),p1);
    return zero(ret)?(xmult(*((point*)a),*((point*)b),p2)>0?1:-1):(ret>0?1:-1);
}
void _graham(int n,point* p,int& s,point* ch){
    int i,k=0;
    for (p1=p2=p[0],i=1;i<n;p2.x+=p[i].x,p2.y+=p[i].y,i++)
        if (p1.y-p[i].y>eps||(zero(p1.y-p[i].y)&&p1.x>p[i].x))
            p1=p[k=i];
    p2.x/=n,p2.y/=n;
    p[k]=p[0],p[0]=p1;
    qsort(p+1,n-1,sizeof(point),graham_cp);
    for (ch[0]=p[0],ch[1]=p[1],ch[2]=p[2],s=i=3;i<n;ch[s++]=p[i++])
        for (;s>2&&xmult(ch[s-2],p[i],ch[s-1])<-eps;s--);
}

//构造凸包接口函数,传入原始点集大小n,点集p(p原有顺序被打乱!)
//返回凸包大小,凸包的点在convex中
//参数maxsize为1包含共线点,为0不包含共线点,缺省为1
//参数clockwise为1顺时针构造,为0逆时针构造,缺省为1
//在输入仅有若干共线点时算法不稳定,可能有此类情况请另行处理!
//不能去掉点集中重合的点
int graham(int n,point* p,point* convex,int maxsize=0,int dir=1){
    point* temp=new point[n];
    int s,i;
    _graham(n,p,s,temp);
    for (convex[0]=temp[0],n=1,i=(dir?1:(s-1));dir?(i<s):i;i+=(dir?1:-1))
        if (maxsize||!zero(xmult(temp[i-1],temp[i],temp[(i+1)%s])))
            convex[n++]=temp[i];
    delete []temp;
    return n;
}
double distance_zy(point p1,point p2){
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}

point intersection(line u,line v){
    point ret=u.a;
    double t=((u.a.x-v.a.x)*(v.a.y-v.b.y)-(u.a.y-v.a.y)*(v.a.x-v.b.x))
            /((u.a.x-u.b.x)*(v.a.y-v.b.y)-(u.a.y-u.b.y)*(v.a.x-v.b.x));
    ret.x+=(u.b.x-u.a.x)*t;
    ret.y+=(u.b.y-u.a.y)*t;
    return ret;
}

//判两直线平行
int parallel(line u,line v){
    return zero((u.a.x-u.b.x)*(v.a.y-v.b.y)-(v.a.x-v.b.x)*(u.a.y-u.b.y));
}


point p[N], cp[N*2], corner[4], xp[4];
line recl[4], L[N * 2];
int n, nn;
double w, h;
double len[N*2][4], dp[N*2][N*2], dcl[N*2][N*2];
bool crossL[N*2][N*2];

void getPoints(int a)
{

    if(zero(cp[a].x - cp[a + 1].x)){
        xp[0].x = xp[1].x = cp[a].x;
        xp[0].y = 0;   xp[1].y = h;
        if(distance_zy(xp[0], cp[a]) - distance_zy(xp[0], cp[a + 1]) > eps)
            swap(xp[0], xp[1]);
    }else if(zero(cp[a].y - cp[a + 1].y)){
        xp[0].y = xp[1].y = cp[a].y;
        xp[0].x = 0;   xp[1].x = w;
        if(distance_zy(xp[0], cp[a]) - distance_zy(xp[0], cp[a + 1]) > eps)
            swap(xp[0], xp[1]);
    }else{
        line l;
        l.a = cp[a];    l.b = cp[a + 1];
        int i, j;
        for(i = 0; i < 4; i ++)
        {
            xp[i] = intersection(l, recl[i]);
        }

        for(j = 0; j < 2; j ++)
            for(i = j + 1; i < 4; i ++)
            if(distance_zy(xp[i], cp[a]) - distance_zy(xp[i], cp[a + 1]) < eps)
            {
                //printf("dis %d = %lf\tdis %d = %lf\n", a, distance_zy(xp[i], cp[a]), a + 1, distance_zy(xp[i], cp[a + 1]));
                swap(xp[i], xp[j]);
                break;
            }
        if(distance_zy(xp[0], cp[a]) - distance_zy(xp[1], cp[a]) > eps)
            swap(xp[0], xp[1]);
        if(distance_zy(xp[2], cp[a + 1]) - distance_zy(xp[3], cp[a + 1]) > eps)
            swap(xp[3], xp[1]);
        else
            swap(xp[2], xp[1]);
    }
}

void getLen()
{
    int i, j;
    for(i = 0; i < n; i ++)
    {
        len[i + n][0] = len[i][0] = distance_zy(cp[i], cp[i + 1]);
        getPoints(i);
        len[i + n][1] = len[i][1] = distance_zy(cp[i], xp[0]);
        len[i + n][2] = len[i][2] = distance_zy(cp[i + 1], xp[1]);
        len[i + n][3] = len[i][3] = distance_zy(xp[0], xp[1]);
     /*   printf("%d : xp[0] : %lf %lf xp[1] : %lf %lf\n", i, xp[0].x, xp[0].y, xp[1].x, xp[1].y);
        for(j = 0; j < 4; j ++)
            printf("len[%d][%d] = %lf\n", i, j, len[i][j]);
            */
    }



}

void init()
{
    corner[0].x = 0;    corner[0].y = 0;
    corner[1].x = 0;    corner[1].y = h;
    corner[2].x = w;    corner[2].y = h;
    corner[3].x = w;    corner[3].y = 0;
    recl[0].a = corner[0];  recl[0].b = corner[1];
    recl[1].a = corner[1];  recl[1].b = corner[2];
    recl[2].a = corner[2];  recl[2].b = corner[3];
    recl[3].a = corner[3];  recl[3].b = corner[0];
    memset(crossL, 0, sizeof(crossL));
    int i, j;
    for(i = 0; i < n; i ++)
        cp[i + n] = cp[i];
    nn  = n * 2;
    for(i = 0; i < nn; i ++)
        L[i].a = cp[i], L[i].b = cp[(i + 1) % nn];
    for(i = 0; i < nn; i ++)
        for(j = 0; j < nn; j ++)
            dcl[i][j] = inf;
    for(i = 0; i < nn; i ++)
        for(j = 0; j < nn; j ++)
            if(i == j)  continue;
            else if(!parallel(L[i], L[j]))
            {
                p1 = intersection(L[i], L[j]);
                dcl[i][j] = min(distance_zy(p1, L[i].a), distance_zy(p1, L[i].b));
                if(distance_zy(p1, L[i].a) < distance_zy(p1, L[i].b))
                    crossL[i][j] = true;
                //printf("dcl[%d][%d] = %lf\n", i, j, dcl[i][j]);
            }
    getLen();
}

int main()
{
    int i, j, k, Len;
    double ans, tmp, tmpl, tmpr;

    //freopen("out.txt", "w", stdout);
    while(~scanf("%d%lf%lf", &n, &w, &h))
    {

        for(i = 0; i < n; i ++)
            scanf("%lf%lf", &p[i].x, &p[i].y);
        n = graham(n, p, cp);
/*
        for(i = 0; i < n; i ++)
        {
            printf("%d :%lf %lf\n", i, cp[i].x, cp[i].y);
        }

*/        init();
        getLen();
        int nn = n * 2;
        for(i = 0; i < nn; i ++)
            for(j = 0; j < nn; j ++)
                dp[i][j] = inf;

        for(i = 0; i < nn; i ++)
        {
            dp[i][i] = 0.0;
          //  printf("dp[%d][%d] = %lf\n", i, i, dp[i][i]);
        }

        for(Len = 2; Len <= n; Len ++)
            for(i = 0; i + Len <= nn; i ++)
            {
                j = i + Len - 1;
              //  printf("i = %d\tj = %d\n", i, j);
                for(k = i; k < j; k ++)
                {
                    //printf("k = %d\n", k);
                    tmp = dp[i][k] + dp[k + 1][j];
                    tmpl = len[k][1];   tmpr = len[k][2];
                    //printf("tmpl = %lf\ttmpr = %lf\n", tmpl, tmpr);
                    if(crossL[k][i - 1 < 0 ? n - 1 : i - 1])    tmpl = min(tmpl, dcl[k][i - 1 < 0 ? n - 1 : i - 1]);
                    else                                        tmpr = min(tmpr, dcl[k][i - 1 < 0 ? n - 1 : i - 1]);
                    if(crossL[k][j])                            tmpl = min(tmpl, dcl[k][j]);
                    else                                        tmpr = min(tmpr, dcl[k][j]);

                    //printf("tmpl = %lf\ttmpr = %lf\n", tmpl, tmpr);
                    tmp = tmp + tmpl + tmpr + len[k][0];
                    dp[i][j] = min(dp[i][j], tmp);
                }
                //printf("dp[%d][%d] = %lf\n", i, j, dp[i][j]);
            }

        ans = inf;
        for(i = 0; i < n; i ++)
        {
            ans = min(ans, dp[i][i + n - 1] + len[i + n - 1][3]);
        }
        printf("%.6lf\n", ans);
    }
    return 0;
}
