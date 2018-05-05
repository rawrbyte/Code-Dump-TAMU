public class Circle extends Shape{
	public Point center;
	public double radius;
	Double area;
	private static double pi = Math.PI; 
	
	public Circle (Point point, double r){
		center = point;
		radius = r;
		area = pi * Math.pow(radius, 2);
	}

	public Circle(double x, double y, double z){
		center = new Point (x,y);
		radius = z;
	}
	
	public double get_radius(){ return radius; }
	public Point get_point(){ return center; }
	public Point position(){ return center; }
	public double area(){ return area; }

	@Override
    public boolean equals(Object obj){
        if(obj == null) return false;
        if(this == obj) return true;
        if(!super.equals(obj)) return false;
        Circle shape;
        if(obj instanceof Circle){
            shape = (Circle) obj;
            if(this.position().equals(shape.position()) && this.congruent(shape)) return true;
        }
        return false;
    }

    public int hashCode(){
		int hash = 13;
		hash = 7 * hash + this.center.hashCode();
		hash = 7 * hash + this.area.hashCode();
		return hash;
	}

    public String toString(){
    	String cirStr = "";
    	cirStr += ("Circle " + "(" + center.get_x() + ", " + center.get_y() + "), radius = " + radius );
    	return cirStr;
    }

    public boolean congruent(Circle c){
        if(this.get_radius() == c.get_radius()) return true;
        return false;
    }

}
	