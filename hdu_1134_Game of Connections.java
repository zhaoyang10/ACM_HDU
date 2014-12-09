import java.io.*;
import java.math.BigInteger;
import java.util.*;


public class Main {

    public static void main(String[] args)
    {
        final int N = 100;
        Scanner in = new Scanner(System.in);
        BigInteger a[] = new BigInteger[N+1];
        a[1] = BigInteger.ONE;
        for(int i=2; i<=N; i++)        a[i] = a[i-1].multiply(BigInteger.valueOf(4*i-2)).divide(BigInteger.valueOf(i+1));
        while(in.hasNext())
        {
            int n = in.nextInt();
            if(n == -1)    break;
            System.out.println(a[n]);
        }
                in.close();
    }
    
}
