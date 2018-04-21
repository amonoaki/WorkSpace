public class TestException
{
    public static void main(String[] args) {
        String str1 = "2";
        String str2 = "3";
        int num1 = 0, num2 = 0;
        num1 = Integer.parseInt(str1);
        num2 = Integer.parseInt(str2);
        System.out.println(num2 + " / " + num1 + " = " + num2 / num1);

        int n1 = Integer.parseInt(args[0]);
        int n2 = Integer.parseInt(args[1]);
        System.out.println(n2 + " / " + n1 + " = " + n2 / n1);
    }
}
