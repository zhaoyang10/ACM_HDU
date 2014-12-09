#include <cstdio>  
#include <iostream>  
using namespace std;  
  
const int hash_size=300007;  
const __int64 mod=1000000007;  
  
int n, m;  
int Pow[40];  
int Case;  
int th[300];  
  
struct node {  
    __int64 sum;  
    int size;  
    int msk[hash_size];  
    __int64 dp[hash_size];  
    int next[hash_size];  
    int head[hash_size];  
    void clear() {  
        sum=0;  
        size=0;  
        memset(head, -1, sizeof(head));  
    }  
    void push(int _msk, __int64 val) {  
        int x=_msk%hash_size;  
        for(int it=head[x];it!=-1;it=next[it]) {  
            if(msk[it]==_msk) {  
                dp[it]=(dp[it]+val)%mod;  
                return ;  
            }  
        }  
        msk[size]=_msk;  
        dp[size]=val;  
        next[size]=head[x];      
        head[x]=size++;  
    }  
}hh[2];  
  
void solve() {  
    Case++;  
    scanf("%d %d", &n, &m);  
    node *src=hh, *des=hh+1;  
    src->clear ();  
    int i, j, k, tk, temp, p, q, t1, t2;  
    __int64 val;  
    src->push (0, 1);  
    char str[5];  
    for(i=0;i<n;i++) {  
        for(j=0;j<=m;j++) {  
            if(j!=m)  
                scanf("%s", str);  
            des->clear ();  
            for(p=0;p<src->size ;p++) {  
                k=src->msk [p];  
                val=src->dp [p];  
                if(j==m) {  
                    if(k/Pow[m+1])  
                        continue;  
                    temp=k%Pow[m];  
                    des->sum =(des->sum +val)%mod;  
                    des->push ((temp<<2), val);  
                    continue;  
                }  
                t1=(k/Pow[j])%4, t2=(k/Pow[j+1])%4;  
                for(q=0;q<4;q++) {  
                    if( ( ( (t1==0) || (t1==th[str[q]]) ) && ( (t2==0) || (t2==th[str[(q+1)&3]]) ) ) ) {  
                        temp=k-Pow[j]*t1-Pow[j+1]*t2;  
                        tk=temp+Pow[j]*th[str[(q+3)&3]]+Pow[j+1]*th[str[(q+2)&3]];  
                        des->push (tk, val);  
                    }  
                }  
            }  
            swap(src, des);  
        }  
    }  
    printf("Case %d: %I64d\n", Case, src->sum );  
}  
  
int main () {  
    int T;  
    th['R']=1, th['F']=2, th['C']=3;  
    Pow[0]=1;  
    for(int i=1;i<32;i++)  
        Pow[i]=(Pow[i-1]<<2);  
    scanf("%d", &T);  
    while(T--)  
        solve();  
    return 0;  
}  
