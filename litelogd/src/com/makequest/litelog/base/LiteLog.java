package com.makequest.litelog.base;

import com.makequest.litelog.output.stdout.StdoutOutputLog;

public class LiteLog {
	public static void main (String args[]){
		LlogThreadPool.addWorker(new StdoutOutputLog());
		LlogThreadPool.addWorker(new StdoutOutputLog());
		LlogThreadPool.addWorker(new StdoutOutputLog());
		LlogThreadPool.addWorker(new StdoutOutputLog());
		LlogThreadPool.addWorker(new StdoutOutputLog());
		LlogThreadPool.addWorker(new StdoutOutputLog());
		LlogThreadPool.addWorker(new StdoutOutputLog());
		LlogThreadPool.addWorker(new StdoutOutputLog());
		LlogThreadPool.addWorker(new StdoutOutputLog());
		LlogThreadPool.startWorker();
		LlogListener.startListener(9000);
	}
}
