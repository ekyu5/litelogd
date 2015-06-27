package com.makequest.litelog.exception;

public class StringParseException extends Exception {

	private String error = null;
	/**
	 * 
	 */
	private static final long serialVersionUID = -4211944142089909898L;

	public StringParseException(String r){
		error = r;
	}
	
	public String getReason(){
		return error;
	}
}
