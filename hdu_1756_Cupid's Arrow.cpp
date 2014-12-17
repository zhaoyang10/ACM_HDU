#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
#define sqr(a) ((a) * (a))
const double eps = 1e-9;
const int MAX_N = 110;
inline int sgn(const double &a) { return a > eps ? 1 : (a < -eps ? -1 : 0); }

struct Point{
    double x, y;
    Point(){ x = y = 0; }
    Point(double _x, double _y) : x(_x), y(_y){}
    Point operator + (const Point &a) const {
        return Point(x + a.x, y + a.y);
    }
    Point operator - (const Point &a) const {
        return Point(x - a.x, y - a.y);
    }
    Point operator * (const double &k) const {
        return Point(x * k, y * k);
    }
    Point operator / (const double &k) const {
        return Point(x / k, y / k);
    }
    /*******叉积 det， sin<a, b>********/
    double operator * (const Point &b) const {
        return x * b.y - y * b.x;
    }
    /*******点积 dot， cos<a, b>********/
    double operator % (const Point &b) const {
        return x * b.x + y * b.y;
    }
    Point& operator = (const Point &a){
        x = a.x;    y = a.y;
        return *this;
    }
    bool operator < (const Point &a) const {
        return sgn(x - a.x) < 0 || (!sgn(x - a.x) && sgn(y - a.y) < 0);
    }
    bool operator == (const Point &a) const {
        return !sgn(x - a.x) && !sgn(y - a.y);
    }
    bool operator != (const Point &a) const {
        return sgn(x - a.x) || sgn(y - a.y);
    }
    //法向量， 左手方向
    Point normal() const {
        return Point(-y, x);
    }
    void read(){
        scanf("%lf %lf", &x, &y);
    }
    void print(){
        printf("%.6lf %.6lf\n", x, y);
    }
};

inline double det(const Point &a, const Point &b, const Point &c){
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

struct Segment{
    Point a, b;
    Segment(): a(Point()), b(Point()) {}
    Segment(Point _a, Point _b) : a(_a), b(_b) {}
    Segment(double x1, double y1, double x2, double y2) : a(x1, y1), b(x2, y2) {}
};


inline bool pointOnSegment(const Point &a, const Segment &s){
    return !sgn(det(a, s.a, s.b))
            && sgn(min(s.a.x, s.b.x) - a.x) <= 0 && sgn(a.x - max(s.a.x, s.b.x)) <= 0
            && sgn(min(s.a.y, s.b.y) - a.y) <= 0 && sgn(a.y - max(s.a.y, s.b.y)) <= 0;
}

inline bool isIntersectSS(const Segment &sa, const Segment &sb){
    if( !sgn( det(sa.a, sa.b, sb.a) ) && !sgn( det(sa.a, sa.b, sb.b) ) ){
        return sgn( min(sa.a.x, sa.b.x) - max(sb.a.x, sb.b.x) ) <= 0
            && sgn( min(sb.a.x, sb.b.x) - max(sa.a.x, sa.b.x) ) <= 0
            && sgn( min(sa.a.y, sa.b.y) - max(sb.a.y, sb.b.y) ) <= 0
            && sgn( min(sb.a.y, sb.b.y) - max(sa.a.y, sa.b.y) ) <= 0;
    }
    /**********如果不包括端点则把<=改为<************/
    return det(sa.a, sb.a, sb.b) * det(sa.b, sb.a, sb.b) <= 0
            && det(sb.a, sa.a, sa.b) * det(sb.b, sa.a, sa.b) <= 0;
}


inline bool pointInsidePolygon(Point *p, int n, const Point &c) {
    Point infinity = Point(1e8 + rand(), 1e8 + rand());
    Segment seg(c, infinity);
    int i, cnt = 0;
    for(i = 0; i < n; i ++){
        if(pointOnSegment(c, Segment(p[i], p[(i + 1) % n]))){
            return true;
        }
        if(isIntersectSS(seg, Segment(p[i], p[(i + 1) % n]))){
            cnt ++;
        }
    }
    return cnt % 2 == 1;
}

Point p[MAX_N];
Point c;

int main()
{
    int n, m, i;
    while(~scanf("%d", &n)){
        for(i = 0; i < n; i ++){
            p[i].read();
        }
        scanf("%d", &m);
        for(i = 0; i < m; i ++){
            c.read();
            if(pointInsidePolygon(p, n, c)){
                puts("Yes");
            }else{
                puts("No");
            }
        }
    }
    return 0;
}
