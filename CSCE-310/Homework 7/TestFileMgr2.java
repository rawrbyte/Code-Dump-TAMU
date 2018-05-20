package simpledb.file;

import java.util.Random;
import java.util.concurrent.ThreadLocalRandom;

import simpledb.server.SimpleDB;

public class TestFileMgr2 {
    public static void main(String args[]) throws Exception {
    	System.out.println("Start of TestFileMgr");
		SimpleDB.init("simpledbfiletest");//args[0]	test database name given directly instead of thru an argument
		String homedir = System.getProperty("user.home");
		System.out.println("home directory = "+homedir);
		FileMgr fm = SimpleDB.fileMgr();
		
		//fill a page with string values of the sequence of integers 0, 1, 2, ....
		Page pS = new Page();
		int offset = 0;
		int i = 0;
		while (offset + Page.INT_SIZE+Integer.toString(i).length()< Page.BLOCK_SIZE){
			pS.setString(offset, Integer.toString(i));
			offset += Page.INT_SIZE+Integer.toString(i).length();
			++i;
		}
		Block bS = new Block("junkfile", 1);//filename "junkfile", block num 1
		pS.write(bS);//write the page to the designated block
		
		//fill a page with a sequence of ints which are multiples of INT_SIZE
		Page pI = new Page();
		for (i = 0; i*Page.INT_SIZE < Page.BLOCK_SIZE; ++i){
			pI.setInt(i*Page.INT_SIZE, i);
		}
		Block bI = new Block("junkfile", 2);
		pI.write(bI);
		
		int filesize = fm.size("junkfile"); //filesize should be 3
		assert filesize == 3;
		Block blk = new Block("junkfile", filesize-1);
		
		//increment a designated integer
		Page p1 = new Page();
		p1.read(blk);
		int n = p1.getInt(32);//read the int at offset 32
		p1.setInt(32, n+1);//add one to the int and rewrite it to the same offset
		p1.write(blk);
		
		//write a string to a designated location
		Page p2 = new Page();
		p2.setString(20, "hello");//write the string to the designated offset
		blk = p2.append("junkfile");//append the page to the file named junkfile
		Page p3 = new Page();
		p3.read(blk);
		String s = p3.getString(20);
		System.out.println("Block " + blk.number() + " contains " + s);
		
		Page p4 = new Page();
		p4.setBoolean(40, "true");
		blk = p4.append("junkfile");
		
		Page p5 = new Page();
		p5.read(blk);
		String ss = p5.getBoolean(40);
		System.out.println("Block " + blk.number() + " contains boolean value " + ss);
		
		Page p6 = new Page();
		p6.setBoolean(50, "false");
		blk = p6.append("junkfile");
		
		Page p7 = new Page();
		p7.read(blk);
		ss = p7.getBoolean(50);
		System.out.println("Block " + blk.number() + " contains boolean value " + ss);
		
		Page p8 = new Page();
		p8.setBoolean(60, "null");
		blk = p8.append("junkfile");
		
		Page p9 = new Page();
		p9.read(blk);
		ss = p9.getBoolean(60);
		System.out.println("Block " + blk.number() + " contains boolean value " + ss);
		
		System.out.println("end of TestFileMgr");
    }
}
