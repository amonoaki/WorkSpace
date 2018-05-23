//团队管理

package com.oracle.team.service;

import com.oracle.team.domain.Architect;
import com.oracle.team.domain.Designer;
import com.oracle.team.domain.Employee;
import com.oracle.team.domain.Programmer;

public class TeamService {

	private int counter = 1;
	private final int MAX_MEMBER = 6, MAX_PROGRAMMER = 3, MAX_DESIGNER = 2, MAX_ARCHITECT = 1;
	private Programmer[] team = new Programmer[MAX_MEMBER];
	private int total = 0;
	
	public Programmer[] getTeam() {
		Programmer[] exactTeam = new Programmer[total];
		
		for (int i = 0; i < total; i++) {
			exactTeam[i] = team[i];
		}
		
		return exactTeam;
	}
	
	public void addMember(Employee e) throws TeamException {
		int programmer_counter = 0, designer_counter = 0, architect_counter = 0; 
		
		if (total >= MAX_MEMBER) {
			throw new TeamException("团队成员已满");
		}
		else if (!(e instanceof Programmer)){
			throw new TeamException("该员工不是开发人员，无法添加");
		}
		Programmer pro = (Programmer)e;
		
		for (Programmer p : team) {
			if (p != null) {
				if (p.getId() == pro.getId()) {
					throw new TeamException("该员工已是团队成员");
				}
				
				if (p instanceof Architect) {
					architect_counter++;
				}
				else if (p instanceof Designer) {
					designer_counter++;
				}
				else if (p instanceof Programmer) {
					programmer_counter++;
				}
			}
		}
		
		//将欲添加成员加入计数
		if (pro instanceof Architect) {
			architect_counter++;
		}
		else if (pro instanceof Designer) {
			designer_counter++;
		}
		else if (pro instanceof Programmer) {
			programmer_counter++;
		}
		
		//对计数结果进行判断，看各类成员是否满员
		if (architect_counter > MAX_ARCHITECT) {
			throw new TeamException("团队中架构师数量已满");
		}
		else if (designer_counter > MAX_DESIGNER) {
			throw new TeamException("团队中设计师数量已满");
		}
		else if (programmer_counter > MAX_PROGRAMMER) {
			throw new TeamException("团队中程序员数量已满");
		}
		
		//该成员经过检查，确认可以添加
		pro.setMemberId(counter);
		team[total] = pro;
		counter++;
		total++;
		
	}
	
	public void removeMember(int memberId) throws TeamException {
		int i, j;
		
		for (i = 0; i < total; i++) {
			if (team[i].getId() == memberId) {
				for (j = i+1; j < total; j++) {
					team[j-1] = team[j];
				}
				team[total-1] = null;
				return;
			}
		}
		
		if (i == total) {
			throw new TeamException("找不到该团队人员");
		}
	}
	
	public static void main(String[] args) {
		NameListService nameListService = new NameListService();
		Employee[] employees = nameListService.getAllEmployees();
		TeamService teamService = new TeamService();
		Programmer[] programmers = teamService.getTeam();
		
		try {
			teamService.addMember(employees[6]);
			teamService.addMember(employees[2]);
			teamService.addMember(employees[3]);
			teamService.addMember(employees[4]);
			teamService.addMember(employees[5]);
		} catch (TeamException e) {
			System.out.println(e);
		}
		
		for (Programmer p : programmers) {
			System.out.println(p);
		}
		
	}
	
}
