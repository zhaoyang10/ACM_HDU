#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;

struct Rabbit{
    int x,y,t,dir,s;
}R[2];
int n;

int getDir(char c)
{
    if(c == 'N')    return 0;
    if(c == 'W')    return 1;
    if(c == 'S')    return 2;
    if(c == 'E')    return 3;
}

void move()
{
    int i;
    for(i=0;i<2;i++){
        if( R[i].dir == 0 ){
            if( R[i].x > R[i].s ) R[i].x -= R[i].s;
            else{
                R[i].x = R[i].s - R[i].x + 2;
                R[i].dir = 2;
            }
        }else    if( R[i].dir == 1 ){
            if( R[i].y > R[i].s ) R[i].y -= R[i].s;
            else{
                R[i].y = R[i].s - R[i].y + 2;
                R[i].dir = 3;
            }
        }else    if( R[i].dir == 2 ){
            if( R[i].x + R[i].s > n ){
                R[i].x = n - ( ( R[i].s + R[i].x ) - n );
                R[i].dir = 0;
            }else    R[i].x += R[i].s;
        }else    if( R[i].dir == 3 ){
            if( R[i].y + R[i].s > n ){
                R[i].dir = 1;
                R[i].y = n - ( ( R[i].s + R[i].y ) - n );
            }else    R[i].y += R[i].s;
        }
    }
}

void turn(int Time)
{
    int i,j;
    if( R[0].x == R[1].x && R[0].y == R[1].y )        swap ( R[0].dir, R[1].dir );
    else{
        for( i = 0; i < 2; i++ )    if( Time%R[i].t == 0 )    R[i].dir =( R[i].dir + 1 ) % 4;
    }
}

char* revers(int x)
{
    char *st;
    if(x==0)    st = "North";
    if(x==1)    st = "West";
    if(x==2)    st = "South";
    if(x==3)    st = "East";
    return st;
}

int main()
{
    int i,j,k,m;
    char str[10];
    while(~scanf("%d",&n),n){
        R[0].x = R[0].y = 1;
        R[1].x = R[1].y = n;
        for(i=0;i<2;i++){
            scanf("%s%d%d",str,&R[i].s,&R[i].t);
            R[i].dir = getDir(str[0]);
        }
        scanf("%d",&m);
    //    for(j=0;j<2;j++)    printf("%d: %d\t%d\t%s\n",j,R[j].x,R[j].y,revers(R[j].dir));
        for(i=1;i<=m;i++){
            move();
            turn(i);
        //    printf("Time = %d:\n",i);
            //for(j=0;j<2;j++)    printf("%d: %d\t%d\t%s\n",j,R[j].x,R[j].y,revers(R[j].dir));
        }
        for(i=0;i<2;i++)    printf("%d %d\n",R[i].x,R[i].y);
    }
    return 0;
}
