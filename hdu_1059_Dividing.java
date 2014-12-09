import java.io.PrintStream;
import java.util.Scanner;
public class Main {
    static int a[] = new int [7];
    static int tot;
    static int d[] = new int [20010];
    static int p[] = new int [22];
    public static void main(String [] args){
        Scanner in = new Scanner( System.in );
        PrintStream out = new PrintStream( System.out );
        int i,j,sum,ca=1;
        boolean dp[] = new boolean [120010];
        p[0]=1;    for(i=1;i<=20;i++)    p[i]=p[i-1]*2;
        while(in.hasNext()){
            sum=0;
            if(ca!=1)    out.println();
            for(i=1;i<=6;i++){    a[i] = in.nextInt();    sum+=a[i]*i;}
            if(sum==0)    break;
            out.println("Collection #"+ca+":");
            ca++;
            if((sum&1)==1)    out.println("Can't be divided.");
            else{
                sum/=2;
                for(i=1;i<=sum;i++)    dp[i]=false;    dp[0]=true;
                init();
                boolean flag=false;
                for(i=0;i<tot;i++){
                    for(j=sum-d[i];j>=0;j--)
                        if(dp[j]){    
                            dp[j+d[i]]=true;
                            if(j+d[i]==sum)    {flag=true;break;}
                        }
                    if(flag)    break;
                }
                if(dp[sum])    flag=true;    
                if(flag)    out.println("Can be divided.");
                else out.println("Can't be divided.");
            }

        }
        in.close();
    }
    public static void init(){
        tot=0;
        int i,j,k,num;
        for(i=1;i<=6;i++){
            while(a[i]>0){
                j=half(a[i]);    j--;
                if(j<=0)     break;
                for(k=j;k>=0;k--){
                    num = p[k];
                    a[i]-=num;
                    d[tot++]=num*i;
                }
            }
            while(a[i]>0)    {    d[tot++]=i;    a[i]--;    }
        }
    }
    public static int half(int x){
        int mid,he=0,ta=20;
        while(he<ta){
            mid=(he+ta)>>1;
            if(p[mid]>x)    ta = mid;
            else he = mid+1;
        }
        return he-1;
    }
}
