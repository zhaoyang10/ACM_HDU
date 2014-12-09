import java.io.PrintStream;
import java.util.Scanner;
import java.math.BigDecimal;
public class Main {
    public static void main(String[] args){
        Scanner in = new Scanner ( System.in );
        PrintStream out = new PrintStream( System.out );
        while(in.hasNext()){
            BigDecimal p = in.nextBigDecimal();
            int n= in.nextInt();
            p = p.pow(n).stripTrailingZeros();
            String str = p.toPlainString();
            if(str.startsWith("0."))    str = str.substring(1);
            out.println(str);
        }
        in.close();
    }
}
