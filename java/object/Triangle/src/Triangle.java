//5三角形类

public class Triangle extends ClosedFigure {
	
	public Point p1, p2, p3;
	
	public Triangle(Point p1, Point p2, Point p3) throws IllegalArgumentException{
		
		//点
		this.p1 = p1;
		this.p2 = p2;
		this.p3 = p3;
		
//		//线
//		Line line1 = new Line(p1, p2);
//		Line line2 = new Line(p2, p3);
//		Line line3 = new Line(p1, p3);
//		
//		//长度
//		double length1 = line1.length();
//		double length2 = line2.length();
//		double length3 = line3.length();
//		
//		//判断：两边之和大于第三边，两边之差小于第三边
//		boolean flag1 = (length1 + length2 > length3 && Math.abs(length1 - length2) < length3);
//		boolean flag2 = (length2 + length3 > length1 && Math.abs(length2 - length3) < length1);
//		boolean flag3 = (length1 + length3 > length2 && Math.abs(length1 - length3) < length2);
//		
//		if (!(flag1 && flag2 && flag3)) {
//			throw new IllegalArgumentException();
//		}
	}
	
	public boolean check() {
		
		//线
		Line line1 = new Line(p1, p2);
		Line line2 = new Line(p2, p3);
		Line line3 = new Line(p1, p3);
		
		//长度
		double length1 = line1.length();
		double length2 = line2.length();
		double length3 = line3.length();
		
		//判断：两边之和大于第三边，两边之差小于第三边
		boolean flag1 = (length1 + length2 > length3 && Math.abs(length1 - length2) < length3);
		boolean flag2 = (length2 + length3 > length1 && Math.abs(length2 - length3) < length1);
		boolean flag3 = (length1 + length3 > length2 && Math.abs(length1 - length3) < length2);
		
		if (!(flag1 && flag2 && flag3)) {
			throw new IllegalArgumentException();
		} else {
			return true;
		}
	}
	
	public boolean check2() throws MyFigureException {
		
		//线
		Line line1 = new Line(p1, p2);
		Line line2 = new Line(p2, p3);
		Line line3 = new Line(p1, p3);
		
		//长度
		double length1 = line1.length();
		double length2 = line2.length();
		double length3 = line3.length();
		
		//判断：两边之和大于第三边，两边之差小于第三边
		boolean flag1 = (length1 + length2 > length3 && Math.abs(length1 - length2) < length3);
		boolean flag2 = (length2 + length3 > length1 && Math.abs(length2 - length3) < length1);
		boolean flag3 = (length1 + length3 > length2 && Math.abs(length1 - length3) < length2);
		
		if (!(flag1 && flag2 && flag3)) {
			throw new MyFigureException("三个点不能构成三角形");
		} else {
			return true;
		}
	}
}
