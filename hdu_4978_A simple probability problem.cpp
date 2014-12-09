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
double cross(pt a,pt b,pt c){return (b-a)*(c-a);}
double length(pt a){return sqrt(a.x*a.x+a.y*a.y);}


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
    return cn;
}

int main(){
    int T, n, i, cas;
    double ans, d;
    scanf("%d", &T);
    for(cas = 1; cas <= T; cas ++)
    {
        scanf("%d%lf", &n, &d);
        for(i = 0; i < n; i ++) scanf("%lf%lf", &p[i].x, &p[i].y);
        n = convex(p, n, cp);
        cp[n] = cp[0];  ans = 0;
        for(i = 0; i < n; i ++) ans += length(p[cp[i + 1]] - p[cp[i]]);
        ans /= (pi * d);
        printf("Case #%d: %.4lf\n", cas, ans);
    }
    return 0;
}
