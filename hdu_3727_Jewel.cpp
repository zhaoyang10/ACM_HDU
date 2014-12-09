#include<iostream>
#include<cassert>
#include<cstring>
#include<algorithm>
#include<cstdio>
using namespace std;
const int N = 100005;
int num[N],now;
pair<int,int> hash[N];
int seg[N<<2],M;
// chairman tree
const int MAXN = 2000000;
int sum[MAXN],pl[MAXN],pr[MAXN],size,root[N];
int make_tree(int l, int r, int val){
    int t = size++;
//    cout<<l<<" "<<r<<" "<<val<<endl;
    if(l == r) { sum[t] = val; return t;}
    int m = l+r>>1;
    pl[t] = make_tree(l,m,val);
    pr[t] = make_tree(m+1,r,val);
    sum[t] = sum[pl[t]] + sum[pr[t]];
    return t;
}
int make_tree(int l,int r, int _pl,int _pr){
    int t = size ++;
    pl[t] = _pl; pr[t] =_pr;
    sum[t] = sum[_pl] + sum[_pr];
    return t;
}
int change(int L, int R,int pos, int at, int v){
    if(L == R)
        return make_tree(L,R,v);
    int m = L+R >> 1;
    if(at <=m ) return make_tree(L,R, change(L,m,pl[pos] , at, v),pr[pos]);
    return make_tree(L, R , pl[pos] , change(m+1,R,pr[pos] ,at, v));
}
int ask(int l,int r, int pos, int L, int R){
    if(l <= L && r >= R)
        return sum[pos];
    int mid = L+R >>1 , val = 0;
    if(l <= mid) val += ask(l,r,pl[pos], L, mid);
    if(r > mid) val += ask(l,r,pr[pos], mid+1,R);
    return val;
}
// init()
int n;
void init(){
    size = 0;
    for(int i=0;i<n;i++)
        hash[i] = make_pair(num[i] , i);
    sort(hash, hash + n);
    root[0] = make_tree(0,n-1,1);
    for(int i=1; i<n; i++){
        root[i] = change(0,n-1,root[i-1],hash[i-1].second , -1);
    }
//    cout<<size<<endl;
    for(int i=30; i>=0; i--) if(n < (1<<i)) M = 1<<i;
    for(int i=0; i<M*2; i++) seg[i] = 0;
}
// segment tree
void ins(int pos){
    for(pos += M; pos; pos >>= 1)
        seg[pos] ++;
}
int find_rank(int pos){
    int ans = 0;
    for(pos += M; pos; pos >>=1)
        if(pos &1) ans += seg[pos ^ 1];
    return ans +1;

}
int find_kth(int k){
    int ans=1;
    while(ans < M){
        int l = ans <<1;
        int r = ans <<1|1;
        assert(seg[ans] >= k);
        if(seg[l] >= k) ans = l;
        else {
            k -= seg[l];
            ans = r;
        }
    }
    return hash[ans-M].first;
}
// main
int find(int val){
    int l = 0, r= n;
    while(l<r){
        int mid = l+r >>1;
        if(val <= hash[mid].first) r = mid;
        else l = mid+1;
    }
    return l;
}
int chk(int pos, int l, int r){
    int val = ask(l,r,root[pos],0,n-1);
    int ans = (r-l+1-val >> 1) + 1;
//    cout<<(ans)<<endl;
    return ans;
}
struct Query{
    char cmd[20];
    int l,r,v;
} query[N*5];
int main(){
    int _test = 0,Q;
    while(~scanf("%d",&Q)){
        n = 0;
        for(int i=0; i<Q;i++){
            scanf("%s",query[i].cmd);
            if(!strcmp(query[i].cmd, "Insert")){
                scanf("%d",&query[i].v);
                num[n++] = query[i].v;
            }
            else {
                char x = query[i].cmd[strlen(query[i].cmd) -1];
                if(x =='1')
                    scanf("%d%d%d",&query[i].l , &query[i].r ,&query[i].v);
                else scanf("%d",&query[i].v);
            }
        }
        init();
        long long Q1 = 0, Q2= 0, Q3 = 0;
        printf("Case %d:\n", ++ _test);
        for(int i=0;i<Q;i++){
            if(!strcmp(query[i].cmd,"Insert")){
                ins(find(query[i].v));
            }
            else {
                char x = query[i].cmd[strlen(query[i].cmd) -1];
                if(x == '1'){
                    int L = query[i].l-1, R = query[i].r-1 , k = query[i].v;
                    int l = 0, r = n;
//                    cout<<"qeury_1 "<<L<<" "<<R<<" "<<k<<endl;
                    while(l < r){
                        int m = l+r >>1;
//                        cout<<l<<" "<<r<<" "<<m<<" "<<hash[m].first<<endl;
                        if(chk(m,L,R) > k) r = m ;
                        else l = m+1;
                    }
                    l--;
                    int v1 = hash[l].first;
                    Q1 += v1;
                    //cout<<v1<<endl;
                }
                else if(x=='2'){
                    int u = find(query[i].v);
                    int v2 = find_rank(u);
                    //cout<<v2<<endl;
                    Q2 += v2;
                }
                else {
                    int v3 = find_kth(query[i].v);
                    Q3 += v3;
                    //cout<<v3<<endl;
                }
            }
        }
        cout<<Q1<<endl<<Q2<<endl<<Q3<<endl;
//        cout<<size<<endl;
    }
}
