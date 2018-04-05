public class Account
{
    private double balance;
    private String details = "收支\t账户金额\t收支金额\t说  明\n";

    public Account() {
        this.balance = 0;
    }
    public Account(double balance) {
        this.balance = balance;
    }

    public String getDetails() {
        return details;
    }

    public void incomeProcess(double income, String document) {
        balance += income;
        details = getDetails() + "收入\t" + balance + "\t\t" + income + "\t\t" + document + "\n";
    }

    public void spendingProcess(double spending, String document) {
        balance -= spending;
        details = getDetails() + "支出\t" + balance + "\t\t" + spending + "\t\t" + document + "\n";
    }
}
