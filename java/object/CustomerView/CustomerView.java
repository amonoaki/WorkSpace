import java.util.Scanner;

/*主类*/

public class CustomerView
{
    CustomerList customers = new CustomerList(4);
    Scanner scanner = new Scanner(System.in);

    //main方法，取得自身类的一个实例，调用实质上的主方法enterMainMenu()
    public static void main(String[] args) {
        CustomerView init = new CustomerView();
        init.enterMainMenu();
    }

    //实质上的主方法
    public void enterMainMenu() {
        int option;
        boolean loopFlag = false;

        do {
            System.out.print("\n\n---------------------客户信息管理软件--------------------- \n\n" +
            "                      1 添 加 客 户\n" +
            "                      2 修 改 客 户\n" +
            "                      3 删 除 客 户\n" +
            "                      4 客 户 列 表\n" +
            "                      5 退       出\n\n" +
            "                      请选择(1-5)：");
            option = CMUtility.readInt(true);
            switch (option) {
                case 1: addNewCustomer(); break;    //增加客户
                case 2: modifyCustomer(); break;    //修改客户
                case 3: deleteCustomer(); break;    //删除客户
                case 4: listAllCustomers(); break;  //打印客户列表
                case 5: System.out.print("确认是否退出(Y/N) : ");
                        loopFlag = CMUtility.forSure();  //获得用户选择，为Y/y返回true；否则返回false
                        break;
                default: System.out.println("没有此选项，请重试。"); break;
            }
        } while (!loopFlag);  //loopFlag为 假 时循环继续
        System.out.println("已退出。");
    }

    //增加客户
    private void addNewCustomer() {
        Customer customer = new Customer();

        System.out.println("\n-------------------------添加客户------------------------- ");
        
        System.out.print("姓名：");
        customer.setName(scanner.next());
        System.out.print("性别：");
        customer.setGender(scanner.next().charAt(0));
        System.out.print("年龄：");
        customer.setAge(CMUtility.readInt(true));
        System.out.print("电话：");
        customer.setPhone(scanner.next());
        System.out.print("邮箱：");
        customer.setEmail(scanner.next());
        scanner.nextLine();  //吸收回车，否则会对后面输入产生影响，体现在每次新增用户后，对该用户的第一次修改时。

        if (customers.addCustomer(customer)) {
            System.out.println("-------------------------添加完成-------------------------");
        } else {
            System.out.println("空间已满，无法添加。");
        }
    }

    //修改客户
    private void modifyCustomer() {
        Customer customer = new Customer();
        int index;

        System.out.println("\n-------------------------修改客户------------------------- ");
        System.out.print("请选择待修改客户编号(-1退出)：");
        if (( index = CMUtility.readInt(false) - 1 ) != -2) {    //当用户输入-1，即索引index为-2时，不修改
            String temp;
            Customer originalCustomer;
            if (customers.getCustomer(index) != null && customers.getCustomer(index).getName() != null) {
            //只有当返回的不是空对象时才进行修改操作，
            //返回空对象说明编号无效，在else处打印提示
                originalCustomer = customers.getCustomer(index);            

                //修改姓名
                System.out.print("姓名(" + originalCustomer.getName() + "):");
                temp = scanner.nextLine();
                if (temp.equals("")) {
                    customer.setName(originalCustomer.getName());
                } else {
                    customer.setName(temp);
                }
                //修改性别
                System.out.print("性别(" + originalCustomer.getGender() + "):");
                temp = scanner.nextLine();
                if (temp.equals("")) {
                    customer.setGender(originalCustomer.getGender());
                } else {
                    customer.setGender(temp.charAt(0));
                }
                //修改年龄
                System.out.print("年龄(" + originalCustomer.getAge() + "):");
                temp = scanner.nextLine();
                int age;
                if (temp.equals("")) {
                    customer.setAge(originalCustomer.getAge());
                    /*此部分修改年龄的代码还没处理好，显得啰嗦。*/
                } else {
                    try {
                        age = Integer.parseInt(temp);
                        if (age > 0) {
                            customer.setAge(age);
                        } else {
                            System.out.println("检测到负数，此项未修改。");
                            customer.setAge(originalCustomer.getAge());
                        }
                    } catch(NumberFormatException e) {
                        System.out.println("检测到非数字字符，此项未修改。");
                        customer.setAge(originalCustomer.getAge());
                    }
                }
                //修改号码
                System.out.print("电话号码(" + originalCustomer.getPhone() + "):");
                temp = scanner.nextLine();
                if (temp.equals("")) {
                    customer.setPhone(originalCustomer.getPhone());
                } else {
                    customer.setPhone(temp);
                }
                //修改邮箱
                System.out.print("电子邮箱(" + originalCustomer.getEmail() + "):");
                temp = scanner.nextLine();
                if (temp.equals("")) {
                    customer.setEmail(originalCustomer.getEmail());
                } else {
                    customer.setEmail(temp);
                }

            //编号无效时打印提示
            } else {
                System.out.println("编号无效，请重试");
            }

            if (customers.replaceCustomer(index, customer)) {
                System.out.println("-------------------------修改完成------------------------- ");
            }
        }
    }

    //删除客户
    private void deleteCustomer() {
        int index;

        System.out.println("\n-------------------------删除客户-------------------------");
        System.out.print("请选择待删除客户编号(-1退出)：");
        if (( index = CMUtility.readInt(false) - 1) != -2) {      //当用户输入-1，即索引index为-2时，不删除
            System.out.print("确认是否删除(Y/N)：");
            if (CMUtility.forSure()) {
                if (customers.deleteCustomer(index)) {
                    System.out.println("-------------------------删除完成-------------------------");
                } else {
                    System.out.println("该客户不存在，操作无效");
                }
            } else {
                System.out.println("操作已取消");
            }
        } else {
        	System.out.println("操作取消，已返回上一层");
        }
    }

    //打印客户列表
    private void listAllCustomers() {
        Customer[] allCustomers = customers.getAllCustomers();

        System.out.println("\n-------------------------客户列表-------------------------\n");
        System.out.println("编号\t姓名\t性别\t年龄\t电话\t\t邮箱");
        int id = 0;
        for (Customer cus : allCustomers) {
        	id++;
        	if (cus == null) {
        		System.out.println("对象为空");
        	}
            if (cus != null && cus.getName() != null) {
                System.out.println(id + "\t" + cus.toString());
            }
        }
        System.out.println("\n-----------------------客户列表完成-----------------------");
    }
}
