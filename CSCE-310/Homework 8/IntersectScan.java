package simpledb.query;

public class IntersectScan implements Scan {
	private Scan s1, s2, s;

	public IntersectScan(Scan scan1, Scan scan2) {
		s1 = scan1;
		s2 = scan2;
		beforeFirst();
	}

	public void beforeFirst() {
		s1.beforeFirst();
		s = s1;
	}

	public boolean next() {
		if (s.next())
			return true;
		if (s != s2)
			return false;
		
		s = s2;
		s2.beforeFirst();
		
		return s2.next();
	}

	public void close() {
		s1.close();
		s2.close();
	}

	public Constant getVal(String fldname) {
		return s.getVal(fldname);
	}
	
	public int getInt(String fldname) {
		return s.getInt(fldname);
	}
	
	public String getString(String fldname) {
		return s.getString(fldname);
	}

	public boolean hasField(String fldname) {
		return s.hasField(fldname);
	}
}
