import java.io.*;
import java.util.*;
import java.math.BigDecimal;

public class Main {
    
    public static void main(String[] args)
    {
        BigDecimal a,b;
        Scanner in = new Scanner(System.in);
        while(in.hasNext())
        {
            a = in.nextBigDecimal();
            b = in.nextBigDecimal();
            if(a.compareTo(b) == 0)
            {
                System.out.println("YES");
            }else{
                
                System.out.println("NO");
            }
        }
    }
}
