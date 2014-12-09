#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<cmath>
using namespace std;
#define N 3010
#define eps 1e-10
char s[N][N];
double mat[N][N];
double vec[2][N];
int num[N];
int n;

bool check()
{
    int i;
    double tmp = 0.0;
    for(i = 1; i <= n; i ++)
        if(fabs(vec[1][i] - vec[0][i]) > eps)
            return true;
    return false;
}

void print()
{
    int i;
    for(i = 1; i <= n; i ++)
        printf("%.2lf ", vec[1][i]);
    puts("");
    double ans = 0.0;
    for(i = 1; i <= n; i ++)
        ans += vec[1][i];
    printf("sum = %.2lf\n", ans);
}

void printm()
{
    int i, j;
    for(i = 1; i <= n; i ++)
    {
        for(j = 1; j <= n; j ++)
            printf("%.2lf ", mat[i][j]);
        printf("\n");
    }
}

int main()
{
    int i, j;
    double tmp;
    while(~scanf("%d", &n))
    {
        for(i = 1; i <= n; i ++)
            scanf("%s", s[i]);
        tmp = 0.15 / n;
        for(i = 1; i <= n; i ++)
            for(j = 1; j <= n; j ++)
                mat[i][j] = tmp;
        for(i = 1; i <= n; i ++)
        {
            num[i] = 0;
            for(j = 1; j <= n; j ++)
                if(s[i][j - 1] == '1')
                    num[i] ++;
            if(num[i] == 0) continue;
            tmp = 1.0 / num[i] * 0.85;
            //printf("tmp : %d\t%.2lf\n", i, tmp);
            for(j = 1; j <= n; j ++)
                if(s[i][j - 1] == '1')
                    mat[j][i] += tmp;
        }

        bool first = true;
        for(i = 1; i <= n; i ++)
            vec[0][i] = vec[1][i] = 1.0;
        while(first || check())
        {
            for(i = 1; i <= n; i ++)
                vec[0][i] = vec[1][i];
            for(i = 1; i <= n; i ++)
            {
                vec[1][i] = 0;
                for(j = 1; j <= n; j ++)
                    vec[1][i] += vec[0][j] * mat[i][j];
            }
            first = false;
        }
        for(i = 1; i < n; i ++) printf("%.2lf ", vec[0][i]);
        printf("%.2lf\n", vec[0][n]);
    }
    return 0;
}
