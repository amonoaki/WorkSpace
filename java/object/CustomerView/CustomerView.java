package CustomerView;
import java.util.Scanner;

public class CustomerView
{
    CustomerList customers = new CustomerList(10);
    Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        CustomerView init = new CustomerView();
        init.enterMainMenu();
    }

    public void enterMainMenu() {
        int option;
        
        do {
            System.out.print("-----------------客户信息管理软件----------------- \n\n" +
            "                  1 添 加 客 户\n" +
            "                  2 修 改 客 户\n" +
            "                  3 删 除 客 户\n" +
            "                  4 客 户 列 表\n" +
            "                  5 退       出\n\n" +
            "                  请选择(1-5)：");
            if (scanner.hasNextInt()) {
                option = scanner.nextInt();
            } else {
                scanner.nextLine();
                option = 0;
            }
            switch (option) {
                case 1: addNewCustomer(); break;
                case 2: modifyCustomer(); break;
                case 3: deleteCustomer(); break;
                case 4: listAllCustomers(); break;
                case 5: 
                        System.out.print("确认是否退出(Y/N) : ");
                        String temp = scanner.next();
                        if (temp.equals("Y") || temp.equals("y")) {
                            System.out.println("已退出。"); 
                            break;
                        } else {
                            option = 0;
                            break;
                        }
                default: System.out.println("选项错误，请重试。"); break;
            }
        } while (option != 5);
    }

    private void addNewCustomer() {
        Customer customer = new Customer();

        System.out.println("---------------------添加客户--------------------- ");
        
        System.out.print("姓名：");
        customer.setName(scanner.next());
        System.out.print("性别：");
        customer.setGender(scanner.next());
        System.out.print("年龄：");
        if (scanner.hasNextInt()) {
            customer.setAge(scanner.nextInt());
        } else {
            scanner.next();
        }
        System.out.print("电话：");
        customer.setPhone(scanner.next());
        System.out.print("邮箱：");
        customer.setEmail(scanner.next());

        if (customers.addCustomer(customer)) {
            System.out.println("---------------------添加完成---------------------");
        } else {
            System.out.println("空间已满，无法添加。");
        }
    }

    private void modifyCustomer() {
        Customer customer = new Customer();
        int index;

        System.out.println("---------------------修改客户--------------------- ");
        System.out.print("请选择待修改客户编号(-1退出)：");
        if (( index = scanner.nextInt() - 1 ) != -2) {
            scanner.nextLine();

            String temp;
            Customer originalCustomer = customers.getCustomer(index);
            
            System.out.print("姓名(" + originalCustomer.getName() + "):");
            temp = scanner.nextLine();
            if (temp.equals("")) {
                customer.setName(originalCustomer.getName());
            } else {
                customer.setName(temp);
            }

            System.out.print("性别(" + originalCustomer.getGender() + "):");
            temp = scanner.nextLine();
            if (temp.equals("")) {
                customer.setGender(originalCustomer.getGender());
            } else {
                customer.setGender(temp);
            }

            System.out.print("年龄(" + originalCustomer.getAge() + "):");
            temp = scanner.nextLine();
            if (temp.equals("")) {
                customer.setAge(originalCustomer.getAge());
            } else {
                try {
                    customer.setAge(Integer.parseInt(temp));
                } catch (NumberFormatException e){
                    System.out.println("(数据异常，不是整数，此项未修改。)");
                    customer.setAge(originalCustomer.getAge());
                }
            }

            System.out.print("电话号码(" + originalCustomer.getPhone() + "):");
            temp = scanner.nextLine();
            if (temp.equals("")) {
                customer.setPhone(originalCustomer.getPhone());
            } else {
                customer.setPhone(temp);
            }

            System.out.print("电子邮箱(" + originalCustomer.getEmail() + "):");
            temp = scanner.nextLine();
            if (temp.equals("")) {
                customer.setEmail(originalCustomer.getEmail());
            } else {
                customer.setEmail(temp);
            }

            if (customers.replaceCustomer(index, customer)) {
                System.out.println("---------------------修改完成--------------------- ");
            }
        }
    }

    private void deleteCustomer() {
        int index;

        System.out.println("---------------------删除客户---------------------");
        System.out.print("请选择待删除客户编号(-1退出)：");
        if (( index = scanner.nextInt() - 1) != -2) {
            String temp;
            System.out.print("确认是否删除(Y/N)：");
            temp = scanner.next();
            if (temp.equals("Y") || temp.equals("y")) {
                if (customers.deleteCustomer(index)) {
                    System.out.println("---------------------删除完成---------------------");
                }
            }
        }
    }

    private void listAllCustomers() {
        Customer[] allCustomers = new Customer[10];
        allCustomers = customers.getAllCustomers();

        System.out.println("---------------------------客户列表-------------------------");
        System.out.println("编号\t姓名\t性别\t年龄\t电话\t\t邮箱");
        for (int i = 0; i < 10; i++) {
            if (allCustomers[i] != null && allCustomers[i].getName() != "") {
                System.out.println((i + 1) + "\t" + allCustomers[i].getName() + "\t"+ allCustomers[i].getGender() +
                    "\t" + allCustomers[i].getAge() + "\t" + allCustomers[i].getPhone() + "\t" + allCustomers[i].getEmail());
            }
        }
        System.out.println("---------------------------客户列表完成---------------------");
    }
}

//将输入重整为一个方法，解决年龄无法跳过的问题。
