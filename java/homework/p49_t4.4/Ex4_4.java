import java.util.Scanner;
import java.lang.System.*;

public class Ex4_4 
{
    public static void main (String [] args) 
    {
        int result = 0, ceiling = 0;
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter your input('q' to quit):");
        while (scanner.hasNextInt()) {
            ceiling = scanner.nextInt();
            System.out.println("The list:");
            for (int i = 0; i <= ceiling; i++) {
                if ( (result = CompleteNumber.comNum(i)) != 0) {
                    System.out.print(result + " ");
                }
            }
            System.out.printf("\nEnter your input('q' to quit):\n");
        }
    }
}

class CompleteNumber
{
    static int comNum(int x) {
        int [] num = new int [50];

        //find and store all the factor
        for (int i = 1, index = 0; i <= (int)Math.sqrt(x); i++) {
            if (x % i == 0) {
                num[index] = i;
                if (i == 1 || x == i * i) {
                    index += 1;
                    continue;
                }
                num[index + 1] = x / i;
                index += 2;
            }
            else {
                continue;
            }
        }

        //calculate the sum and compare with x
        int sum = 0;
        for (int i = 0; i < 50; i++) {
            sum += num[i];
        }

        //judge and return
        if (sum == x && x != 1) {
            return x;
        }
        else {
            return 0;
        }
    }
}
