import java.io.PrintStream;
import java.util.Scanner;
import java.math.BigInteger;
public class Main {
    public static void main(String[] args){
        Scanner in = new Scanner( System.in );
        PrintStream out = new PrintStream( System.out );
        while(in.hasNext()){
            int n = in.nextInt();
            BigInteger ans = BigInteger.ONE;
            BigInteger a=BigInteger.ONE;        
            for(int i=1;i<=n;i++){
                ans=ans.multiply(a);
                a=a.add(BigInteger.ONE);
            }
            out.println(ans);
        }
        in.close();
    }
}
