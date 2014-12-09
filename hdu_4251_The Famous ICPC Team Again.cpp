#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
const int nMax = 100010;
int tr[20][nMax],sum[20][nMax];
int a[nMax];

void build(int l,int r,int dep)
{
    if(l==r)    return ;
    int mid=(l+r)>>1,i,la=l,lb=mid+1,same=mid-l+1;
    for(i=l;i<=r;i++)    if(tr[dep][i]<a[mid])    same--;
    for(i=l;i<=r;i++){
        sum[dep][i]=sum[dep][i-1];
        if(tr[dep][i]<a[mid]){
            sum[dep][i]++;
            tr[dep+1][la++]=tr[dep][i];
        }else if(tr[dep][i]>a[mid]){
            tr[dep+1][lb++]=tr[dep][i];
        }else if(same>0){
            same--;
            tr[dep+1][la++]=tr[dep][i];
            sum[dep][i]++;
        }else tr[dep+1][lb++]=tr[dep][i];
    }
    build(l,mid,dep+1);
    build(mid+1,r,dep+1);
}

int query(int s,int t,int l,int r,int dep,int k)
{
    if(s==t)    return tr[dep][s];
    int mid=(l+r)>>1,la,lb;
    la=sum[dep][s-1]-sum[dep][l-1];
    lb=sum[dep][t]-sum[dep][s-1];
    if(lb>=k)    return query(l+la,l+la+lb-1,l,mid,dep+1,k);
    int ra,rb;
    ra=s-l-la;
    rb=t-s+1-lb;
    return query(mid+ra+1,mid+ra+rb,mid+1,r,dep+1,k-lb);
}

int main()
{
    int n,ca=1,i,j,x,y,k,m;
    while(~scanf("%d",&n)){
        for(i=1;i<=n;i++){    scanf("%d",a+i);    tr[0][i]=a[i];    }
        sort(a+1,a+n+1);
        build(1,n,0);
        printf("Case %d:\n",ca++);
        scanf("%d",&m);
        while(m--){
            scanf("%d%d",&x,&y);
            k=((y+x+1)>>1)-x+1;
            printf("%d\n",query(x,y,1,n,0,k));
        }
    }
    return 0;
}
