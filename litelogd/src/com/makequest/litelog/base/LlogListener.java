package com.makequest.litelog.base;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.DatagramChannel;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.util.Iterator;

import com.makequest.litelog.exception.MalformedFrameException;

public class LlogListener {
	private static boolean isRun = true;
	private static ByteBuffer mRecvBuff = ByteBuffer.allocate(1024*4);
	
	public static void startListener(int port){
		try {
			Selector selector = Selector.open();
			DatagramChannel channel = DatagramChannel.open();
			channel.socket().bind(new InetSocketAddress(port));
			channel.configureBlocking(false);
			channel.register(selector, SelectionKey.OP_READ);

			while (isRun) {
				try {
					selector.select();
					Iterator<SelectionKey> selectedKeys = selector.selectedKeys().iterator();
					while (selectedKeys.hasNext()) {
						SelectionKey key = (SelectionKey) selectedKeys.next();
						selectedKeys.remove();

						if (!key.isValid())	continue;

						if (key.isReadable()) {
							receiveEvent(key);
						}
					}
				} catch (IOException e) {
					e.printStackTrace();
					isRun = false;
				}
			} // while()
		} catch (IOException e){
			e.printStackTrace();
		}
	}

	private static void receiveEvent(SelectionKey key){
		DatagramChannel channel = (DatagramChannel)key.channel();
		InetSocketAddress remote = null;
		LlogUnit unit = null;
		try {
			remote = (InetSocketAddress) channel.receive(mRecvBuff);
			try {
				unit = new LlogUnit(mRecvBuff.array(), remote);
			} catch (MalformedFrameException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				return;
			}
			LlogThreadPool.allocWorker(unit);
			
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
