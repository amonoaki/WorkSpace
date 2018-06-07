public class Computer
{
    double cpu = 3.2;
    int memory = 6;
    int disk = 1000;

    public String getDetails() {
        return ("CPU: " + cpu + "GHz, memory: " + memory + "G, disk: " + disk + "G");
    }
}
