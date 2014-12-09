#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
const int nMax = 100010;
struct Person{
    int w,b;

}p[nMax];

bool cmp1(Person p1,Person p2){
    if(p1.b==0 && p2.b!=0)    return true;
    if(p1.b!=0 && p2.b==0)    return false;
    return p1.w<p2.w;
}

bool cmp2(Person p1,Person p2){
    return p1.w<p2.w;
}

int main()
{
    int ca,T,i,j,W,n,m,head,tail,mid,ans1,cost1,ans2,cost2,totb;
    scanf("%d",&T);
    for(ca=1;ca<=T;ca++){
        scanf("%d%d",&n,&W);
        for(i=0;i<n;i++)    scanf("%d%d",&p[i].w,&p[i].b);
        sort(p,p+n,cmp1);

    //    for(i=0;i<n;i++)    printf("p[%d].w=%d\t",i,p[i].w);

        ans1=0,cost1=0,i=0;
        while(i<n && W-cost1>=p[i].w){    cost1+=p[i].w;    ans1++; i++;    if(p[i].b>0)    break;    }
    //    if(i<n && p[i].b>0 && W-cost1>=p[i].w){    cost1+=p[i].w;    ans1=n;    }
        
        ans2=0,cost2=0,i=0;
        head=0,tail=n-1;
        while(head<tail){
            mid=(head+tail)>>1;
            if(p[mid].b==0)    head=mid+1;
            else tail=mid;
        }
    //    printf("head=%d\n",head);
        printf("Case %d: ",ca);
        if(head>=n || W<p[head].w){
            printf("%d %d\n",ans1,cost1);
            continue;
        }
    
        swap(p[head],p[n-1]);
        cost2=p[n-1].w;    //printf("cost2=%d\n",cost2);
        sort(p,p+n-1,cmp2);
        totb=0;
        for(i=0;i<n;i++)    totb+=p[i].b;//    printf("totb=%d\n",totb);
        if(totb>=n-1){
            if(n>ans1 ||( n==ans1 && cost2<cost1) )    printf("%d %d\n",n,cost2);
            else printf("%d %d\n",ans1,cost1);
        }else{
            n-=totb+1;    ans2=totb+1;
            for(i=0;i<n && W-cost2>=p[i].w;i++){
                cost2+=p[i].w;    ans2++;
            }
            if(ans2>ans1 || ans2==ans1 && cost2<cost1)    printf("%d %d\n",ans2,cost2);
            else        printf("%d %d\n",ans1,cost1);
        }
        
    }
//    system("pause");
    return 0;
}
