#include<iostream>
#include<cstdio>
#include<cstring>
#include<cassert>
using namespace std;
const int N = 600005;
template <typename T> inline void chkmin(T &a,T b){if(a>b) a=b;}
template <typename T> inline void chkmax(T &a,T b){if(a<b) a=b;}
bool ch[N<<2];
char parten[10000];
int nxt[N],seg[N<<2][2], stk[N], vis[N], hash[N];
const int inf = ~0u>>2;
struct tree{
    int l,r,v;
    tree(){}
    tree(int _l,int _r,int _v) : l(_l), r(_r), v(_v) {}
} num[N];
int n,len;
int main(){
    int test,M;
    cin >> test;
    for(int _=1;_<=test;_++){
        cin >> n;
        int v,val;
        for(int i=30;i>=0;i--) if((1<<i)>=n) M = 1<<i;
        for(int i=0;i<2*M;i++) seg[i][1] = -1, seg[i][0] = inf;
        for(int i=0;i<n;i++){
            scanf("%d",&v);
            val = v;
            hash[val] = i;
            if(i==0) {
                num[0] = tree(-1,-1,v); 
                v += M-1;
                while(v){seg[v][0] = seg[v][1] = val;v>>=1;}
                continue;
            }
            num[i] = tree(-1,-1,v);
            int mn = -1, mx = inf;
            for(v += M-1; v; v>>=1){
                chkmin(seg[v][0],val);
                chkmax(seg[v][1],val);
                if(v&1) chkmax(mn,seg[v^1][1]);
                else chkmin(mx, seg[v^1][0]);
            }
            //cout<<val<<" "<<mn<<" "<<mx<<endl;
            if(mn == -1 || num[hash[mn]].r !=-1){
                num[hash[mx]].l = i;
            } else num[hash[mn]].r = i;
        }
        len = 0;
        
        for(int i=0;i<n;i++) vis[i] = 0;
        int tp = 0,u;stk[0] =0;
        while(!vis[0]) {
            u = stk[tp];
            ch[len++] = num[u].v & 1;
            v = num[u].l;
            if(v!=-1 && !vis[v]) {stk[++tp] = v; continue;}
            v = num[u].r;
            if(v!=-1 && !vis[v]) {stk[++tp] = v; continue;}
            tp--;
            vis[u] = 1;
        }
//        for(int i=0;i<len;i++) cout<<ch[i]<<" ";cout<<endl;
        
        scanf("%s",parten);
        nxt[0] = -1; int m = strlen(parten);
        int j = -1;
        for(int i=0;i<m;i++) parten[i] -='0';
        for(int i=1;i<m;i++){
            while(j>=0 && parten[i]!=parten[j+1])    
                j=nxt[j];
            if(parten[i]==parten[j+1]) j++; 
            nxt[i] = j;
        }
//        for(int i=0;i<m;i++) cout<<nxt[i]<<" "; cout<<endl;
        int ans = 0; j = -1;
        for(int i=0;i<len;i++){
//            cout<<j<<" ";
            while(j>=0 && parten[j+1]!=ch[i]) j = nxt[j]; 
            if(parten[j+1]==ch[i]) 
                j++;
            if(j == m-1) {
                ans++;
                j = nxt[j];
            }
        }
        printf("Case #%d: %d\n",_,ans);
    }
}
