public class Student
{
    private String name = "Tom";
    private String gender = "male";
    private int age = 19;
    private int id = 3001;
    private double score = 88.0;
    //set method
    public void setName(String name) {
        this.name = name;
    }
    public void setGender(String gender) {
        this.gender = gender;
    }
    public void setAge(int age) {
        this.age = age;
    }
    public void setId(int id) {
        this.id = id;
    }
    public void setScore(double score) {
        this.score = score;
    }
    //get method
    public String getName() {
        return name;
    }
    public String getGender() {
        return gender;
    }
    public int getAge() {
        return age;
    }
    public int getId() {
        return id;
    }
    public double getScore() {
        return score;
    }
    //say method
    public String say() {
        return ("name: " + name + ", gender: " + gender + ", age: " + age
                        + ", id: " + id + ", score: " + score);
    }
}
