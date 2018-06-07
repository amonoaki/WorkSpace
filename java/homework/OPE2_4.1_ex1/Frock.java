public class Frock
{
    private static int currentNum = 100000;
    public static int getNextNum() {
        currentNum += 100;
        return currentNum;
    }
}
