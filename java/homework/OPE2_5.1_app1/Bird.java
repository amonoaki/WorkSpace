public class Bird extends Pet
{
    private boolean canFly;

    public Bird(String name, int age, double weight, boolean canFly) {
        super(name, age, weight);
        this.canFly = canFly;
    }

    public void speak() {
    ;
    }

    public void eat() {
    ;
    }

    public String toString() {
        return super.toString() + "£¬ÄÜ·ñ·ÉÏè£º" + canFly;
    }
}
