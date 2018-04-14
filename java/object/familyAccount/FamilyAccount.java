package familyAccount;
import java.util.Scanner;

public class FamilyAccount
{
    Scanner scanner = new Scanner(System.in);
    Account account = new Account(10000);

    public static void main(String[] args) {
        FamilyAccount unit = new FamilyAccount();
        unit.mainMenu();
    }

    public void mainMenu() {
        int option;
        boolean loopFlag = true;

        while(loopFlag == true) {
            menu();
            if (scanner.hasNextInt()) {
                option = scanner.nextInt();
            } else {
                scanner.next();
                option = -1;
            }
            switch(option) {
                case 1: System.out.println(account.getDetails()); break;
                case 2: income(); break;
                case 3: spending(); break;
                case 4: loopFlag = quit(); break;
                default: System.out.println("需要一个选项(1-4)，请重试。"); break;
            }
        }
        System.out.println("已退出。");
    }

    public void menu() {
        System.out.println("-----------------家庭收支记账软件-----------------");
        System.out.println();
        System.out.println("                   1 收支明细");
        System.out.println("                   2 登记收入");
        System.out.println("                   3 登记支出");
        System.out.println("                   4 退    出");
        System.out.println();
        System.out.print("        请选择(1-4)：");
    }

    public void income() {
        double money = 0;
        String document;

        System.out.print("本次收入金额：");
        money = readDouble(false);  //布尔值为此方法内部一个功能的开关
        System.out.print("本次收入说明：");
        document = readString(); 
        account.incomeProcess(money, document);
    }

    public void spending() {
        double money;
        String document;

        System.out.print("本次支出金额：");
        money = readDouble(true);
        System.out.print("本次支出说明：");
        document = readString();
        account.spendingProcess(money, document);
    }

    public boolean quit() {
        String temp;

        System.out.print("确认是否退出(Y/N)：");
        temp = scanner.next();
        if (temp.equals("Y") || temp.equals("y")) {
            return false;
        } else {
            return true;
        }
    }

    public double readDouble(boolean optionFlag) {
        double money = 0;
        while(scanner.hasNext()) {
            try {
                money = Double.parseDouble( scanner.next() );
                if (money < 0) {
                    System.out.print("金额不能为负，请重试：");
                }
                else if (optionFlag && money > account.getBalance()) {
                //如果optionFlag为真，则执行此代码块，判断输入的金额是否大于余额
                    System.out.print("金额不能为超出账户余额，请重试：");
                }
                else {
                    break;
                }
            } catch(NumberFormatException e) {
                System.out.print("金额应为数字，请重试:");
            }
        }
        return money;
    }

    public String readString() {
        String document = "";
        while(scanner.hasNext()) {
            document = scanner.next();
            if (document.length() < 1 || document.length() > 8) {
                System.out.print("输入字段过长，请重新输入：");
            } else {
                break;
            }
        }
        return document;
    }
}
