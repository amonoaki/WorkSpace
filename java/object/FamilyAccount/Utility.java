package FamilyAccount;

public class Utility
{
    private double balance;
    private StringBuffer details = new StringBuffer("收支\t账户金额\t收支金额\t说  明\n");

    public Utility() {
        this.balance = 0;
    }
    public Utility(double balance) {
        this.balance = balance;
    }

    public double getBalance() {
        return balance;
    }

    public StringBuffer getDetails() {
        return details;
    }

    //处理收入
    public void incomeProcess(double income, String document) {
        balance += income;
        details = details.append("收入\t" + balance + "\t\t" + income + "\t\t" + document + "\n");
    }
    //处理支出
    public void spendingProcess(double spending, String document) {
        balance -= spending;
        details = details.append("支出\t" + balance + "\t\t" + spending + "\t\t" + document + "\n");
    }
}
