#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
using namespace std;
#define MAXN    1010
char s[MAXN];
int a[MAXN][MAXN],dp[MAXN][MAXN],up[MAXN][MAXN],down[MAXN][MAXN];
int n,m,rec,squ;
int sta[MAXN];

void init_dp()
{
    int i,j;
    memset(dp,0,sizeof(dp));
    for(i=1;i<=n;i++)
        for(j=m;j>=1;j--)
            if(a[i][j])        dp[i][j]=dp[i][j+1]+1;
            else             dp[i][j]=0;
}

void reverse1()
{
    int i,j;
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            a[i][j]=1-a[i][j];
}
void reverse2()
{
    int i,j;
    for(i=1;i<=n;i++){
        if(i&1){
            for(j=2;j<=m;j+=2)
                a[i][j]=1-a[i][j];
        }else{
            for(j=1;j<=m;j+=2)
                a[i][j]=1-a[i][j];
        }
    }
}

void get_up()
{
    int top,i,j;
    for(i=1;i<=m;i++){
        sta[top=0]=1;
        if(a[1][i])    up[1][i]=1;
        else        up[1][i]=0;
        for(j=2;j<=n;j++){
        //    printf("i=%d\tj=%d\n",j,i);
    //        for(int k=0;k<=top;k++)    printf("sta[%d]=%d\n",k,sta[k]);
            if(a[j][i]==0)    {    sta[top=0]=j;    up[j][i]=0;    continue;    }
            while(    top>=0    &&    dp[sta[top]][i]>=dp[j][i]    )    top--;
            if(top==-1){    up[j][i]=j;        sta[++top]=j;    }
            else{    up[j][i]=j-sta[top];    sta[++top]=j;    }
        }
    }
}

void get_down()
{
    int top,i,j;
    for(i=1;i<=m;i++){
        sta[top=0]=n;    
        if(a[n][i])        down[n][i]=1;
        else            down[n][i]=0;
        for(j=n-1;j>=1;j--){
            if(a[j][i]==0){        sta[top=0]=j;    down[j][i]=0;    continue;}
            while(    top>=0    &&    dp[sta[top]][i]>=dp[j][i]    )    top--;
            if(top==-1){    down[j][i]=n-j+1;    sta[++top]=j;    }
            else{    down[j][i]=sta[top]-j;        sta[++top]=j;    }    
        }
    }
}


void get_rec()
{
    get_up();
    get_down();
    int i,j;
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            rec=max(rec,2*(up[i][j]+down[i][j]-1+dp[i][j]));
}

void get_squ()
{
    get_up();
    get_down();
    int i,j;
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            squ=max(squ,4*min ( up[i][j]+down[i][j]-1 , dp[i][j] ) );
}

void check()
{
    int i,j;
    printf("\n\n");
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++)
            printf("%d",a[i][j]);
        printf("\n");
    }
    printf("dp:\n");
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++)    printf("%d ",dp[i][j]);
        printf("\n");
    }
    printf("up:\n");
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++)    printf("%d ",up[i][j]);
        printf("\n");
    }
    printf("down:\n");
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++)    printf("%d ",down[i][j]);
        printf("\n");
    }
    printf("\n");
}

int main()
{
    int T,i,j,k,ca=1;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        rec=0;    squ=0;
        for(i=1;i<=n;i++){
            scanf("%s",s);
            for(j=1;j<=m;j++)
                if(s[j-1]=='B')        a[i][j]=1;
                else a[i][j]=0;
        }
        init_dp();    get_rec();//        printf("rec=%d\n",rec);        check();
        reverse1();
        init_dp();    get_rec();//        printf("rec=%d\n",rec);        check();
        reverse2();
        init_dp();    get_squ();//        printf("squ=%d\n",squ);        check();9
        reverse1();
        init_dp();    get_squ();//        printf("squ=%d\n",squ);        check();
        printf("Case #%d: ",ca++);
        printf("%d\n",max(squ,rec));
//        printf("%d\n",rec);
    }
//    system("pause");
    return 0;
}
