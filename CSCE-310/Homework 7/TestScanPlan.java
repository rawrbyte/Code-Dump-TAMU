package simpledb.query;

import simpledb.tx.Transaction;
import simpledb.server.SimpleDB;

import java.util.Arrays;
import java.util.Collection;

import simpledb.metadata.MetadataMgr;

public class TestScanPlan {
	public static void main(String[] args) {
			SimpleDB.init("studentdb");
			Transaction tx = new Transaction();
			MetadataMgr mdMgr = SimpleDB.mdMgr();
			
			Plan pstudent = new TablePlan("student", tx);
			Plan pdept = new TablePlan("dept", tx);
			Plan penroll = new TablePlan("enroll", tx);
			Plan psection = new TablePlan("section", tx);
			
			ProductPlan psd = new ProductPlan(pstudent, pdept);
			ProductPlan psde = new ProductPlan(psd, penroll);
			ProductPlan psdes = new ProductPlan(psde, psection);
			
			Expression lhs1 = new FieldNameExpression("sid");
			Expression rhs1 = new FieldNameExpression("studentid");
			Term t1 = new Term(lhs1, rhs1);
			
			Expression lhs2 = new FieldNameExpression("sectid");
			Expression rhs2 = new FieldNameExpression("sectionid");
			Term t2 = new Term(lhs2, rhs2);
			
			Expression lhs3 = new FieldNameExpression("did");
			Expression rhs3 = new FieldNameExpression("majorid");
			Term t3 = new Term(lhs3, rhs3);
			
			Predicate pred1 = new Predicate(t1);
			Predicate pred2 = new Predicate(t2);
			Predicate pred3 = new Predicate(t3);
			
			System.out.println("Testing Plan ... ");
			
			Predicate pred = pred1;
			pred.conjoinWith(pred2);
			pred.conjoinWith(pred3);
			
			Plan p1 = new SelectPlan(psdes, pred);
			Collection<String> c = Arrays.asList("sname", "dname", "grade" );
			Plan p2 = new ProjectPlan(p1, c);
			Scan s = p2.open();
			s.beforeFirst();
			while(s.next()) {
				String sname = s.getString("sname");
				String dname = s.getString("dname");
				String grade = s.getString("grade");
				System.out.println(sname + "\t" + dname + "\t" + grade);
			}
			
			s.close();
			tx.commit();
	}
}