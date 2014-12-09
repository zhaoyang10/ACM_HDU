#include<iostream>
#include<cassert>
#include<algorithm>
#include<cstdio>
#include<complex>
#include<cmath>
using namespace std;
// template
typedef complex<double> pnt;
typedef pair<pnt,double> circle;
const int N = 1005;
const double eps = 1e-10;
const double pi = acos(-1.0);
inline bool eq(double a, double b){return abs(b-a) < eps;}
inline double fix(double arg) {
    while(arg > pi) arg -= 2*pi;
    while(arg <= -pi) arg += 2*pi;
    return arg;
}
circle num[N];
struct line {
    int id,c;
    double arg;
    line(){}
    line(int _id,int _c,double _arg) :
    id(_id) , c(_c), arg(_arg){
//        cout<<"add: "<<id<<" "<<arg<<" "<<c<<endl;
    }
    bool operator < (const line& A) const{
        return eq(arg , A.arg) ? c > A.c : arg < A.arg;
    }
} Line[N<<2];
// cut line
#define ht first
#define rs second
inline void cut_line(const circle &A, const circle &B, int& ans, int& cnt,const int& id) {
    double d = abs(A.ht - B.ht) ;
    if(d <= abs(A.rs - B.rs)) {
        if(d <= B.rs - A.rs ) {ans ++; return ;}
        if(eq(d , A.rs - B.rs) ) {
            Line[cnt++] = line(id, 1 , arg(B.ht - A.ht));
            Line[cnt++] = line(id,-1 , arg(B.ht - A.ht));
        }
        return ;
    }
    double t;
    t = acos((A.rs - B.rs)/ d);
    double ag = arg(B.ht - A.ht);
    Line[cnt++] = line(id, 1 , fix(ag-t));
    Line[cnt++] = line(id,-1 , fix(ag+t));
    if(d > A.rs + B.rs + eps) {
        double t = acos((A.rs + B.rs)/d);
        Line[cnt++] = line(id, 1 , fix(ag+t));
        Line[cnt++] = line(id,-1 , fix(ag-t));
    }
}
// solve
bool vis[N];
int work(int n, int len){
    int ans = 0, sum = 0;
    for(int i=0;i<n;i++){
        vis[i] = 0;
    }
    for(int i=0;i<len+len;i++) {
        int k = i%len;
        int id = Line[k].id;
        int c = Line[k].c;
        if(c == 1){
            assert(vis[id]==0);
            vis[id] = 1; sum ++;
        }
        else if(c == -1) {
            if(vis[id] == 1)
                sum --, vis[id] = 0;
        }
        if(sum > ans ) ans = sum;
    }
    return ans;
}
// main
int main(){
    int cas;
    cin >> cas;
    for(int oo=1; oo<= cas; oo++) {
        int n,len = 0;
        scanf("%d",&n);
        for(int i=0;i<n;i++) {
            int x,y,r;
            scanf("%d%d%d",&x,&y,&r);
            num[i] = make_pair(pnt(x,y) , r);
        }
        int ans = 0;
        for(int s = 0; s < n; s ++) {
//            cout<<"start: "<<s<<endl;
            len = 0; int sum = 1;
            for(int i=0;i< n; i++) if(i!=s) 
                cut_line(num[s] , num[i], sum, len, i);
            sort(Line, Line + len);
            sum += work(n,len);
            if(sum > ans) ans = sum;
        }
        printf("Case #%d: %d\n",oo, ans);
    }
}
