package com.makequest.litelog.base;

public class HeadConstant {
	public static final byte minLength = 5;
	
	public static class version{
		public static final byte v1 = 0x20;
	}
	public static class level{
		public static final byte debug = 0x02;
		public static final byte info = 0x03;
		public static final byte warn = 0x04;
		public static final byte min = 0x05;
		public static final byte maj = 0x06;
		public static final byte crit = 0x07;
		
		public static final byte trace = 0x08;
		
		/*
		 * For server internal use only
		 * not for protocol.
		 */
		public static final byte all = 0x00;
	}
	
}
