public class Test
{
    public static void main(String [] args) {
        PC pc = new PC();
        NotePad notepad = new NotePad();
        System.out.println("class PC: keyboard: " + pc.keyboard);
        pc.game();
        System.out.println("class Computer: " + pc.getDetails());
        System.out.println("class NotePad: gps: " + notepad.gps);
        notepad.navigate();
        System.out.println("class Computer: " + notepad.getDetails());
    }
}
