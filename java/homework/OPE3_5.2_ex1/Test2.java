/*
1. 编写Person类，包含姓名、年龄、体重等属性，提
供对应的访问方法；
2. 编写测试类Test1，在main方法中创建三个不同的Per
son对象，将这三个对象序列化到文件中；
3. 使用上述测试类，从文件中反序列化三个Person对
象，打印输出。验证序列化的正确
*/

import java.io.*;

public class Test2
{
    public static void main(String[] args) {

        Person[] persons = {
        new Person("1", 1, 1), 
        new Person("2", 2, 2), 
        new Person("3", 3, 3) 
        };
        Person[] persons1 = new Person[3];

        File file = new File("persons.txt");

        try {
            ObjectOutputStream out = new ObjectOutputStream( new FileOutputStream(file) );
            out.writeObject(persons);
            out.close();
            
            ObjectInputStream in = new ObjectInputStream( new FileInputStream(file) );
            persons1 = (Person[])in.readObject();
            in.close();

            for (Person p : persons1) {
                System.out.println(p.toString());
            }

        } catch(Exception e) {
            System.out.println("Something error...");
        }
    }
}
