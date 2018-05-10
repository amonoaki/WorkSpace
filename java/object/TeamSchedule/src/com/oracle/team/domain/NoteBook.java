package com.oracle.team.domain;

public class NoteBook implements Equipment {

	private String model;
	private double price;

	public NoteBook(String model, double price) {
		// TODO Auto-generated constructor stub
		this.model = model;
		this.price = price;
	}
	
	@Override
	public String getDescription() {
		// TODO Auto-generated method stub
		return model + "(" + price + ")";
	}

}
