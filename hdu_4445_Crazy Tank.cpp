#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const double g = 9.8;
const double PI = acos(-1.0);
#define nMax 300
#define eps 1e-8

double H,L1,L2,R1,R2;
double v[nMax],vv[nMax];

inline double getPos(double V,double Sin,double Cos)
{
    double res = V*Sin;
    res *= ( sqrt( V*V*Cos*Cos + 2.0*g*H ) - V*Cos );
    return res;
}

int main()
{
    double Ang,pos;
    int i,j,Max,num,n;
    bool flag;
    while(~scanf("%d",&n),n){
        scanf("%lf%lf%lf%lf%lf",&H,&L1,&R1,&L2,&R2);
        for(i=0;i<n;i++)    scanf("%lf",v+i);
        for(i=0;i<n;i++)    vv[i]=v[i]*v[i];
        Max = 0;
        L1 *= g;    L2 *= g;    R1 *= g;    R2 *= g;
        //printf("---cos(%lf)=%lf\n",PI,cos(PI));
        for( double tAng = 0; tAng < 180 + eps; tAng += 0.1){
            //printf("Ang = %lf\n",Ang);
            flag = true;    num = 0;
            Ang = tAng*PI/180;
            double Sin = sin(Ang) , Cos = cos(Ang), Sin2 = Sin*Sin, Cos2 = Cos*Cos;
            for( i=0; i<n; i++ ){
                pos = getPos( v[i],Sin,Cos );
            //    if( Ang - floor(Ang) <= eps )    printf("Ang = %lf\tpos = %lf\n",Ang,pos);
                if( pos >= L2 - eps && pos <= R2 + eps ){
                    flag = false;
                    break;
                }
                if( pos >= L1 - eps && pos <= R1 + eps ){
                    num ++;
                }
            }
        /*
            for( i=0; i<n; i++ ){
                double tmp = vv[i]*Sin2*( vv[i]*Cos2 + 2.0*g*H );
                double tmp1 = vv[i]*Sin*Cos;
                if( ( L2 + tmp1 ) * ( L2 + tmp1 ) - eps < tmp && ( R2 + tmp1 )*( R2 + tmp1 ) + eps > tmp ){
                    flag = false;
                    break;
                }
                if( ( L1 + tmp1 ) * ( L1 + tmp1 ) - eps < tmp && ( R1 + tmp1 )*( R1 + tmp1 ) + eps > tmp ){
                    num ++;
                }
            }
            */
            if( flag && Max < num )    Max = num;
        }
        printf("%d\n",Max);
    }
    return 0;
}
