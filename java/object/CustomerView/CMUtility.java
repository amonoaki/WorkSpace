package CustomerView;
import java.util.Scanner;

/*工具类，规范用户输入*/

public class CMUtility
{
    //确保获得规范的整数输入
    public static int readInt(boolean optionFlag) {
        Scanner scanner = new Scanner(System.in);
        
        int input = 0;
        while(scanner.hasNext()) {
            try {
                input = Integer.parseInt( scanner.next() );
                if (optionFlag && input < 0) {
                    //当功能开关打开，即optionFlag为true时，此代码块执行，否则不执行
                    System.out.print("输入不能为负，请重试：");
                }
                else {
                    break;
                }
            } catch(NumberFormatException e) {
                System.out.print("输入应为数字，请重试:");
            }
        }
        //scanner.nextLine();
        return input;
    }

    //确认用户选择，Y/N
    public static boolean forSure() {
        Scanner scanner = new Scanner(System.in);

        String temp = scanner.next();
        if (temp.equals("Y") || temp.equals("y")) {
            return true;
        } else {
            return false;
        }
    }
}
