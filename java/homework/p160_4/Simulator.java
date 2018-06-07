public class Simulator
{
    void playSound(Animal animal) {
        System.out.println("Animal name: " + animal.getAnimalName());
        animal.cry();
    }
}
