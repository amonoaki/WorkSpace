package CustomerView;

public class CustomerList
{
    private Customer[] customers;
    private int total = 0;

    public CustomerList(int totalCustomer) {
        customers = new Customer[totalCustomer];
    }

    public boolean addCustomer(Customer customer) {
        if (total < customers.length) {
            customers[total] = customer;
            total += 1;
            return true;
        } else {
            return false;
        }
    }

    public boolean replaceCustomer(int index, Customer customer) {
        if (index >= 0 && index < customers.length) {
            customers[index] = customer;
            return true;
        } else {
            return false;
        }
    }

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

    public Customer[] getAllCustomers() {
        return customers;
    }

    public Customer getCustomer(int index) {
        return customers[index];
    }
}
