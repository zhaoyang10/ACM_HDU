import java.util.*;
import java.math.BigInteger;
import java.io.*;
public class Main {
    public static void main(String[] args)
    {
        
        //System.out.println("fuck!");
        BigInteger a[] = new BigInteger[101];
        a[1] = BigInteger.ONE;
        for(int i=2; i<=100; i++)
        {
            a[i] = a[i-1].multiply(BigInteger.valueOf(4*i-2)).
                    divide(BigInteger.valueOf(i+1));
        }
        int x;
        Scanner in = new Scanner(System.in);
        while(in.hasNext())
        {
            x = in.nextInt();
            System.out.println(a[x]);
        }
    }
}
