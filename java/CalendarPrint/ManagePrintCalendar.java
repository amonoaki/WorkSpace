import java.util.Calendar;
import java.util.Scanner;

//di类为主类
public class ManagePrintCalendar
{
	public static void main(String[] args) {

		//获取年份
		Scanner in_t1=new Scanner(System.in);
		int year=in_t1.nextInt();
		in_t1.close();

		//创建自定义类的实例，一个月份对应一个实例对象
		PrintCalendar[] printCalendar = new PrintCalendar[12];
		for (int i = 0; i < 12; i++) {
			printCalendar[i] = new PrintCalendar(year, i+1);
		}

		//循环打印三大行，每大行4个月，每个月8小行
		for (int k = 0; k < 3; k++) {
			for (int i = 0; i < 8; i++) {
				for (int j = 4*k; j < (4*k + 4); j++) {
					printCalendar[j].printCalendar(i);
					System.out.print("       ");
				}
				System.out.println("");
			}
		}	
	}
}

//自定义类，为打印日历中一个月份的抽象
class PrintCalendar {

	int runnian=0;
	int year, month, weekDay, lastDay;
	int j;
	Calendar cal = Calendar.getInstance();
	
	//构造方法初始化各个年份、月份、初始星期、是否闰年、该月天数
	public PrintCalendar(int year, int month) {
		this.year = year;  //年份
		this.month = month;  //月份
		if(((year%4==0)&&(year%100!=0))||(year%400==0)){
			this.runnian=1;  //是否闰年
		}

		cal.set(year, month-1, 1);
		this.weekDay=cal.get(Calendar.DAY_OF_WEEK) - 1;  //第一天是星期几

		this.j = weekDay;

		//该月多少天
		if(month==1||month==3||month==5||month==7||month==8||month==10||month==12) {
			this.lastDay=31;
		}
		else if(month==2){
			if (runnian==1)
				this.lastDay=29;
			else
				this.lastDay=28;
		}
		else {
			this.lastDay = 30;
		}
	}

	//根据条件逐行打印这个月
	public void printCalendar(int row) {

		if(row == 2) {
			for (int i = 0; i < weekDay; i++) {
				System.out.print("    ");
			}
		}

		if(row == 0) {
			System.out.print("############"+month+"月############ ");
		}
		else if(row == 1) {
			System.out.print("日  一  二  三  四  五  六  ");
		}
		else if(row >= 2 && row < 8) {
			for (j += 1; j <= weekDay+lastDay; j++) {
				System.out.printf("%2d  ", (j-weekDay));
				if (j%7 == 0) {
					break;
				}
			}
			if(j > weekDay+lastDay) {
				j -= 1;
				for (; j <= 42; j++) {
					if (j%7 == 0) {
						break;
					}
					System.out.printf("    ");
				}
			}
			if (row == 7 && j == 35) {
				for (j += 1; j <= 42; j++) {
					System.out.printf("    ");
					if (j%7 == 0) {
						break;
					}
				}
			}

		}
	}
}

