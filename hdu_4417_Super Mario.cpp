#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
using namespace std;
const int nMax = 100010;

int tr[20][nMax],sum[20][nMax];
int a[nMax];
void build(int l,int r,int dep)
{
    if(l==r)    return ;
    int i,la,lb,mid=(l+r)>>1,same=mid+1-l;
    la=l;    lb=mid+1;
    for(i=l;i<=r;i++){
        if(tr[dep][i]<a[mid])    same--;
    }
    //if(l==1)    printf("sum[%d][0]=%d\t",dep,sum[dep][0]);
    for(i=l;i<=r;i++){
        sum[dep][i]=sum[dep][i-1];
        if(tr[dep][i]<a[mid]){
            sum[dep][i]++;
            tr[dep+1][la++]=tr[dep][i];
        }
        if(tr[dep][i]>a[mid]){
            tr[dep+1][lb++]=tr[dep][i];
        }
        if(tr[dep][i]==a[mid]){
            if(same>0){
                tr[dep+1][la++]=tr[dep][i];
                sum[dep][i]++;
                same--;
            }else{
                tr[dep+1][lb++]=tr[dep][i];
            }
        }
        //printf("sum[%d][%d]=%d\t",dep,i,sum[dep][i]);
    }
    //puts("");
    build(l,mid,dep+1);
    build(mid+1,r,dep+1);
}

int query(int s,int t,int l,int r,int dep,int k)
{
    //printf("s=%d\tt=%d\tl=%d\tr=%d\tdep=%d\tk=%d\t",s,t,l,r,dep,k);
    if(s==t)    return tr[dep][s];
    int la=sum[dep][s-1]-sum[dep][l-1];
    int lb=sum[dep][t]-sum[dep][s-1];
    int mid=(l+r)>>1;
    //printf("la=%d\tlb=%d\tmid=%d\n",la,lb,mid);
    if(lb>=k)    return query(l+la,l+la+lb-1,l,mid,dep+1,k);
    int ra=s-l-la;
    int rb=t-s+1-lb;
    return query(mid+ra+1,mid+rb+ra,mid+1,r,dep+1,k-lb);
}

int main()
{
    int T,ca,n,m,i,j,k,x,y,h,he,ta,mid;
    scanf("%d",&T);
    for(ca=1;ca<=T;ca++){
        scanf("%d%d",&n,&m);
        for(i=1;i<=n;i++){    scanf("%d",a+i);    tr[0][i]=a[i];}
        sort(a+1,a+n+1);
        build(1,n,0);
        printf("Case %d:\n",ca);
        while(m--){
            scanf("%d%d%d",&x,&y,&h);
            x++;    y++;
            he=1;    ta=y-x+2;
            while(he<ta){
                mid=(he+ta)>>1;
                int tmp=query(x,y,1,n,0,mid);
                //printf("\ntmp=%d\t");
                if(tmp<=h)    he=mid+1;
                else ta=mid;
                //printf("he=%d\tta=%d\n",he,ta);
            }
            printf("%d\n",he-1);
        }
    }
    return 0;
}
