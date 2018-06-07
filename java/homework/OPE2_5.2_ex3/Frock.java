public abstract class Frock implements Clothing
{
	int size;
	String color;

    public Frock() {}
    public Frock(int size, String color) {
        this.size = size;
        this.color = color;
    }

  	public abstract double calcArea();

    public String getColor() {
        return color;
    }
}
