//2线类
public class Line {

	public Point p1, p2;
	
	public Line(Point p1, Point p2) {
		this.p1 = p1;
		this.p2 = p2;
	}
	
	public double length() {
		double x = p1.x - p2.x;
		double y = p1.y - p2.y;
		
		double length = Math.sqrt(x*x + y*y);
		
		return length;
	}
	
	public String toString() {
		return "两点间距离" + length();
	}
}
