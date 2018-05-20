package simpledb.query;

import simpledb.record.Schema;

public class IntersectPlan implements Plan {
	private Plan p1, p2;

	public IntersectPlan(Plan p1, Plan p2) {
		this.p1 = p1;
		this.p2 = p2;
	}

	public Scan open() {
		Scan s1 = p1.open();
		Scan s2 = p2.open();
		return new IntersectScan(s1, s2);
	}

	public int blocksAccessed() {
		return p1.blocksAccessed() + p2.blocksAccessed();
	}

	public int recordsOutput() {
		return p1.recordsOutput() + p2.recordsOutput();
	}

	public int distinctValues(String fldname) {
		return p1.distinctValues(fldname) + p2.distinctValues(fldname);
	}

	public Schema schema() {
		return p1.schema();
	}
}
