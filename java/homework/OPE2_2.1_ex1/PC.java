public class PC extends Computer
{
    private String keyboard = "DELL¼üÅÌ";

    public PC (double cpu, int memory, int disk, int price, String keyboard) {
        super(cpu, memory, disk, price);
        this.keyboard = keyboard;
    }

    public void setKeyboard(String keyboard) {
        this.keyboard = keyboard;
    }

    public String getKeyboard() {
        return keyboard;
    }

    public void game() {
        System.out.println("keyboard: " + keyboard);
    }

    public String getDetails() {
        return super.getDetails() + ", keyboard: " + getKeyboard();
    }
}
