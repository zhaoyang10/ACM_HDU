#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<map>
#include<vector>
#include<cmath>
using namespace std;

const int nMax = 30100;
int last[nMax],f[nMax],node[nMax*10],In[nMax],d[nMax*10];
int dp[20][nMax*10];
int tot,dfn;
map<string,int>mp;
struct Son{
    string name;
    vector<int>s;
    void clear(){    name="";    s.clear();    }
    void print(int n){    for(int i=0;i<n;i++)    cout<<".";    cout<<name<<endl;    }
}S[nMax];

void insert(string str){
    int i,sz,j;
    for(i=0,sz=str.size(); i < sz && str[i]=='.' ; i++);
    last[j=i]=tot;    for(;i<sz;i++)    S[tot].name+=str[i];
    S[last[j-1]].s.push_back(tot);

}

bool cmp(int x,int y){    return S[x].name<S[y].name;    }

void init(int n){
    for(int i=1;i<=n;i++)    S[i].clear();
    memset(last,-1,sizeof(last));
    memset(f,-1,sizeof(f));
    memset(d,-1,sizeof(d));
    tot=2;    dfn=1;    mp.clear();
}

void dfs1(int u,int fa,int dep)
{
    In[u]=dfn;
    f[u]=fa;    d[dfn]=dep;        node[dfn]=u;
    dfn++;
    for(int i=0,sz=S[u].s.size();i<sz;i++){        dfs1(S[u].s[i],u,dep+1);    d[dfn]=dep;        node[dfn++]=u;    }
    d[dfn]=dep;        node[dfn++]=u;
}

void RMQ(int n)
{
    int i,j;
    for(i=1;i<=n;i++)  dp[0][i]=i;
    for(i=1;(1<<i)<=n;i++)
        for(j=1;j+(1<<i)-1<=n;j++)
            if(d[dp[i-1][j]]<d[dp[i-1][j+(1<<(i-1))]])    dp[i][j]=dp[i-1][j];
            else dp[i][j]=dp[i-1][j+(1<<(i-1))];
}

int In_RMQ(int u,int v)
{
    int m;
    int k=( int )( log( (double) (v-u+1.0) )/ log(2.0) );
    if(d[ dp[k][u] ]<d[ dp[k][ v-(1<<k)+1 ] ])    m=dp[k][u];
    else m=dp[k][ v-(1<<k)+1 ];
    return node[m];
}

void dfs2(int u,int dep)
{
    S[u].print(dep);
    for(int i=0,sz=S[u].s.size();i<sz;i++)    dfs2(S[u].s[i],dep+1);
}

int main()
{
    int n,i,j,k;
    string str;
    while(cin>>n){
        if(n==0)    break;
        init(n);    n--;
        cin>>str;
        S[1].name=str;    last[0]=1;
        while(n--){
            cin>>str;
            insert(str);
            tot++;
        }
        for(i=1;i<tot;i++)    sort(S[i].s.begin(),S[i].s.end(),cmp);
        for(i=1;i<tot;i++)    mp[S[i].name]=i;

        dfs1(1,-1,0);        RMQ(dfn-1);
        cin>>n;
        while(n--){
            cin>>str;
            if(str[0]=='L')        dfs2(1,0);
            else if(str[0]=='b'){
                cin>>str;
                if(mp[str]==1){    cout<<"1"<<endl;    continue;}
                cout<<S[f[mp[str]]].s.size()<<endl;
            }else    if(str[0]=='c'){
                cin>>str;    i=In[mp[str]];
                cin>>str;    j=In[mp[str]];
                if(i>j)    swap(i,j);
                int u=In_RMQ(i,j);
                if(In[u]==i)    u=f[u];
                cout<<S[u].name<<endl;
            }
        }
    }
    system("pause");
    return 0;
}
