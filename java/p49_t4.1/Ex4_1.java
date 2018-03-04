import java.util.*;

public class Ex4_1 
{
    public static void main (String [] args)
    {
        int sum = 0, n = 0;
        Scanner scanner = new Scanner(System.in);
        System.out.println("Please enter your input(enter 'q' to quit):");
        while (scanner.hasNextInt()) {
            sum = 0;
            n =  scanner.nextInt();
            for (int i = 1; i <= n; i++) {
                sum +=  Factorial.fac(i);
            }
            System.out.printf("Result = %d\n", sum);
            System.out.println("Please enter your input(enter 'q' to quit):");
        }
    }
}

class Factorial 
{
    static int fac (int ceiling) {
        int product = 1;
        for (int i = ceiling; i > 1; i--) {
            product *= i;
        }
        return product;
    }
}
