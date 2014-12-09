#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int match[1000];
int mp[400][400];
bool visitx[400], visity[400];
int xx[400], yy[400];
const int inf = 0x7f7f7f7f;
int minx, N;

void init( )
{
  memset(match, -1, sizeof(match));
  memset(mp, 0, sizeof(mp));
  memset(xx, 0, sizeof(xx));
  memset(yy, 0, sizeof(yy));
}

bool Hungary( int x)
{
   visitx[x] = true;
   for( int i = 1; i <= N; i++)
   {   
       if( visity[i] ) continue;
       int temp = xx[x] +  yy[i] - mp[x][i]; 
       if( temp == 0 )
       {
            visity[i] = true;
            if( match[i] ==  -1 || Hungary(match[i]))
             {
                  match[i] = x;
                  return true;
             }
       }
       else
       {
           if( temp < minx )
               minx = temp;
       }
   } 
   return false;
}

void KM( )
{
   for( int i = 1; i <= N; i++)
   {
      for( int j = 1; j <= N; j++)
        {
           if( mp[i][j] > xx[i] )
            xx[i] = mp[i][j];
            yy[j] = 0;
        }
    }
    for( int i = 1; i <= N; i++)
    {
        while( 1 )
        {
          memset(visitx, 0, sizeof(visitx));
          memset(visity, 0, sizeof(visity));
          minx = inf;
          if( Hungary( i ) )
            break;
          else
          {
             for(int j = 1; j <= N; j++)
             {
                if( visitx[j] )
                     xx[j] -= minx;
                if( visity[j] )
                     yy[j] += minx;   
             
             }
          }
        }
    }
    int sum = 0;
    for( int i = 1; i <= N; i++)
        sum += mp[match[i]][i];
    printf("%d\n", sum);

}

int main( )
{

  while( scanf("%d",&N) != EOF )
  { 
     init( );
     for( int i = 1; i <= N; i++)
        for( int j = 1; j <= N; j++)
        scanf("%d",&mp[i][j]);
     KM( );
  }
}
