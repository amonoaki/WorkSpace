public class TestDog
{
    public static void main(String [] args)
    {
        Dog dog1 = new Dog();
        Dog dog2 = new Dog();
        System.out.println(dog1.say());
        System.out.println(dog2.say());
        dog1.name = "¾©°Í";
        dog2.name = "¼ªÍÞÍÞ";
        dog2.weight = 8;
        System.out.println(dog1.say());
        System.out.println(dog2.say());
    }
}

class Dog
{
    String name;
    int age = 1;
    double weight = 10;
    String say() {
        return ("name: " + name + ", age: " + age + ", weight: " + weight);
    }
}
