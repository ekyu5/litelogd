package com.makequest.litelog.base;

import java.net.InetAddress;
import java.util.concurrent.LinkedBlockingQueue;

public abstract class LlogOutputAdaptor implements Runnable{
	
	private LinkedBlockingQueue<LlogUnit> mQueue = new LinkedBlockingQueue<LlogUnit>();
	private boolean isRun = true;
	private byte mLevelLog = HeadConstant.level.all;
	private byte mLevelTrace = HeadConstant.level.all;
	
	public LinkedBlockingQueue<LlogUnit> getQueueHandler(){
		return mQueue;
	}
	
	public void setLogLevel(byte level){
		mLevelLog = level;
	}
	
	public void setLogTrace(byte level){
		mLevelTrace = level;
	}
	
	@Override
	public void run() {
		while(isRun){
			try {
				LlogUnit log = mQueue.take();
				int level = log.level;
				if (log.useTrace && level > mLevelTrace){
					logTrace(log.getRemoteHost()
							,	log.getGroup()
							,	log.getHost()
							,	log.getName()
							,	log.getLog());
				}
				else if (level > mLevelLog){
					logNormal(log.getRemoteHost()
							,	log.getGroup()
							,	log.getHost()
							,	log.getName()
							,	log.getLog());
				}
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				isRun = false;
			}
		}
	}
	
	abstract public void logNormal(InetAddress from, String group, String host, String name, String log);
	abstract public void logTrace(InetAddress from, String group, String host, String name, String log);
}
