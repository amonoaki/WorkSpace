public class NotePad extends Computer
{
    private int gps = 10;
    
    public NotePad(double cpu, int memory, int disk, int price, int gps) {
        super(cpu, memory, disk, price);
        this.gps = gps;
    }
    public void setGps(int gps) {
        this.gps = gps;
    }

    public int getGps() {
        return gps;
    }

    public void navigate() {
        System.out.println("gps:" + gps);
    }
    
    public String getDetails() {
        return super.getDetails() + ", gps: " + gps; 
    }
}
