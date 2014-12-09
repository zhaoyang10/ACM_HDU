#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<vector>
#include<set>
using namespace std;
#define eps (1e-9)
#define N 100000

const double pi=acos(-1.0);
double degtorad(double deg){return deg/180.0*pi;}
double radtodeg(double rad){return rad*180.0/pi;}

double fabs(double d){return d<0?-d:d;}//特别注意写法，防止-0.00
int dcmp(double d){return (fabs(d)<eps)?0:(d>0?1:-1);}

struct pt{
    double x,y;
    pt(){}
    pt(double x,double y):x(x),y(y){};
    pt operator +(pt b){return pt(x+b.x,y+b.y);}
    pt operator -(pt b){return pt(x-b.x,y-b.y);}
    pt operator *(double k){return pt(x*k,y*k);}
    pt operator /(double k){return pt(x/k,y/k);} //k!=0
    double operator *(pt b){return x*b.y-b.x*y;} //cross sin<a,b>
    double operator %(pt b){return x*b.x+y*b.y;} //dot cos<a,b>
    bool operator <(const pt &b)const{return dcmp(y-b.y)==0?x<b.x:y<b.y;}
    bool operator ==(const pt &b)const{return dcmp(x-b.x)==0&&dcmp(y-b.y)==0;}
};
double cross(pt a,pt b,pt c){return (b-a)*(c-a);}
double dot(pt a,pt b,pt c){return (b-a)%(c-a);}
double length(pt a){return sqrt(a.x*a.x+a.y*a.y);}


int pons(pt p,pt a1,pt a2){//点在线段上(含端点),0,1, 在直线上只需要叉积等于0即可
    return dcmp((a1-p)*(a2-p))==0&&dcmp((a1-p)%(a2-p))<=0;
}

int scross1(pt a,pt b,pt c,pt d){//线段规范相交，不计端点,0,1
    return dcmp((b-a)*(c-a))*dcmp((b-a)*(d-a))==-1&&
           dcmp((d-c)*(a-c))*dcmp((d-c)*(b-c))==-1;
}

int scross2(pt a,pt b,pt c,pt d){//线段相交含端点 0,1,-1
    if (scross1(a,b,c,d)) return 1;//规范相交
    if (pons(c,a,b)||pons(d,a,b)||pons(a,c,d)||pons(b,c,d)) return -1;//在端点相交
    return 0;//不相交
}

int parallel(pt u1, pt u2, pt v1, pt v2) //直线平行 u1u2 // v1v2
{
    return fabs((u2-u1)*(v2-v1))<eps;
}

pt intersection(pt u1, pt u2, pt v1, pt v2) //直线交点 u1u2 X v1v2 需先判断是否平行！！
{
    double t=((u1.x-v1.x)*(v1.y-v2.y)-(u1.y-v1.y)*(v1.x-v2.x))
            /((u1.x-u2.x)*(v1.y-v2.y)-(u1.y-u2.y)*(v1.x-v2.x));
    return pt(t*(u2.x-u1.x)+u1.x,t*(u2.y-u1.y)+u1.y);
}


pt getinter(pt a,pt b,pt c,pt d){//ab cd直线交点,线段需先判断是否相交
    double s1=(b-a)*(c-a);
    double s2=(b-a)*(d-a);
    pt p;
    p.x=(c.x*s2-d.x*s1)/(s2-s1);
    p.y=(c.y*s2-d.y*s1)/(s2-s1);
    return p;
}

struct Line{
    pt p[2];
    int value;
    Line(){}
    Line(pt p0, pt p1){p[0]=p0;p[1]=p1;}
    bool operator<(const Line & L)const{return (this->p[0]==L.p[0])?(this->p[1]<L.p[1]):(this->p[0]<L.p[0]);}
};

set<double>sx;
set<double>::iterator i1, i2;
vector<Line>sl;
int n, tot;
double ans[55];

struct Triangle{
    pt p[3];
    void sort(){std::sort(p, p+3);}
    void insert(vector<Line> & s)
    {
        s.push_back(Line(p[0], p[1]));
        s.push_back(Line(p[1], p[2]));
        s.push_back(Line(p[0], p[2]));
    }
}tr[N];

void inters(Line l1, Line l2)
{
    int kind = scross2(l1.p[0], l1.p[1], l2.p[0], l2.p[1]);
    if(kind == 0)   return;
    if(kind == -1)
    {
        if(pons(l1.p[0], l2.p[0], l2.p[1])) sx.insert(l1.p[0].x);
        if(pons(l1.p[1], l2.p[0], l2.p[1])) sx.insert(l1.p[1].x);
        if(pons(l2.p[0], l1.p[0], l1.p[1])) sx.insert(l2.p[0].x);
        if(pons(l2.p[1], l1.p[0], l1.p[1])) sx.insert(l2.p[1].x);
    }else if(kind == 1)
    {
        sx.insert(intersection(l1.p[0], l1.p[1], l2.p[0], l2.p[1]).x);
    }
}

void verticle(double x1, double x2, vector<Line>& s)
{
    int i, j, k;   pt pa, pb;  Line L;
    for(i = 0; i < n; i ++)
    {
        if(parallel(tr[i].p[0], tr[i].p[1], tr[i].p[1], tr[i].p[2]))    continue;
        for(j = 0; j < 3; j ++)
        {
            pa = tr[i].p[j];    pb = tr[i].p[(j + 1) % 3];
            if(fabs(pa.x - pb.x) < eps) continue;
            if(pa.x - pb.x > eps)   swap(pa, pb);
            if(pa.x - x2 > -eps || x1 - pb.x > -eps)  continue;
            pa.y = pb.y + (pa.y - pb.y) * (x1 - pb.x) / (pa.x - pb.x); pa.x = x1;
            pb.y = pa.y + (pb.y - pa.y) * (x2 - pa.x) / (pb.x - pa.x); pb.x = x2;
            L.p[0] = pa;    L.p[1] = pb;        k = (j + 2) % 3;
            pa.y = pb.y + (pa.y - pb.y) * (tr[i].p[k].x - pb.x) / (pa.x - pb.x);
            if(pa.y - tr[i].p[k].y > eps)   L.value = -1;
            if(tr[i].p[k].y - pa.y > eps)  L.value = 1;
            s.push_back(L);
        }
    }
}

void cal(double x1, double x2)
{
    int i, sz, value = 0;
    double y1 = 0, y2 = 0, mul = (x2 - x1) / 2.0;
    for(i = 0, sz = sl.size(); i < sz; i ++)
    {
        if(sl[i].p[0].x - sl[i].p[1].x > eps) swap(sl[i].p[0], sl[i].p[1]);
        ans[value] += mul * (sl[i].p[0].y - y1 + sl[i].p[1].y - y2);
        value += sl[i].value;   y1 = sl[i].p[0].y;    y2 = sl[i].p[1].y;
    }
}

int main(){
    int T, i, j;
    //freopen("1009.in", "r", stdin);
    //freopen("10090.out", "w", stdout);
    scanf("%d", &T);
    while(T --)
    {
        scanf("%d", &n);
        sl.clear(); sx.clear();
        memset(ans, 0, sizeof(ans));
        for(i = 0; i < n; i ++)
        {
            for(j = 0; j < 3; j ++)
                scanf("%lf%lf", &tr[i].p[j].x, &tr[i].p[j].y);
            tr[i].sort();
            tr[i].insert(sl);
        }
        for(i = 0; i < sl.size(); i ++)
            for(j = i + 1; j < sl.size(); j ++)
                inters(sl[i], sl[j]);

        for(i1 = i2 = sx.begin(), i2 ++; i2 != sx.end();)
        {
            if((*i2) - (*i1) < eps){
                sx.erase(i1);
                //i1 = i2 = sx.begin();    i2 ++;
                i1 = i2;    i2 ++;
            }else{
                i1 ++; i2 ++;
            }
        }
        for(i1 = i2 = sx.begin(), i2 ++; i2 != sx.end(); i1 ++, i2 ++)
        {
            sl.clear();
            verticle(*i1, *i2, sl);
            sort(sl.begin(), sl.end());
            cal(*i1, *i2);
        }
        for(i = 1; i <= n; i ++) printf("%.10lf\n", ans[i]);
    }
    return 0;
}

