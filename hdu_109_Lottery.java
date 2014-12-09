import java.io.PrintStream;
import java.util.Scanner;
import java.math.BigInteger;
public class Main {
    static     BigInteger one = BigInteger.ONE;
    static    BigInteger zero = BigInteger.ZERO;
    static    BigInteger ans[][] = new BigInteger [23][2];
    static    PrintStream out = new PrintStream ( System.out );
    public static void main(String[] args){
        init();
        Scanner in = new Scanner ( System.in );
        
        while(in.hasNext()){
            int n = in.nextInt();
            output(n);
        }
        in.close();
    }
    
    static void init()
    {
        
        BigInteger jc[] = new BigInteger [23];
        
        BigInteger tmp = one.add(one);
        BigInteger sum;
        jc[1] = one;
        int i,k;
        for(i=2;i<=22;i++){
            jc[i] = jc[i-1].multiply(tmp);
            tmp = tmp.add(one);
        }
        //tmp = one.add(one);
    /*    p[1] = one;
        for(i=2;i<=22;i++){
            p[i] = one;
            for(k=1;k<=i;k++)    p[i] = p[i].multiply(tmp);
            tmp = tmp.add(one);
        }*/
        ans[1][0] = one;    ans[1][1] = one;    
        ans[2][0] = one.add(one.add(one));    ans[2][1] = one;
        for(k=3;k<=22;k++){
            ans[k][1] =    jc[k];
            sum = zero;    tmp = one;
            for(i=1;i<=k;i++){
                sum = sum.add( jc[k].divide(tmp) );
                tmp = tmp.add(one);
            }
            ans[k][0]=sum.multiply(tmp.subtract(one));
            BigInteger Gcd = ans[k][0].gcd(ans[k][1]);
            ans[k][0] = ans[k][0].divide(Gcd);
            ans[k][1] = ans[k][1].divide(Gcd);
        }
        
    }
    
    static void output(int n){
        if( ans[n][1].equals(one) )        out.println(ans[n][0]);
        else{
            //out.println(ans[n][0]+"   "+ans[n][1]);
            
            BigInteger m = ans[n][0].divide(ans[n][1]);
            BigInteger mod = ans[n][0].mod(ans[n][1]);
            String str2 = m.toString(),str0 = mod.toString(),str1 = ans[n][1].toString();
            int i,len = str2.length();
            for(i=0;i <= len; i++)    out.print(" ");        out.println(str0);
            out.print(str2+" ");
            int len1= Math.max(str0.length(),str1.length());
            for(i=0;i<len1;i++)    out.print("-");    out.println();
            for(i=0;i <= len;i++)    out.print(" ");        out.println(str1);
        }
    }
}
