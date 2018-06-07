package com.oracle.team.view;

import com.oracle.team.domain.Employee;
import com.oracle.team.service.NameListService;
import com.oracle.team.service.TeamService;

public class TeamView {

	private NameListService listSvc = new NameListService();
	private TeamService teamSvc = new TeamService();
	
	
	public static void main(String[] args) {
		
		TeamView util = new TeamView();
		util.enterMainMenu();
	}
	
	
	public void enterMainMenu() {
		
		listAllEmployees();

		boolean loopFlag = true;
		while(loopFlag) {
			System.out.print("1-团队列表  2-添加团队成员  3-删除团队成员 4-退出   请选择(1-4)： _");
			
			switch (TSUtility.readMenuSelection()) {
			case '1':
				System.out.println("尚未开发");
				break;
			case '2':
				System.out.println("尚未开发");
				break;
			case '3':
				System.out.println("尚未开发");
				break;
			case '4':
				System.out.print("确认是否退出(Y/N)");
				if (TSUtility.readConfirmSelection() == 'Y') {
					loopFlag = false;
				}
				break;
			default:
				break;
			}
		}
		System.out.println("已退出");
		
	}
	
	private void listAllEmployees() {
		
		Employee[] allEmployees = listSvc.getAllEmployees();
		
		System.out.println("-------------------------------------开发团队调度软件-------------------------------------- \n");
		System.out.println("ID\t姓名\t年龄\t工资\t职位\t状态\t奖金\t股票\t领用设备\n");
		
		for (Employee employee : allEmployees) {
			System.out.println(employee.toString());
		}
		
		System.out.println("--------------------------------------------------------------------------------------------------- ");
		
	}
}
