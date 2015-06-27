package com.makequest.litelog.output.stdout;

import java.net.InetAddress;

import com.makequest.litelog.base.LlogOutputAdaptor;

public class StdoutOutputLog extends LlogOutputAdaptor{

	@Override
	public void logNormal(InetAddress from, String group, String host,
			String name, String log) {
		// TODO Auto-generated method stub
		System.out.println("LOG   : " + from.toString() + " " + group + " " + host +" " + name + " " + log);
	}

	@Override
	public void logTrace(InetAddress from, String group, String host,
			String name, String log) {
		// TODO Auto-generated method stub
		System.out.println("TRACE : " + from.toString() + " " + group + " " + host +" " + name + " " + log);

	}

}
