public class Computer
{
    private double cpu = 3.2;
    private int memory = 6;
    private int disk = 1000;
    private int price = 1000;

    public Computer() {
    
    }

    public Computer(double cpu, int memory, int disk, int price) {
        this.cpu = cpu;
        this.memory = memory;
        this.disk = disk;
        this.price = price;
    }

    public void setCpu(double cpu) {
        this.cpu = cpu;
    }

    public void setMemory(int memory) {
        this.memory = memory;
    }

    public void setDisk(int disk) {
        this.disk = disk;
    }

    public double getCpu() {
        return cpu;
    }

    public int memory() {
        return memory;
    }

    public int disk() {
        return disk;
    }

    public String getDetails() {
        return ("CPU: " + cpu + "GHz, memory: " + memory + "G, disk: " + disk + "G");
    }
}
