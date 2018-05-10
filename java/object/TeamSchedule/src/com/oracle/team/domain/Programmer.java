package com.oracle.team.domain;

import com.oracle.team.service.Status;

public class Programmer extends Employee {
	
	private int memberId;
	private Status status;
	private Equipment equipment;
	
	public int getMemberId() {
		return memberId;
	}
	public void setMemberId(int memberId) {
		this.memberId = memberId;
	}

	public Status getStatus() {
		return status;
	}
	public void setStatus(Status status) {
		this.status = status;
	}

	public Equipment getEquipment() {
		return equipment;
	}
	public void setEquipment(Equipment equipment) {
		this.equipment = equipment;
	}

	public Programmer() {}
	public Programmer(int id, String name, int age, double salary, Equipment equipment) {
		super(id, name, age, salary);
		this.setEquipment(equipment);
	}

	@Override
	public String toString() {
		return super.toString() + "\t" + "≥Ã–Ú‘±" + "\t" + status + "\t\t\t" + equipment.getDescription();
	}

}
