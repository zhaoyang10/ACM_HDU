import java.io.PrintStream;
import java.util.Scanner;
import java.math.BigInteger;
public class Main {
    public static int nMax = 1001;
    public static void main(String[] args){
        Scanner in = new Scanner ( System.in );
        PrintStream out = new PrintStream( System.out );
        BigInteger one = BigInteger.ONE;
        BigInteger fib[] = new BigInteger[nMax];
        fib[1]=one;    fib[2]=one;
        for(int i=3;i<nMax;i++)    fib[i]=fib[i-1].add(fib[i-2]);
        int ca,T,n;
        T=in.nextInt();
        for(ca=0;ca<T;ca++){
            n=in.nextInt();
            out.println(fib[n]);
        }
        in.close();
    }
}
