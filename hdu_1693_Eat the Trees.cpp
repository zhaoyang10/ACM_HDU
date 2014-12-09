#include<cstdio>
#include<cstring>
using namespace std;
__int64 f[2][1<<12];
int main()
{
    int T,c=0,p,q,i,j,k,n,m,ok;
    bool x,y,g,h;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&m,&n);
        memset(f,0,sizeof(f));
        f[0][0]=1;
        for(g=1,h=0,i=0;i<m;i++){
            for(j=1;g=!g,h=!h,j<=n;j++)
                for(scanf("%d",&ok),k=0;k<1<<n<<1;k++){
                    p=1<<j;    q=p>>1;    x=k&p;    y=k&q;
                    if(ok){
                        f[h][k]=f[g][k^p^q];
                        if(x^y)    f[h][k]+=f[g][k];
                    }else    f[h][k]=x|y?0:f[g][k];
                }
            memset(f[h],0,sizeof(f[h]));
            for(j=0;j<1<<n;j++)    f[h][j<<1]=f[g][j];
        }
        printf("Case %d: There are %I64d ways to eat the trees.\n",++c,f[h][0]);
    }
//    system("pause");
    return 0;
}
