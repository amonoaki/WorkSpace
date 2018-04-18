package CustomerView;

/*客户管理类*/

public class CustomerList
{
    private Customer[] customers;
    private int total = 0;  //计数器

    //创建一定容量的容器，用于存放客户，即给对象数组分配空间
    public CustomerList(int totalCustomer) {
        customers = new Customer[totalCustomer];
    }

    //增加客户，增加之前计数器已经>=数组长度，说明容量已满，不增加客户，返回false
    public boolean addCustomer(Customer customer) {
        if (total < customers.length) {
            customers[total] = customer;
            total += 1;  //增加一个客户，计数器加一
            return true;
        } else {
            return false;
        }
    }

    //修改客户，如果索引index越界，即不在数组范围内，不修改，返回false
    public boolean replaceCustomer(int index, Customer customer) {
        if (index >= 0 && index < customers.length) {
            customers[index] = customer;
            return true;
        } else {
            return false;
        }
    }

    //删除客户，原理为，将待删客户后的每一个元素依次向前移动一个位置；
    //如果索引index越界，不删除，返回false
    public boolean deleteCustomer(int index) {
        if (index >= 0 && index < customers.length) {
            for (int i = index; i < customers.length - 1; i++) {
                customers[i] = customers[i + 1];
            }
            total -= 1;
            return true;
        } else {
            return false;
        }
    }

    //返回整个数组
    public Customer[] getAllCustomers() {
        return customers;
    }

    //返回指定的数组元素
    public Customer getCustomer(int index) {
        return customers[index];
    }
}
