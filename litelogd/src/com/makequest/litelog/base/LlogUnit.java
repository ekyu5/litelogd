package com.makequest.litelog.base;

import java.io.UnsupportedEncodingException;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.util.Arrays;

import com.makequest.litelog.exception.ErrorCode;
import com.makequest.litelog.exception.MalformedFrameException;
import com.makequest.litelog.exception.StringParseException;

public class LlogUnit {
	private byte[]	datagram = null;
	private byte 	version = 0;
	public byte 	level = 0;
	public boolean 	useTrace = false;
	
	public int 		seq = 0;
	
	/*
	 * log[0] : Group
	 * log[1] : Host
	 * log[2] : Name
	 */
	private String 	log[] = null;
	
	private InetSocketAddress remoteAddress = null;

	
	/**
	 * Constructor.
	 * Parse llog header only.
	 * 
	 * @param datagram : Received UDP datagram.
	 * @throws MalformedFrameException
	 */
	public LlogUnit(byte[] dgram, InetSocketAddress rhost) throws MalformedFrameException {
		datagram = dgram;
		remoteAddress = rhost;
		if (datagram.length < HeadConstant.minLength){
			throw new MalformedFrameException(ErrorCode.EC_DGRAM_TOO_SHORT);
		}
		
		version = (byte) (datagram[0] & 0xE0);
		if (version != HeadConstant.version.v1){
			throw new MalformedFrameException(ErrorCode.EC_VERSION_NOT_SUPPORTED);
		}
		
		level = datagram[1];
		
		if ((level & HeadConstant.level.trace)  == HeadConstant.level.trace){
			useTrace = true;
		}
		
		level &= ~HeadConstant.level.trace;
		
        seq = (((int)datagram[2]) << 8) & 0xFF00;
        seq |= ((int)datagram[3]) & 0xFF;
   	}	
	
	/**
	 * Parse received log data.
	 * Using this method, it can identify log group, name and sent host.
	 * 
	 * @throws StringParseException
	 */
	public void parseData() throws StringParseException{
        byte[] logBody = Arrays.copyOfRange(datagram, 2, datagram.length);
        String logLine = null;
        try {
			logLine = new String(logBody, "UTF-8");
		} catch (UnsupportedEncodingException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			throw new StringParseException("Log decode fail");
		}
        log = logLine.split("|", 4);
        if (log.length != 4){
        	throw new StringParseException("Can't parse log token.");
        }
	}
	
	public String getGroup(){
		return log[0];
	}
	
	public String getHost(){
		return log[1];
	}
	
	public String getName(){
		return log[2];
	}
	
	public String getLog(){
		return log[3];
	}
	
	public InetAddress getRemoteHost(){
		return remoteAddress.getAddress();
	}
}
