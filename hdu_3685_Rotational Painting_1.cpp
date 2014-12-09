#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<vector>
using namespace std;
#define eps (1e-8)
#define NN 51010

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
    bool operator ==(pt b){return dcmp(x-b.x)==0&&dcmp(y-b.y)==0;}
    void output(){printf("x = %lf y = %lf\n", x, y);}
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

int parallel(pt u1, pt u2, pt v1, pt v2)
{
    return fabs((u2-u1)*(v2-v1))<eps;
}

pt intersection(pt u1, pt u2, pt v1, pt v2)
{
    double t=((u1.x-v1.x)*(v1.y-v2.y)-(u1.y-v1.y)*(v1.x-v2.x))
            /((u1.x-u2.x)*(v1.y-v2.y)-(u1.y-u2.y)*(v1.x-v2.x));
    return pt(t*(u2.x-u1.x)+u1.x,t*(u2.y-u1.y)+u1.y);
}

double getarea(pt p[],int n){//多边形有向面积，点有序，p[0..n-1]，顺时针小于零
    double res=0;
    p[n]=p[0];
    for(int i=0;i<n;i++) res+=p[i]*p[i+1]; //cross(O,p[i],p[i+1]);
    return res/2.0;
}

pt getcentroid(pt p[],int n){ //求重心 p[0..n-1];
    double tx=0,ty=0,tc;
    double a=getarea(p,n);
    p[n]=p[0];
    for(int i=0;i<n;i++)  {
        tc=p[i]*p[i+1];
        tx=tx+(p[i].x+p[i+1].x)*tc;
        ty=ty+(p[i].y+p[i+1].y)*tc;
    }
    return pt(tx/(6.0*a),ty/(6.0*a));
}

int pinpoly(pt a,pt p[],int n){//点与多边形位置关系
    int wn=0;
    p[n]=p[0];
    for(int i=0;i<n;++i){
        if (pons(a,p[i],p[i+1])) return -1;//边界
        int k=dcmp((p[i+1]-p[i])*(a-p[i]));
        int d1=dcmp(p[i].y-a.y);
        int d2=dcmp(p[i+1].y-a.y);
        if (k>0&&d1<=0&&d2>0) wn++;
        if (k<0&&d2<=0&&d1>0) wn--;
    }
    if (wn!=0) return 1;//内部
    return 0;//外部
}
//----------------------圆---------------------------
//凸包 andrew O(nlogn))------------------------------------
pt p[NN], con[NN];
int cp[NN];

int convex(pt p[],int n,int cp[]){
    sort(p,p+n);
    int i,up,cn=0;      //凸包上总点数cn，点的编号存放在cp[0..cn-1]中。
    for (i=0;i<n;i++){
        while ( cn>1 && cross(p[cp[cn-2]],p[cp[cn-1]],p[i])<eps) cn--;//<eps不记录共线点
        cp[cn++]=i;                                                  //<-eps记录共线点,必须去重点
    }
    up=cn;
    for (i=n-1;i>=0;i--){
        while (cn>up && cross(p[cp[cn-2]],p[cp[cn-1]],p[i])<eps) cn--;
        cp[cn++]=i;
    }
    if (n>1) cn--;
    return cn;
}

bool check(pt p, pt s, pt e)
{
    if(p == s || p == e)    return false;
    return fabs(cross(p,s,e)) < eps  &&
        (p.x-s.x)*(p.x-e.x)<eps && (p.y-s.y)*(p.y-e.y)<eps;
}

int main(){
    int T, n, m, i, ans; pt w, d, v, a, b, c;
    scanf("%d", &T);
    while(T --)
    {
        scanf("%d", &n);
        for(i = 0; i < n; i ++) scanf("%lf%lf", &p[i].x, &p[i].y);
        w = getcentroid(p, n);
        m = convex(p, n, cp);   cp[m] = cp[0];
        for(i = 0; i < m; i ++) con[i] = p[cp[i]];

        //printf("weight : ");    w.output();
        for(i = 0, ans = 0; i < m; i ++)
        {
            a = p[cp[i]] - p[cp[i + 1]];
            d.x = -a.y; d.y = a.x;
            v = intersection(p[cp[i]], p[cp[i + 1]], w, w + d);
            //if(check(v, p[cp[i]], p[cp[i + 1]]))    ans ++;
            if(pons(v, p[cp[i]], p[cp[i + 1]]) && !(p[cp[i]] == v) && !(p[cp[i + 1]] == v)) ans ++;
            //p[cp[i]].output();  p[cp[i + 1]].output();
            //a = p[cp[i + 1]] - p[cp[i]];    b = w - p[cp[i]];
            //c = p[cp[i]] - p[cp[i + 1]];    d = w - p[cp[i + 1]];
            //puts("line 1:"); a.output(); b.output();    printf("a*b = %lf\n", a%b);
            //puts("line 2:"); c.output(); d.output();    printf("c*d = %lf\n", c%d);
            //if( a%b < eps || c%d < eps)  continue;
            //else    ans ++;
//            printf("d : ");         d.output();
//            printf("%d : ans = %d\n", i, ans);
        }
        printf("%d\n", ans);
    }
    return 0;
}
