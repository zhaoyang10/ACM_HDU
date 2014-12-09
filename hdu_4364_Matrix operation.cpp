#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int nMax = 6;
const int MAX = 0xff;
const int XOR = 0x1b;
int ini[nMax][nMax],sta[nMax][nMax],ans[nMax][nMax];

void init()
{
    sta[0][0]=2;    sta[0][1]=3;    sta[0][2]=1;    sta[0][3]=1;
    sta[1][0]=1;    sta[1][1]=2;    sta[1][2]=3;    sta[1][3]=1;
    sta[2][0]=1;    sta[2][1]=1;    sta[2][2]=2;    sta[2][3]=3;
    sta[3][0]=3;    sta[3][1]=1;    sta[3][2]=1;    sta[3][3]=2;
}

int con_16(char s)
{
    if(s>='0' && s<='9')    return s-'0';
    return s-'A'+10;
}

inline int check(int x){    
//    printf("\nx=%d\tx^%d=%d\n",x,XOR,x^XOR);
    if(x> MAX )    return (x^XOR)%(MAX+1);        
    return x;    
}

int convert(char* s)
{
    int res=0;
    if(s[0]>='0' && s[0]<='9')    res+=16*(s[0]-'0');    else res+=16*(s[0]-'A'+10);
    if(s[1]>='0' && s[1]<='9')    res+=(s[1]-'0');    else res+=(s[1]-'A'+10);
    return res;
}


inline int Op(int op,int x)
{
    if(op==1)    return x;
    if(op==2)    return check(x<<1);
    return check(x<<1) ^ x ;
}

int get_ans(int x,int y)
{
    int k,res=0;
    for(k=0;k<4;k++){
//        printf("%d %d:%d\n",sta[x][k],ini[x][y],Op(sta[x][k],ini[k][y]));
        res=( res ^ Op(sta[x][k],ini[k][y]) )%(MAX+1);
    }
//    printf("ans[%d][%d]=%d\n",x,y,res);
    return res;
}

void output(int x)
{
    int i,j;
    i=x/16;    j=x%16;
    if(i>9)    printf("%c",'A'+i-10);    else printf("%d",i);
    if(j>9)    printf("%c",'A'+j-10);    else printf("%d",j);
}

int main()
{
    init();
    int i,j,k,T;
    char s[10];
    bool first=true;
    scanf("%d",&T);
    while(T--){
        if(first)    first=false;    else puts("");

        for(i=0;i<4;i++)
            for(j=0;j<4;j++){
                scanf("%s",s);
                ini[i][j]=convert(s);
            }
/*
        puts("input:");
        for(i=0;i<4;i++){
            for(j=0;j<4;j++)
                printf(" %d",ini[i][j]);
            puts("");
        }
    */    
        
        for(i=0;i<4;i++)
            for(j=0;j<4;j++)
                ans[i][j]=get_ans(i,j);
                
/*        
        for(i=0,puts("output:");i<4;i++){
            for(j=0;j<4;j++)
                printf(" %d",ans[i][j]);
            puts("");
        }
*/
        for(i=0;i<4;i++)
            for(j=0;j<4;j++){
                output(ans[i][j]);
                if(j==3)    puts("");
                else        printf(" ");
            }
    }
//    system("pause");
    return 0;
} 
