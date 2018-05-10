package com.oracle.team.domain;

public class PC implements Equipment {

	private String model;
	private String display;
	
	public PC(String model, String display) {
		this.display = display;
		this.model = model;
	}
	
	@Override
	public String getDescription() {
		// TODO Auto-generated method stub
		return model + "(" + display + ")";
	}

}
