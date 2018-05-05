import java.io.File;
import java.util.ArrayList;

public class Point implements Comparable<Point>{
	private static final Point ORIGIN = new Point(0,0);
	public double x, y;
	public Point(double pos1, double pos2){
		x = pos1;
		y = pos2;
	}
	
	public double get_x() { return x; }
	public double get_y() { return y; }
	
	public void clear(){
		x = 0.0;
		y = 0.0;
	}
	
	public double distance (Point that){
		double xdiff = x - that.x;
		double ydiff = y - that.y;
		return Math.sqrt(xdiff * xdiff + ydiff * ydiff);
	}
	
	public void move(double x, double y){
			this.x = x;
			this.y = y;
	}
	
	public int compareTo(Point p){
		double pDist = p.distance(ORIGIN);
		double dist = this.distance(ORIGIN);
		if (dist > pDist)
			return 1;
		else if (dist == pDist)
			return 0;
		else
			return -1;
	}	
}