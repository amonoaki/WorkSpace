public class Test
{
    public static void main(String [] args)
    {
        int max;  //to store the index of the largest weight 
        Pet temp;

        Pet [] animal = {
            new Cat("小花", 2, 5, "花"),
            new Cat("小黑", 3, 6, "黑"),
            new Dog("大旺", 2, 10, "泰迪"),
            new Dog("小吉", 3, 4, "吉娃娃"),
            new Bird("小飞", 1, 1, true),
            new Bird("大笨", 2, 2, false)
        };

        for (int i = 0; i < animal.length - 1; i++) {
            max = i;
            for (int j = i + 1; j < animal.length; j++) {
                if (animal[j].getWeight() > animal[max].getWeight()) {
                    max = j;
                }
            }
            temp = animal[i];
            animal[i] = animal[max];
            animal[max] = temp;
        }

        for (int i = 0; i < animal.length; i++) {
            System.out.println(animal[i].toString());
        }
    }
}
