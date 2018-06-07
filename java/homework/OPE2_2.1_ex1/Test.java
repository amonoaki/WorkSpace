public class Test
{
    public static void main(String [] args) {
        PC pc = new PC(3.6, 4, 1000, 2000, "Œ¢»Ì");
        NotePad notepad = new NotePad(2.2, 1, 32, 3000, 10);
        System.out.println(pc.getDetails());
        System.out.println(notepad.getDetails());
   }
}
