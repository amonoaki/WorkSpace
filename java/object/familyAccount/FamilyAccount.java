package FamilyAccount;
import java.util.Scanner;
import java.io.*;

public class FamilyAccount
{
    Scanner scanner = new Scanner(System.in);
    Utility account = new Utility(10000);
    File file = new File("account_data.txt")

    //main方法，取得所在类的一个实例，调用实质上的主方法，程序开始
    public static void main(String[] args) {
        FamilyAccount unit = new FamilyAccount();
        unit.mainMenu();
    }
    
    /*实质上的主方法，统领其余方法*/
    public void mainMenu() {
        int option;
        boolean loopFlag = true;
        
        //loopFlag为假时循环结束
        while(loopFlag == true) {
            //显示菜单及输入提示
            menu();
            //获取用户输入的选项
            if (scanner.hasNextInt()) {
                option = scanner.nextInt();
            } else {
                scanner.next();
                option = -1;
            }
            //根据选项进行相应操作
            switch(option) {
                case 1: System.out.println(account.getDetails()); break;  //直接调用getDetails()方法输出明细
                case 2: income(); break;          //导向income()方法，处理收入
                case 3: spending(); break;        //导向spending()方法，处理支出
                case 4: loopFlag = quit(); break; //quit()方法根据用户输入返回布尔值, 将其赋给loopFlag
                default: System.out.println("需要一个选项(1-4)，请重试。"); break;
            }
        }
        System.out.println("已退出。");  //程序成功退出的提示
    }

    //打印菜单
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

    //处理收入
    public void income() {
        double money = 0;
        String document;

        System.out.print("本次收入金额：");
        money = readDouble(false);  //方法参数为此方法内部一个功能的开关，此处关闭
        System.out.print("本次收入说明：");
        document = readString(); 
        account.incomeProcess(money, document);
    }

    //处理支出
    public void spending() {
        double money;
        String document;

        System.out.print("本次支出金额：");
        money = readDouble(true);  //功能开关打开
        System.out.print("本次支出说明：");
        document = readString();
        account.spendingProcess(money, document);
    }

    //判断是否退出，是则返回false
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

    //确保获得规范的金额输入
    public double readDouble(boolean optionFlag) {
        double money = 0;
        while(scanner.hasNext()) {
            try {
                money = Double.parseDouble( scanner.next() );
                if (money < 0) {
                    System.out.print("金额不能为负，请重试：");
                }
                else if (optionFlag && money > account.getBalance()) {
                //如果optionFlag为真，则执行此代码块，判断输入的金额是否大于余额，否则此代码块不执行
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

    //确保获得规范的明细输入
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
