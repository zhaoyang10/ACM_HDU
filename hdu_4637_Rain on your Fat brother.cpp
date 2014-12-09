#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<vector>
using namespace std;
#define eps (1e-9)
#define N 1010

const double pi=acos(-1.0);
double degtorad(double deg){return deg/180.0*pi;}
double radtodeg(double rad){return rad*180.0/pi;}

double fabs(double d){return d<0?-d:d;}//特别注意写法，防止-0.00
int dcmp(double d){return (fabs(d)<eps)?0:(d>0?1:-1);}

struct pt{
    double x,y; int value;
    pt(){}
    pt(double x,double y):x(x),y(y){};
    pt operator +(pt b){return pt(x+b.x,y+b.y);}
    pt operator -(pt b){return pt(x-b.x,y-b.y);}
    pt operator *(double k){return pt(x*k,y*k);}
    pt operator /(double k){return pt(x/k,y/k);} //k!=0
    double operator *(pt b){return x*b.y-b.x*y;} //cross sin<a,b>
    double operator %(pt b){return x*b.x+y*b.y;} //dot cos<a,b>
    bool operator <(const pt &b)const{return dcmp(y-b.y)==0?x<b.x:y<b.y;}
    bool operator ==(pt b){return dcmp(x-b.x)==0&&dcmp(y-b.y)==0;}
};
double cross(pt a,pt b,pt c){return (b-a)*(c-a);}
double dot(pt a,pt b,pt c){return (b-a)%(c-a);}
double length(pt a){return sqrt(a.x*a.x+a.y*a.y);}
double angle(pt a,pt b){return acos(a%b/length(a)/length(b));}
double area2(pt a,pt b,pt c){return (b-a)*(c-a);}//abc有向面积两倍


pt rotate(pt a,double rad){//绕原点逆时针旋转
    return pt(a.x*cos(rad)-a.y*sin(rad),a.x*sin(rad)+a.y*cos(rad));
}

pt normal(pt a){//求单位法线，左转90°规格化
    double l=length(a);
    return pt(-a.y/l,a.x/l);
}

double disptol(pt p,pt a1,pt a2){//点到直线距离,两直线距离取一点即可
    pt v1=a2-a1,v2=p-a1;
    return fabs(v2*v1/length(v1));
}

double disptos(pt p,pt a1,pt a2){//点到线段距离
    if (a1==a2) return length(a1-a2);
    pt v1=a2-a1,v2=p-a1,v3=p-a2;
    if (dcmp(v1%v2)<0) return length(v2);
    else if (dcmp(v1%v3)>0) return length(v3);
    else return fabs(v2*v1/length(v1));
}

int pons1(pt p,pt a1,pt a2){//点在线段上(含端点),0,1, 在直线上只需要叉积等于0即可
    //printf("p : %lf %lf a1 : %lf %lf a1 : %lf %lf\n", p, a1, a2);
    //return ((dcmp((a1-p)*(a2-p))==0)&&(dcmp((a1-p)%(a2-p))<=0));
    return (dcmp((a1-p)*(a2-p))==0);//&&(dcmp((a1-p)%(a2-p))<=0));
}

int pons2(pt p,pt a1,pt a2){//点在线段上(含端点),0,1, 在直线上只需要叉积等于0即可
    //printf("p : %lf %lf a1 : %lf %lf a1 : %lf %lf\n", p, a1, a2);
    return ((dcmp((a1-p)*(a2-p))==0)&&(dcmp((a1-p)%(a2-p))<=0));
    //return (dcmp((a1-p)*(a2-p))==0);//&&(dcmp((a1-p)%(a2-p))<=0));
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


//三角形
struct triangle{
    pt p[3];
    triangle(){};
    triangle(pt pa, pt pb, pt pc){p[0]=pa;  p[1]=pb;    p[2]=pc;}

}trg[N];

//圆--------------------------
struct circle{
    pt p;
    double r;
    circle(){};
    circle(pt p,double r):p(p),r(r){}
    pt getpt(double a){
        return pt(p.x+cos(a)*r,p.y+sin(a)*r);
    }
}cl[N];

bool in(pt p1, pt p2, pt p3)
{
    return (p3.x - p2.x > -eps && p1.x - p3.x > -eps);
}

bool inc(circle c, pt p)
{
    return (c.p.y - p.y > eps);
}

//圆与直线交点
int linsc(pt a1,pt a2,circle c,double &t1,double &t2,vector<pt>& sol){
    pt v=a2-a1;
    double a=v.x,b=a1.x-c.p.x,d=v.y,f=a1.y-c.p.y;
    double aa=a*a+d*d,bb=2*(a*b+d*f),cc=b*b+f*f-c.r*c.r;
    double delta=bb*bb-4*aa*cc;
    if (dcmp(delta)<0) return 0;//相离
    if (dcmp(delta)==0){//相切
        return 1;
    }
    //相交
    pt p1, p2;
    t1=(-bb-sqrt(delta))/(2*aa);    t2=(-bb+sqrt(delta))/(2*aa);
    p1 = a1+v*t1;   p2 = a1+v*t2;   if(p1.y - p2.y > eps)   swap(p1, p2);
    if(inc(c, p1))
    {
        p1.value = 1;
        sol.push_back(p1);
        if(inc(c, p2))
        {
            p2.value = -1;
            sol.push_back(p2);
        }else{
            double deltay = c.p.y - a1.y;
            double deltax = v.x * deltay / v.y;
            p2 = pt(a1.x + deltax, c.p.y);
            p2.value = -1;
            sol.push_back(p2);
        }
    }
    return 2;
}

void triangleLineIntersection(pt pa, pt pb, triangle trg, vector<pt>& sol)
{
    pt p[5];    int i, j, now = 0;
    //puts("step 0");
    if(parallel(trg.p[1], trg.p[2], pa, pb))
    {
        //puts("in parallel");
        if(pons1(trg.p[1], pa, pb))
        {
            //puts("one line");
            if(pa.y - trg.p[1].y > -eps && pa.y - trg.p[2].y > -eps)    return;
            if(pb.y - trg.p[1].y < eps && pb.y - trg.p[2].y < eps)      return;
            if(trg.p[1].y - trg.p[2].y > eps)   p[2] = trg.p[2], p[3] = trg.p[1];
            else                                p[2] = trg.p[1], p[3] = trg.p[2];
            if(p[2].y - pa.y < eps)     p[2] = pa;
            if(p[3].y - pb.y > -eps)    p[3] = pb;
            //printf("trg.p[1] : %lf %lf\ntrg.p[2] : %lf %lf\npa : %lf %lf\npb : %lf %lf\np2 : %lf %lf\np3 : %lf %lf\n", \
            //       trg.p[1].x, trg.p[1].y, trg.p[2].x, trg.p[2].y, pa.x, pa.y, pb.x, pb.y, p[2].x, p[2].y, p[3].x, p[3].y);
            p[2].value = 1; p[3].value = -1;

            sol.push_back(p[2]);    sol.push_back(p[3]);
            return;
        }
        //puts("out parallel");
    }
    //puts("step 1");
    for(i = 0; i < 3; i ++)
    {
        j = (i + 1) % 3;
        if(!parallel(pa, pb, trg.p[i], trg.p[j]))
        {
            p[4] = intersection(pa, pb, trg.p[i], trg.p[j]);
            if(pons2(p[4], trg.p[i], trg.p[j]))
                p[now ++] = p[4];
        }
    }
    //puts("step 2");
    if(now <= 1)    return;
    if(now == 3)
    {
        sort(p, p + 3);
        if(p[0] == p[1])    p[1] = p[2];
    }
    p[0].value = 1;         p[1].value = -1;
    sol.push_back(p[0]);    sol.push_back(p[1]);
    //puts("step 3");
}

pt pa, pb;
vector<pt> sp;

void outvec()
{
    for(int i = 0; i < sp.size(); i ++) printf("%d : %lf %lf %d\n", i, sp[i].x, sp[i].y, sp[i].value);
}

double solve(int n)
{
    int i, j, flag = 0, sz;
    double t1, t2, ans = 0.0;
    sp.clear();
    for(i = 1; i <= n; i ++)
    {
        //printf("%d : ", i);
        linsc(pa, pb, cl[i], t1, t2, sp);
        //printf("circle ok.  \n");
        //outvec();
        triangleLineIntersection(pa, pb, trg[i], sp);
        //printf("triangle ok.\n");
        //outvec();
    }
    //system("pause");
    pa.value = 0;   pb.value = 0;   sp.push_back(pa);   sp.push_back(pb);
    sort(sp.begin(), sp.end());
    //puts("sorted.");
    //outvec();
    for(i = 0, sz = sp.size() - 1; i < sz; i ++)
    {
        if(sp[i].y - pb.y > -eps)   break;
        flag += sp[i].value;
        if(flag > 0 && (sp[i].y - pa.y > -eps))
        {
            ans += sp[i].x - sp[i + 1].x;
        }
        //printf("%d : ans = %.4lf flag = %d\n", i, ans, flag);
    }
    return ans;
}

int main(){
    int T, cas, i, n;
    double v1, v2, v, t, x, ax, ay, ar, ah, ans;
    //freopen("out2.txt", "w", stdout);
    scanf("%d", &T);

    for(cas = 1; cas <= T; cas ++)
    {
        scanf("%lf%lf%lf%lf%lf", &v1, &v2, &v, &t, &x);
        t = (v1 * t) / (v2 - v1) + t;
        pa = pt(x, 0);  pb = pt(x - v1 * t, v * t);
        scanf("%d", &n);
        for(i = 1; i <= n; i ++)
        {
            scanf("%lf%lf%lf%lf", &ax, &ay, &ar, &ah);
            cl[i] = circle(pt(ax, ay), ar);
            trg[i] = triangle(pt(ax-ar,ay), pt(ax+ar,ay), pt(ax,ay+ah));
        }
        ans = solve(n);
        printf("Case %d: %.4lf\n", cas, ans/v1);
    }
    return 0;
}
