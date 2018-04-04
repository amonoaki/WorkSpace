import java.lang.Math;
import java.util.Scanner;

public class Ex4_5
{
    public static void main(String [] args)
    {
        int ceiling = 0, sum = 0, item = 0;

        Scanner scanner = new Scanner(System.in);
        System.out.print("Please input the ceiling('q' to quit):");
        while (scanner.hasNextInt()) {
            sum = 0;
            item = 0;
            ceiling = scanner.nextInt();

            for (int i = 0; i < ceiling; i++) {
                item += 8 * Math.pow(10, i);
                sum +=  item;
            }
            System.out.println("The result is: " + sum);
            System.out.print("Please input the ceiling('q' to quit):");
        }
    }
}
