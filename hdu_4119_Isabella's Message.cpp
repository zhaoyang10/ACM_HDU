#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<string>
#include<map>
#include<vector>
using namespace std;
const int nMax = 100;
map<string,int>mp;
char s[nMax][nMax],st[nMax];
struct Hole{
    int x,y;
    bool operator<(const Hole & h1)const{
        if(x==h1.x)    return y<h1.y;
        return x<h1.x;    
    }
}h[5][nMax*nMax];
int n,th,ts,tw;
string hstr[10],word[nMax*nMax],ans[nMax*nMax];
bool head[5],tail[5];
void get(int m)
{
    int i,j,k;
    hstr[m]="";
    for(k=0;k<th;k++){
        i=h[m][k].x;    j=h[m][k].y;
    //    printf("i=%d\tj=%d\n",i,j);
        hstr[m]+=s[i][j];
    }
    if(hstr[m][0]=='.')    head[m]=true;    else head[m]=false;
    if(hstr[m][hstr[m].size()-1]=='.')    tail[m]=true;    else tail[m]=false;
//    cout<<"hstr["<<m<<"]:"<<hstr[m]<<endl;
}

int cmp(int ttw,int ttans){
    int i,tn=min(ttw,ttans);
    for(i=0;i<tn;i++)
        if(word[i]<ans[i])    return -1;
        else if(word[i]>ans[i])    return 0;
    if(ttw<ttans)    return -1;
    return 0;
}

int main()
{
    int T,i,j,k,ca,sz,nans,tans;
    string str;
    scanf("%d",&T);
    for(ca=1;ca<=T;ca++){
        scanf("%d",&n);    th=0;    ts=1;    tans=0;
        for(i=0;i<n;i++)    scanf("%s",s[i]);
        for(i=0;i<n;i++){
            scanf("%s",st);
            for(j=0;j<n;j++)    
            if(st[j]=='*'){
                h[0][th].x=i;        h[0][th].y=j;
                h[1][th].x=j;        h[1][th].y=n-1-i;
                h[2][th].x=n-i-1;    h[2][th].y=n-j-1;
                h[3][th].x=n-j-1;    h[3][th].y=i;
                th++;
            }
        }
        for(i=0;i<4;i++)    sort(h[i],h[i]+th);
        
        for(i=0;i<4;i++)    get(i);
        
        scanf("%d",&k);    mp.clear();
        while(k--){    cin>>str;    if(mp[str]==0)    mp[str]=ts++;    }
        
//        system("pause");
        for(i=0;i<4;i++){
            tw=0;
            word[0]="";
            sz=hstr[i].size();    j=0;
            while(j<sz){
                while(j<sz && hstr[i][j]=='.')    j++;
                if(j==sz)    break;
                while( j<sz && hstr[i][j]!='.'){    word[tw]+=hstr[i][j];    j++;}
                tw++;    word[tw]="";
            }
            for(j=1;j<4;j++){
                int n1=(i+j-1)%4,n2=(i+j)%4;
                sz=hstr[n2].size();    k=0;
                if( (!tail[n1]) && (!head[n2]) ){    
                    tw--;
                    while(k<sz && hstr[n2][k]!='.'){    word[tw]+=hstr[n2][k];    k++;    }
                    tw++; word[tw]="";
                }
                while(k<sz){
                    while(k<sz && hstr[n2][k]=='.')    k++;
                    if(k==sz)    break;
                    while(k<sz && hstr[n2][k]!='.')    word[tw]+=hstr[n2][k],k++;
                    tw++;    word[tw]="";
                }
            }
        //    printf("tw=%d\n",tw);
            bool flag=true;
            for(j=0;j<tw;j++)    if(mp[word[j]]==0){    flag=false;    break;}
            if(!tw)    flag=false;
            if(flag){
                if(tans==0){
                    for(j=0;j<tw;j++)    ans[j]=word[j];
                    nans=tw;
                    tans=1;
                }else{
                    if(cmp(tw,nans)==-1){
                        for(j=0;j<tw;j++)    ans[j]=word[j];
                        nans=tw;
                    }
                }
            }
        }
        
        printf("Case #%d:",ca);
        if(tans==0)        printf(" FAIL TO DECRYPT\n");
        else{    for(i=0;i<nans;i++)    cout<<" "<<ans[i];        puts("");}
        
    }
//    system("pause");
    return 0;
}
