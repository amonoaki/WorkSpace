//测试类
public class Test {

	public static void main(String[] args) {

		//创建三个点
		Point p1, p2, p3;
		p1 = new Point(1, 1);
		p2 = new Point(2, 2);
		p3 = new Point(3, 3);
		
		try {
			Triangle triangle1 = new Triangle(p1, p2, p3);
//			if (triangle1.check()) {
//				System.out.println("可以构成三角形");
//			}
			if (triangle1.check2()) {
				System.out.println("可以构成三角形");
			}
		} 
		catch(MyFigureException e) {
			System.out.println("捕获到自定义异常");
			System.out.println(e);
		}
		catch(IllegalArgumentException e) {
			System.out.println("三个点不能构成三角形");
		} 
		finally {
			System.out.println("程序正常退出");
		}
	}

}
