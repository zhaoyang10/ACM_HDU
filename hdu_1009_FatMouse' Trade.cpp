#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<set>
#include<map>
#include<cmath>
using namespace std;
#define eps 1e-8
#define N 1010
int ord[N];
double J[N],F[N];

bool cmp(int x,int y){
    return J[x]/F[x] > J[y]/F[y];
}


int main()
{
    int n,i,j;
    double m,tmp,ans;
    while(~scanf("%lf%d",&m,&n)){
        if(m + 1 < eps && n == -1)  break;
        for(i=0; i<n; i++)  scanf("%lf%lf",J+i,F+i),ord[i]=i;
        sort(ord,ord+n,cmp);
        /*for(i=0; i<n; i++){
            printf("ord[%d] : %d  %lf\n",i,ord[i],J[ord[i]]/F[ord[i]]);
        }*/
        ans = 0.0;
        for(i=0; i<n && m>eps; i++){
            if(fabs(F[ord[i]]) < eps) continue;
            tmp = min(m,F[ord[i]]);
            ans += J[ord[i]] * tmp / F[ord[i]];
            m -= tmp;
        }
        for(i=0; i<n; i++)  if(fabs(F[ord[i]]) < eps) ans += J[ord[i]];
        printf("%.3lf\n",ans);
    }
    return 0;
}
