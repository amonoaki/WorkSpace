package com.oracle.team.domain;

public class Architect extends Designer {

	private int stock;
	
	public int getStock() {
		return stock;
	}
	public void setStock(int stock) {
		this.stock = stock;
	}
	
	public Architect(int id, String name, int age, double salary, Equipment equipment, double bouns, int stock) {
		super(id, name, age, salary, equipment, bouns);
		this.setStock(stock);
	}
	
	public String toString( ) {
		return getId() + "\t" + getName() + "\t" + getAge() + "\t" + getSalary() + "\t" + "¼Ü¹¹Ê¦" + "\t" + getStatus() + "\t" + getBouns() + "\t" + stock + "\t" + getEquipment().getDescription();
	}

}
