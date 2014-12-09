#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<vector>
using namespace std;
#define eps (1e-9)
#define NN 1010

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
};
//圆--------------------------
struct circle{
    pt p;
    double r;
    circle(){};
    circle(pt p,double r):p(p),r(r){}
    pt getpt(double a){
        return pt(p.x+cos(a)*r,p.y+sin(a)*r);
    }
};

double cross(pt a,pt b,pt c){return (b-a)*(c-a);}
double length(pt a){return sqrt(a.x*a.x+a.y*a.y);}

pt rotate(pt a,double rad){//绕原点逆时针旋转
    return pt(a.x*cos(rad)-a.y*sin(rad),a.x*sin(rad)+a.y*cos(rad));
}


pt getinter(pt a,pt b,pt c,pt d){//ab cd直线交点,线段需先判断是否相交
    double s1=(b-a)*(c-a);
    double s2=(b-a)*(d-a);
    pt p;
    p.x=(c.x*s2-d.x*s1)/(s2-s1);
    p.y=(c.y*s2-d.y*s1)/(s2-s1);
    return p;
}

//外接圆，垂直平分线交点
circle getcircumcircle(pt a,pt b,pt c){
    circle ret;
    pt p1=(a+b)/2,p2=(a+b)/2+rotate(b-a,pi/2);
    pt p3=(c+b)/2,p4=(c+b)/2+rotate(b-c,pi/2);
    ret.p=getinter(p1,p2,p3,p4);
    ret.r=length(ret.p-a);
    return ret;
}

//凸包 andrew O(nlogn))------------------------------------
pt p[NN];
int cp[NN];

int convex(pt p[],int n,int cp[]){
    sort(p,p+n);
    int i,up,cn=0;      //凸包上总点数cn，点的编号存放在cp[0..cn-1]中。
    for (i=0;i<n;i++){
        while (cn>1 && cross(p[cp[cn-2]],p[cp[cn-1]],p[i])<eps) cn--;//<eps不记录共线点
        cp[cn++]=i;                                                  //<-eps记录共线点,必须去重点
    }
    up=cn;
    for (i=n-1;i>=0;i--){
        while (cn>up && cross(p[cp[cn-2]],p[cp[cn-1]],p[i])<eps) cn--;
        cp[cn++]=i;
    }
    if(cn>1)  cn--;
    return cn;
}


int main(){
    int n, i, j, k;
    double ans, r, t;
    while(~scanf("%d", &n) && n)
    {
        for(i = 0; i < n; i ++) scanf("%lf%lf", &p[i].x, &p[i].y);
        if(n == 1)
        {
            puts("0.50");
            continue;
        }else if(n == 2){
            printf("%.2lf\n", length(p[0] - p[1])/2 + 0.5);
            continue;
        }
        n = convex(p, n, cp);
        r = 0.0;
        pt a, b, c;
        for(i = 0; i < n; i ++)
        {
            for(j = i + 1; j < n; j ++)
            {
                for(k = j + 1; k < n; k ++)
                {
                //if(cross(p[cp[i]], p[cp[j]], p[cp[k]]) < eps || cross(p[cp[j]], p[cp[i]], p[cp[k]]) < eps || cross(p[cp[k]], p[cp[j]], p[cp[i]]) < eps)
                    a = p[cp[i]] - p[cp[j]];    b = p[cp[j]] - p[cp[k]];    c = p[cp[k]] - p[cp[i]];
                    if(a%a > b%b + c%c || b%b > a%a + c%c || c%c > a%a + b%b)
                    {
                        r = max(r, length(p[cp[i]] - p[cp[j]]) / 2);
                        r = max(r, length(p[cp[i]] - p[cp[k]]) / 2);
                        r = max(r, length(p[cp[j]] - p[cp[k]]) / 2);
                    }else{
                        r = max(r, getcircumcircle(p[cp[i]], p[cp[j]], p[cp[k]]).r);
                    }
                }
            }
        }
        printf("%.2lf\n", r+0.5);
    }
    return 0;
}
