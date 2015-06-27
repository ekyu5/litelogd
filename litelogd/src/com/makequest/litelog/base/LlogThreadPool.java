package com.makequest.litelog.base;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.ArrayList;
import java.util.List;

public class LlogThreadPool {
	private static List<LlogOutputAdaptor> tList = new ArrayList<LlogOutputAdaptor>();
	
	public static void addWorker(LlogOutputAdaptor loa){
		tList.add(loa);
	}
	
	public static void startWorker(){
		for(LlogOutputAdaptor loa : tList){
			Thread t = new Thread(loa);
			t.start();
		}
	}
	
	public static void allocWorker(LlogUnit unit){
		int inst = getSequence(unit);
		if (inst < 0){
			// fail
		}
		tList.get(inst).getQueueHandler().add(unit);
	}

	private static int getSequence(LlogUnit unit){
		if (tList.size() <= 0)	return -1;
		
		MessageDigest md = null;
		byte[] hashOutput = null;
		int valueOut = 0;

		try {
			md = MessageDigest.getInstance("MD5");
			md.update(unit.getGroup().getBytes()); 
			md.update(unit.getHost().getBytes());
			md.update(unit.getName().getBytes());
			hashOutput = md.digest();
		} catch (NoSuchAlgorithmException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return -1;
		} 

		valueOut = (((int)hashOutput[0]) << 24) & 0xFF000000;
		valueOut |= (((int)hashOutput[1]) << 16) & 0x00FF0000;
		valueOut |= (((int)hashOutput[2]) << 8) & 0x0000FF00;
		valueOut |= ((int)hashOutput[3]) & 0x000000FF;

		return valueOut%tList.size();
	}
}