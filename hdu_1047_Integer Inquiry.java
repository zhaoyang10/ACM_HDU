import java.util.Scanner;
import java.io.PrintStream;
import java.math.BigInteger;
public class Main {
    public static void main(String[] args){
        Scanner in = new Scanner(    System.in    );
        PrintStream    out = new PrintStream (    System.out    );
        int T,ca;
        BigInteger a,s;
        T = in.nextInt();
        for(ca=0;ca<T;ca++){
            if(ca!=0)    out.println();
            s=BigInteger.ZERO;
            while(true){
                a=in.nextBigInteger();
                if(a.equals(BigInteger.ZERO))    break;        
                s=s.add(a);
            }
            out.println(s);
        }
        in.close();
    }
}
