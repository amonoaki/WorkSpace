public abstract class Frock {
	
	private int size;
	private String color;
	private double price;
	
	public Frock() {
		size = 180;
		color = "黑色";
		price = 200;
	}
	
	public Frock(int size, String color, double price) {
		this.size = size;
		this.color = color;
		this.price = price;
	}
	
	public void setSize(int size) {
		this.size = size;
	}
	
	public int getSize() {
		return size;
	}
	
	public void setColor(String color) {
		this.color = color;
	}

    public String getColor() {
        return color;
    }
	
	public void setPrice(double price) {
		this.price = price;
	}
	
	public double getPrice() {
		return price;
	}
	
	@Override
	public String toString() {
		return "尺寸 : " + size + ", 颜色 : " + color + ", 价格 : " + price;
	}
	
    public abstract double calcArea();
}
