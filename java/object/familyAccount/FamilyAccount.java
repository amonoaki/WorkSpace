package familyAccount;
import java.util.Scanner;

public class FamilyAccount
{
    public static void main(String[] args) throws java.io.IOException{
        int option;
        double money;
        String document;
        boolean loopFlag = true;

        Scanner scanner = new Scanner(System.in);
        Account account = new Account(10000);

        Menu.menu();
        while(loopFlag == true) {
            System.out.print("请选择(1-4)：");
            option = scanner.nextInt();
            switch(option) {
                case 1: System.out.println(account.getDetails()); break;
                case 2: 
                        System.out.print("本次收入金额：");
                        money = scanner.nextDouble();
                        System.out.print("本次收入说明：");
                        document = scanner.next();
                        account.incomeProcess(money, document); break;
                case 3: 
                        System.out.print("本次支出金额：");
                        money = scanner.nextDouble();
                        System.out.print("本次支出说明：");
                        document = scanner.next();
                        account.spendingProcess(money, document); break;
                case 4: 
                        System.out.print("确认是否退出(Y/N)：");
                        if (System.in.read() == (int)'Y') {
                            loopFlag = false;
                        }
                        break;
                default: System.out.println("选项错误，请重试。"); break;
            }
        }
        System.out.println("已退出。");
    }
}
