package simpledb.metadata;

import simpledb.record.*;
import simpledb.server.SimpleDB;
import simpledb.tx.Transaction;

public class TestMetaDataMgr {
	public static void main(String[] args) {
			SimpleDB.init("studentdb");
			Transaction tx = new Transaction();
			MetadataMgr mdMgr = SimpleDB.mdMgr();
			
			TableInfo ti = mdMgr.getTableInfo("student", tx);
			Schema sch = ti.schema();
			
			System.out.println("Student Table before: " + sch.fields());
			
			sch.addIntField("test");
			
			if(mdMgr.alterTable("student", sch, tx))
				System.out.println("Table column added");
			
			ti = mdMgr.getTableInfo("student", tx);
			sch = ti.schema();
			
			System.out.println("Student Table after: " + sch.fields());
			
	}
}