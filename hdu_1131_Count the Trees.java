import java.util.*;
import java.math.BigInteger;
import java.io.*;
public class Main {
    public static void main(String[] args)
    {
        
        //System.out.println("fuck!");
        
        final int N = 101;
        
        BigInteger a[] = new BigInteger[N];
        BigInteger b[] = new BigInteger[N];
        
        a[1] = BigInteger.ONE;
        b[1] = BigInteger.ONE;
        
        for(int i=2; i<=100; i++)
        {
            a[i] = a[i-1].multiply(BigInteger.valueOf(4*i-2)).
                    divide(BigInteger.valueOf(i+1));
            b[i] = b[i-1].multiply(BigInteger.valueOf(i));
        }
        int x;
        Scanner in = new Scanner(System.in);
        while(in.hasNext())
        {
            x = in.nextInt();
            if(x == 0)    break;
            System.out.println(a[x].multiply(b[x]));
        }
    }
}
