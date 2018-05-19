package com.oracle.team.domain;

public class Designer extends Programmer {

	private double bouns;
	
	public double getBouns() {
		return bouns;
	}
	public void setBouns(double bouns) {
		this.bouns = bouns;
	}
	
	public Designer(int id, String name, int age, double salary, Equipment equipment, double bouns) {
		super(id, name, age, salary, equipment);
		this.setBouns(bouns);
	}

	public String toString() {
		return getId() + "\t" + getName() + "\t" + getAge() + "\t" + getSalary() + "\t" + "…Ëº∆ ¶" + "\t" + getStatus() + "\t" + bouns + "\t\t" + getEquipment().getDescription();
	}
}
