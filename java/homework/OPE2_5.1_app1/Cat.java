public class Cat extends Pet
{
    private String color;

    public Cat(String name, int age, double weight, String color) {
        super(name, age, weight);
        this.color = color;
    }
    public void speak() {
    ;
    }

    public void eat() {
    ;
    }

    public String toString() {
        return super.toString() + "£¬ÑÕÉ«£º" + color;
    }
}
