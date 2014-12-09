import java.io.PrintStream;
import java.util.Scanner;
import java.math.BigInteger;
public class Main {
    public    static final int    nMax = 481;
    static BigInteger Fib[] = new BigInteger[nMax];
    public static void main(String[] args){
        Scanner in = new Scanner ( System.in );
        PrintStream out = new PrintStream( System.out );
        BigInteger a,b,one=BigInteger.ONE,zero=BigInteger.ZERO;
        
        Fib[1]=BigInteger.ONE;
        Fib[2]=Fib[1].add(Fib[1]);
        int i;
        for(i=3;i<nMax;i++)    Fib[i]=Fib[i-1].add(Fib[i-2]);
        while(in.hasNext()){
            a=in.nextBigInteger();
            b=in.nextBigInteger();
            if(a.equals(zero) && b.equals(zero))    break;
            int n1=get_num(a.subtract(one));
            int n2=get_num(b);
            out.println(n2-n1);
        }
        in.close();
    }
    public static int get_num(BigInteger x){
        int mid,he=1,ta=nMax;
        while(he<ta){
            mid=(he+ta)>>1;
            if(Fib[mid].compareTo(x)==1)    ta=mid;
            else he=mid+1;
        }
        return he-1;
    }
    
}
