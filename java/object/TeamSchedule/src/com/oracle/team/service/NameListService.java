package com.oracle.team.service;

import com.oracle.team.domain.*;

public class NameListService {

	private Employee[] employees = new Employee[12];
		
	public NameListService() {
		for (int i = 0; i < 12; i++) {
			
			int people_type = Integer.parseInt(Data.EMPLOYEES[i][0]);
			int id = Integer.parseInt(Data.EMPLOYEES[i][1]);
			String name = Data.EMPLOYEES[i][2];
			int age = Integer.parseInt(Data.EMPLOYEES[i][3]);
			double salary = Double.parseDouble(Data.EMPLOYEES[i][4]);
			int equipment_type = 0;
			Equipment equipment = null;
			
			if (i != 0) {
				equipment_type = Integer.parseInt(Data.EQIPMENTS[i][0]);
			}
			
			if (people_type == Data.EMPLOYEE) {
				employees[i] = new Employee(id, name, age, salary);
			} else {
				
				if (equipment_type == Data.PC) {
					equipment = new PC(Data.EQIPMENTS[i][1], Data.EQIPMENTS[i][2]);
				}
				else if (equipment_type == Data.NOTEBOOK) {
					equipment = new NoteBook(Data.EQIPMENTS[i][1], Double.parseDouble(Data.EQIPMENTS[i][2]));
				}
				else {
					equipment = new Printer(Data.EQIPMENTS[i][1], Data.EQIPMENTS[i][2]);
				}
				
				if (people_type == Data.PROGRAMMER) {
					employees[i] = new Programmer(id, name, age, salary, equipment);
				}
				else if (people_type == Data.DESIGNER) {
					employees[i] = new Designer(id, name, age, salary, equipment, Double.parseDouble(Data.EMPLOYEES[i][5]));
				}
				else if (people_type == Data.ARCHITECT) {
					employees[i] = new Architect(id, name, age, salary, equipment, Double.parseDouble(Data.EMPLOYEES[i][5]), Integer.parseInt(Data.EMPLOYEES[i][6]));
				}
			}
		}
	}
	
	public Employee[] getAllEmployees() {
		return employees;
	}
	
	public Employee getEmployee(int id) throws TeamException{
		int i;
		
		for (i = 0; i < 12; i++) {
			if (id == employees[i].getId()) {
				return employees[i];
			}
		}
		
		throw new TeamException("该员工不存在");
	}
	
	/*
	public static void main(String[] args) {
		NameListService util = new NameListService();
		Employee[] allEmployees = util.getAllEmployees();
		
		System.out.println("-------------------------------------开发团队调度软件-------------------------------------- \n");
		System.out.println("ID\t姓名\t年龄\t工资\t职位\t状态\t奖金\t股票\t领用设备\n");
		
		for (Employee employee : allEmployees) {
			System.out.println(employee.toString());
		}
		
		System.out.println("--------------------------------------------------------------------------------------------------- ");
		System.out.print("1-团队列表  2-添加团队成员  3-删除团队成员 4-退出   请选择(1-4)： _");
		
	}
	*/
}
