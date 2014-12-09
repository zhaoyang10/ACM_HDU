import java.util.Scanner;
import java.math.BigInteger;
import java.io.PrintStream;
public class Main{
    public static void main(String[] args){
        Scanner in = new Scanner(System.in);
        PrintStream out = new PrintStream(System.out);
        int T,ca;
        BigInteger a,b;
        T = in.nextInt();
        for(ca=1;ca<=T;ca++){
            a=in.nextBigInteger();
            b=in.nextBigInteger();
            if(ca!=1)    out.println();
            out.println("Case "+ca+":");
            out.println(a+" + "+b+" = "+a.add(b));
        }
        in.close();
    }
}
