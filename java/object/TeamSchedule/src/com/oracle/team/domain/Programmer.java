package com.oracle.team.domain;

import com.oracle.team.service.Status;

public class Programmer extends Employee 
{
	private int memberId;
	private Equipment equipment;
	private Status status = Status.FREE;
	
	//1
	public Programmer(int id, String name, int age, double salary,Equipment equipment) 
	{
		super(id, name, age, salary);
		this.equipment=equipment;
		// TODO Auto-generated constructor stub
	}

	//2
	public int getMemberId() {
		return memberId;
	}
	public void setMemberId(int memberId) {
		this.memberId = memberId;
	}

	public Equipment getEquipment() {
		return equipment;
	}
	public void setEquipment(Equipment equipment) {
		this.equipment = equipment;
	}
	
	public Status getStatus() {
        return status;
    }
    public void setStatus(Status status) {
        this.status = status;
    }
	
	//3
	@Override
	public String toString() 
	{
		return getId()+"\t"+getName()+"\t"+getAge()+"\t"+getSalary()+"\t"+"≥Ã–Ú‘±"+"\t"+"FREE"+"\t"+equipment.getDescription();
	}	
}
