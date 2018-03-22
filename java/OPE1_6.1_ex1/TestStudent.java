public class TestStudent
{
    public static void main(String [] args)
    {
        Student student = new Student();
        student.setName("Bill");
        student.setGender("male");
        student.setId(10021);
        student.setAge(20);
        student.setScore(77);
        System.out.println("name: " + student.getName() + ", Gender: " + student.getGender()
                        + ", id: " + student.getId() + ", age: " + student.getAge()
                        + ", score: " + student.getScore());
    }
}
