import java.util.Scanner;

public class Ex4_3 
{
    public static void main (String [] args)
    {
        Scanner scanner = new Scanner(System.in);
        float sum = 0F;
        int ceiling = 0;
        System.out.println("Please enter a interger('q' to quit):");
        while (scanner.hasNextInt()) {
            sum = 0F;
            ceiling = scanner.nextInt();
            for (int i = 1; i <= ceiling; i++) {
                sum += (float)1 / (float)Factorial.fac(i);
                /*
                    class Factorial 
                    {
                        static int fac(int ceiling) {}
                    }
                    //calculate the factorial of an interger.
                */
            }
            System.out.printf("Result = %.3f\n", sum);
            System.out.println("Please enter a interger('q' to quit):");
        }
    }
}
