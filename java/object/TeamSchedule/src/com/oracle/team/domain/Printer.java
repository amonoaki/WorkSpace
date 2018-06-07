package com.oracle.team.domain;

public class Printer implements Equipment {

	private String type;
	private String name;
	
	public Printer(String type, String name) {
		// TODO Auto-generated constructor stub
		this.name = name;
		this.type = type;
	}
	
	@Override
	public String getDescription() {
		// TODO Auto-generated method stub
		return type + "(" + name + ")";
	}

}
