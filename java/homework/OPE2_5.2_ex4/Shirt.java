public class Shirt extends Frock implements Clothing {
	
	public Shirt() {}
	
	public Shirt(int size, String color, double price) {
		super(size, color, price);
	}

    public String getColor() {
        return super.getColor();
    }
	
	public double calcArea() {
		return getSize() * 1.3;
	}
	
	public String getDetails() {
		return toString();
	}
}
