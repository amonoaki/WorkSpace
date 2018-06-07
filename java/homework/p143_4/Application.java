abstract class Animal
{
    abstract void cry();
    abstract String getAnimalName();
}

class Simulator
{
    void playSound(Animal animal) {
        animal.cry();
        System.out.println( animal.getAnimalName() );
    }
}

class Dog extends Animal
{
    void cry() {
        System.out.println("Wang wang...");
    }
    String getAnimalName() {
        return "*Dog*";

    }
}

class Cat extends Animal
{
    void cry() {
        System.out.println("Miao miao...");
    }
    String getAnimalName() {
        return "*Cat*";
    }
}

public class Application
{
    public static void main(String [] args)
    {
        Animal animal;
        Simulator simulator = new Simulator();
        animal = new Dog();
        simulator.playSound(animal);
        animal = new Cat();
        simulator.playSound(animal);

    }
}
