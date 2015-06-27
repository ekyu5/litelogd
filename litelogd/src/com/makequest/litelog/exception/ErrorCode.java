package com.makequest.litelog.exception;

public class ErrorCode {
	public final static int EC_OK = 0;
	
	public static final int EC_SYSTEM_ERROR = 1;
	public static final int EC_ERROR_UNKNOWN = 2;
	
	public static final int EC_MALFORMED_FRAME = 11;
	public static final int EC_DGRAM_TOO_SHORT = 12;
	public static final int EC_VERSION_NOT_SUPPORTED = 13;
	
	public static String getStrError(int code){
		switch (code){
		case EC_OK: 					return new String("OK");
		case EC_MALFORMED_FRAME :		return new String("Malformed Frame");
		}
		return new String("Unkown error.");
	}
}
