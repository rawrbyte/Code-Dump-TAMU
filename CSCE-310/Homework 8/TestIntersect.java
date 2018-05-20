package simpledb.query;

import simpledb.tx.Transaction;
import simpledb.record.TableInfo;
import simpledb.server.SimpleDB;
import simpledb.metadata.MetadataMgr;

public class TestIntersect {
	public static void main(String[] args) {
		SimpleDB.init("studentdb");
		Transaction tx = new Transaction();
		MetadataMgr mdMgr = SimpleDB.mdMgr();
		
		System.out.println("Testing Intersect Scan ... ");
		
		TableInfo ti = mdMgr.getTableInfo("course", tx);
		Scan s1 = new TableScan(ti, tx);
		Scan s2 = new TableScan(ti, tx);
		Scan ss = new IntersectScan(s1, s2);
		
		ss.beforeFirst();
		while(ss.next()){
			int CId = ss.getInt("cid");
			String Title = ss.getString("title");
			int DeptId = ss.getInt("deptid");
			System.out.println(CId + " " + Title + " " + DeptId);
		}
		
		System.out.println("");	
		System.out.println("Testing Intersect Plan ... ");
		
		Plan p1 = new TablePlan("course", tx);
		Plan p2 = new TablePlan("course", tx);
		Plan p3 = new IntersectPlan(p1, p2);
		Scan pp = p3.open();
		
		pp.beforeFirst();
		while(pp.next()){
			int CId = pp.getInt("cid");
			String Title = pp.getString("title");
			int DeptId = pp.getInt("deptid");
			System.out.println(CId + " " + Title + " " + DeptId);
		}
		
		ss.close();
		pp.close();
		tx.commit();
	}
}
