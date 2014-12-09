#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
const double eps = 1e-8;
struct point {
    double x,y;
    point operator - (const point& t) const {
        point tmp;
        tmp.x = x - t.x;
        tmp.y = y - t.y;
        return tmp;
    }
    point operator + (const point& t) const {
        point tmp;
        tmp.x = x + t.x;
        tmp.y = y + t.y;
        return tmp;
    }
    bool operator == (const point& t)const {
        return fabs(x-t.x) < eps && fabs(y-t.y) < eps;
    }
}p[100010];
struct line{
    point a,b;
};
int top;
bool cmpxy(point a,point b){
    if(a.y==b.y)
        return a.x<b.x;
    return a.y<b.y;
}
double cross(point a,point b,point c){
    return (b.x-a.x)*(c.y-a.y)-(c.x-a.x)*(b.y-a.y);
}
void tubao(point *p, int n) {                           
    if ( n < 3 ) 
        return;
    int i, m=0;top=1;
    sort(p, p+n, cmpxy);    
    for (i=n; i < 2*n-1; i++)
        p[i] = p[2*n-2-i];
    for (i=2; i < 2*n-1; i++) {
        while ( top > m && cross(p[top], p[i], p[top-1]) < eps ) 
            top--;
        p[++top] = p[i];
        if ( i == n-1 ) m = top;
    }
}
point gravi(point* p, int n) {                          
    int i;
    double A=0, a;
    point t;
    t.x = t.y = 0;
    p[n] = p[0];
    for (i=0; i < n; i++) {
        a = p[i].x*p[i+1].y - p[i+1].x*p[i].y;
        t.x += (p[i].x + p[i+1].x) * a;
        t.y += (p[i].y + p[i+1].y) * a;
        A += a;
    }
    t.x /= A*3;
    t.y /= A*3;
    return t;
}
point intersection(point u1,point u2,point v1,point v2){
    point ret=u1;
    double t=((u1.x-v1.x)*(v1.y-v2.y)-(u1.y-v1.y)*(v1.x-v2.x))
            /((u1.x-u2.x)*(v1.y-v2.y)-(u1.y-u2.y)*(v1.x-v2.x));
    ret.x+=(u2.x-u1.x)*t;
    ret.y+=(u2.y-u1.y)*t;
    return ret;
}
point ptoline(point p,point l1,point l2){
    point t=p;
    t.x+=l1.y-l2.y,t.y+=l2.x-l1.x;
    return intersection(p,t,l1,l2);
}
bool dot_onseg(point p, point s, point e) {     
    if ( p == s || p == e ) 
        return false;
    return cross(p,s,e) < eps  && 
        (p.x-s.x)*(p.x-e.x)<eps && (p.y-s.y)*(p.y-e.y)<eps;
}
int main()
{
    int t,i,j,n;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(i=0;i<n;i++)
            scanf("%lf%lf",&p[i].x,&p[i].y);
        point cen=gravi(p,n); 
        tubao(p,n);
        line seg;point m; 
        int count=0;
        for(i=0;i<top;i++)
        {
            m=ptoline(cen,p[i],p[i+1]);
            if(dot_onseg(m,p[i],p[i+1]))
                count++;
        }
        printf("%d\n",count);
    }
    return 0;
}
