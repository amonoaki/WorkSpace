import java.io.*;

public class TestBufferReader
{
    public static void main(String[] args) {
        File f = new File("TestBufferReader.java");

        try {
            BufferedReader fin = new BufferedReader(new FileReader(f));

            String str = null;
            int i = 0;

            while ((str = fin.readLine()) != null) {
                System.out.printf("%2d %s\n", i+1, str); 
                i++;
            }

            fin.close();
        } catch(IOException e) {
            System.out.println("Something Error.");
        }
    }
}
