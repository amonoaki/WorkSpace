public class Dog extends Pet
{
    private String type;

    public Dog(String name, int age, double weight, String type) {
        super(name, age, weight);
        this.type = type;
    }

    public void speak() {
    ;
    }
    
    public void eat() {
    ;
    }

    public String toString() {
        return super.toString() + "£¨¿‡–Õ£∫" + type;
    }
}
