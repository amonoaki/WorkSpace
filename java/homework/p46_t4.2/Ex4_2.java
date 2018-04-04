import java.util.*;
import java.lang.System.*;

public class Ex4_2 
{
    public static void main (String [] args)
    {
        int ceiling = 0;
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter your input('q' to quit):");
        while (scanner.hasNextInt()) {
            ceiling = scanner.nextInt();
            if (ceiling < 2) {
                System.out.println("No prime is avariable.");
            }
            else {
                System.out.printf("Prime list(from 2 to %d):\n", ceiling);
            }
            if (ceiling == 2) {
                System.out.print("2 ");
            }
            else if (ceiling > 2) {
                System.out.print("2 3 ");
            }
            for (int i = 4, n = 0; i <= ceiling; i++) {
                if ( (n = Prime.prime(i)) == 0 ) {
                    continue;
                }
                System.out.print(n + " ");
            }
            System.out.println();
            System.out.println("Enter your input('q' to quit):");
        }
    }
}

class Prime
{
    static int prime(int ceiling) {
        int i = 0;
        for (i = 2; i <= (int)Math.sqrt(ceiling); i++) {
            if (ceiling % i == 0) {
                return 0;
            }
        }
        return ceiling;
    }
}
