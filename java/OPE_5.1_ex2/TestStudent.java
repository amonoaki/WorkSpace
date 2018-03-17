public class TestStudent
{
    public static void main(String [] args)
    {
        Student student1 = new Student();
        System.out.println( student1.say() );
        Student student2 = new Student();
        student2.name = "Bill";
        System.out.println( student2.say() );
    }
}

class Student
{
    String name = "Tom";
    String gender = "male";
    int age = 19;
    int id = 3001;
    double score = 88.0;
    String say() {
        return ("name: " + name + ", gender: " + gender + ", age: " + age
                        + ", id: " + id + ", score: " + score);
    }
}
