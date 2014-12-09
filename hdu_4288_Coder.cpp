#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<memory.h>
using namespace std;
const int maxn=100002;
#define lson rt<<1,l,mid
#define rson rt<<1|1,mid+1,r
__int64 sum[maxn<<2][6];
char op[maxn][20];
int num[maxn<<2],n,a[maxn],idx[maxn];//表示左移距离
void pushUp(int rt)
{
    num[rt]=num[rt<<1]+num[rt<<1|1];
    int id=num[rt<<1];
    for(int i=0; i<5; i++)
    {
        sum[rt][i]=sum[rt<<1][i];
    }
    for(int i=0; i<5; i++)
    {
        sum[rt][(i+id)%5]+=sum[rt<<1|1][i];
    }
}
void build(int rt,int l,int r)
{

     num[rt]=0;
    for(int i=0; i<5; i++) sum[rt][i]=0;
    if(l==r) return;
    int mid=(l+r)>>1;
    build(lson);
    build(rson);
}
void updata(int rt,int l,int r,int pos,int op)//op=1 表示 add; op=0 表示 del;
{
    if(l==r)
    {
        num[rt]=op;
        sum[rt][1]=op*idx[l];
        return ;
    }
    int mid=(l+r)>>1;
    if(pos<=mid)
        updata(lson,pos,op);
    else
        updata(rson,pos,op);
    pushUp(rt);
}
int main()
{
    while(scanf("%d",&n)!=EOF)
    {
        int i,j,k=0;
        for(i=0; i<n; i++)
        {
            scanf("%s",&op[i]);
            if(op[i][0]!='s')
            {
                scanf("%d",&a[i]);
                if(op[i][0]=='a')
                {
                    idx[++k]=a[i];
                }
            }
        }
        sort(idx+1,idx+k+1);//因为没有排序ＷＡ了无数次！！
        k=unique(idx+1,idx+k+1)-(idx+1);
        //printf("tot = %d\n",k);
        //for(i=1; i<=k; i++)    printf("%d ",idx[i]);    puts("");
        build(1,1,k);
        for(i=0; i<n; i++)
        {
            int pos=upper_bound(idx+1,idx+k+1,a[i])-(idx+1);
            //printf("[%d]: %d pos = %d\n",i,a[i],pos);
            if(op[i][0]=='a')
            {
                updata(1,1,k,pos,1);
            }
            else if(op[i][0]=='d')
            {
                updata(1,1,k,pos,0);
            }
            else printf("%I64d\n",sum[1][3]);
        }
    }
    return 0;
}
