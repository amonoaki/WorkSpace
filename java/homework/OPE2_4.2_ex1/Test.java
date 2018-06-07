public class Test
{
    public static void main(String [] args)
    {
        Frock frock1 = new Frock();
        Frock frock2 = new Frock();
        Frock frock3 = new Frock();
        System.out.println("serial number 1:" + frock1.getSerialNumber());
        System.out.println("serial number 2:" + frock2.getSerialNumber());
        System.out.println("serial number 3:" + frock3.getSerialNumber());
        frock1.size = 184;
        frock1.color = "白色";
        frock1.price = 232;
        frock1.size = 185;
        frock1.color = "白色";
        frock1.price = 222;
        frock1.size = 190;
        frock1.color = "红色";
        frock1.price = 300;
    }
}
