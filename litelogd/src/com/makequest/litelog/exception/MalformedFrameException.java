package com.makequest.litelog.exception;


public class MalformedFrameException extends Exception {
	
	private int mErrorCode = ErrorCode.EC_SYSTEM_ERROR;

	/**
	 * 
	 */
	private static final long serialVersionUID = 4893964565395819488L;

	public MalformedFrameException(int eCode){
		mErrorCode = eCode;
	}
	
	public String getReason(){
		return ErrorCode.getStrError(mErrorCode);
	}
}
