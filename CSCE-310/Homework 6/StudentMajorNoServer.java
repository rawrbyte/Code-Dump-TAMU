package studentClient.simpledb;
import simpledb.tx.Transaction;
import simpledb.query.*;
import simpledb.server.SimpleDB;
import simpledb.file.*;

/* This is a version of the StudentMajor program that
 * accesses the SimpleDB classes directly (instead of
 * connecting to it as a JDBC client).  You can run it
 * without having the server also run.
 * 
 * These kind of programs are useful for debugging
 * your changes to the SimpleDB source code.
 */

// The difference between StudentMajorNoServer and StudentMajor programs is that StudentMajorNoServer
// accesses the database directory directly instead of requesting an inquiry to the local server which connects
// to the database. Without use of a server, StudentMajorNoServer would need to mimic the functionality of a server
// where transactions are needed to ensure requests are completed one at a time. 

public class StudentMajorNoServer {
	public static void main(String[] args) {
		try {
			// analogous to the driver
			SimpleDB.init("studentdb");
			
			FileMgr fm = SimpleDB.fileMgr();
			
			// analogous to the connection
			Transaction tx = new Transaction();
			
			// analogous to the statement
			String qry = "select SName, DName "
		        + "from DEPT, STUDENT "
		        + "where MajorId = DId";	
			Plan p = SimpleDB.planner().createQueryPlan(qry, tx);
			
			// analogous to the result set
			Scan s = p.open();
			
			System.out.println("Name\tMajor");
			while (s.next()) {
				String sname = s.getString("sname"); //SimpleDB stores field names
				String dname = s.getString("dname"); //in lower case
				System.out.println(sname + "\t" + dname);
			}
			s.close();
			tx.commit();
			
			System.out.println("Average block read: " + fm.readAverage() + " ns");
			System.out.println("Average block write: " + fm.writeAverage() + " ns");
			fm.resetAverages();
		}
		catch(Exception e) {
			e.printStackTrace();
		}
	}
}
