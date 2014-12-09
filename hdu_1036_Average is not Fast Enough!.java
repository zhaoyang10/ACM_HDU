import java.util.Scanner;
import java.io.PrintStream;
import java.math.*;
public class Main {
    public static void main(String[] args){
        Scanner in = new Scanner ( System.in );
        PrintStream out = new PrintStream ( System.out );
        int n = in.nextInt();
        double len = in.nextDouble();
        while(in.hasNext()){
            int num = in.nextInt();
            double sum=0.0;
            boolean flag = false;
            for(int i=0;i<n;i++){
                String str = in.next();
                int h,m,s;
                h = cov(str.charAt(0));
                m = cov(str.charAt(2))*10 + cov(str.charAt(3));
                s = cov(str.charAt(5))*10 + cov(str.charAt(6));
                if(h==-1) flag=true;
                sum += h*3600 + m*60 + s;
                //out.println("h = "+h+" m = "+m+" s = "+s);
            }
            int ans;
            if(flag)    ans=-1;
            else{ 
                double tans =  Math.round(sum / len);
                //out.println("tans = "+tans);
                ans = (int) tans;
            }
            int bn = get_bn(num);
            for(int i=0;i<bn;i++)    out.print(" ");
            out.print(num+": ");
            if(flag)    out.println("-");
            else{        out.print(ans/60 + ":");if(ans%60<10)    out.print("0"); out.println( ans%60 + " min/km");}
        }
        in.close();
    }
    static int cov( char s){
        if(s == '-')    return -1;
        return s-'0';
    }
    static int get_bn(int num){
        if(num>99)    return 0;
        if(num>9)    return 1;
        return 2;
    }
}
