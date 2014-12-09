import java.io.PrintStream;
import java.util.Scanner;
import java.math.BigDecimal;
public class Main {
    static Scanner in = new Scanner(System.in);
    static PrintStream out = new PrintStream(System.out);
    public static void main(String[] args){
        while(in.hasNext()){
            BigDecimal a = in.nextBigDecimal();
            BigDecimal b = in.nextBigDecimal();
            a = a.add(b);
            a = a.stripTrailingZeros();
            String ans = a.toPlainString();
            if(ans.startsWith("0."))    ans=ans.substring(1);
            out.println(ans);
        }
        in.close();
    }
}
