public class Computer
{
    private double cpu = 3.2;
    private int memory = 6;
    private int disk = 1000;

    public String getDetails() {
        return ("CPU: " + cpu + "GHz, memory: " + memory + "G, disk: " + disk + "G");
    }
}
