public class Shirt extends Frock{
	public Shirt() {}
	
	public Shirt(int size, String color){
        super(size, color);
	}
	
	public int getSize(){
	    return size;
	}
	
	public double calcArea() {
		return getSize() * 1.3;
	}
	
	public String getDetails() {
		return toString();
	}
}
