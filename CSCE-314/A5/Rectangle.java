public class Rectangle extends Shape{
	public Point a, b, c, d, center;
	public double length, width;
	Double area;

	public Rectangle(Point first, Point second){
		a = first;
		b = second;
		if (a.get_x() >= b.get_x()){
			if (a.get_y() >= b.get_y()){
				d = new Point (a.get_x(), a.get_y());
				c = new Point (b.get_x(), b.get_y());
			}
			if (a.get_y() < b.get_y()){
				d = new Point (a.get_x(), b.get_y());
				c = new Point (b.get_x(), a.get_y());
			}
		}
		else{
			if (a.get_y() >= b.get_y()){
				d = new Point (b.get_x(), a.get_y());
				c = new Point (a.get_x(), b.get_y());
			}
			if (a.get_y() < b.get_y()){
				d = new Point (b.get_x(), b.get_y());
				c = new Point (a.get_x(), a.get_y());
			}
		}
		length = Math.abs(a.get_x() - b.get_x());
		width = Math.abs(a.get_y() - b.get_y());
		Point position = new Point(a.get_x() - (length/2), a.get_y() - (width/2));
		center = position;
		area = this.area();
	}

	public Rectangle(double first, double second, double third, double fourth){
		a = new Point(first, second);
		b = new Point(third, fourth);
		if (a.get_x() >= b.get_x()){
			if (a.get_y() >= b.get_y()){
				d = new Point (a.get_x(), a.get_y());
				c = new Point (b.get_x(), b.get_y());
			}
			if (a.get_y() < b.get_y()){
				d = new Point (a.get_x(), b.get_y());
				c = new Point (b.get_x(), a.get_y());
			}
		}
		else{
			if (a.get_y() >= b.get_y()){
				d = new Point (b.get_x(), a.get_y());
				c = new Point (a.get_x(), b.get_y());
			}
			if (a.get_y() < b.get_y()){
				d = new Point (b.get_x(), b.get_y());
				c = new Point (a.get_x(), a.get_y());
			}
		}
		length = Math.abs(first-third);
		width = Math.abs(second - fourth);
		area = length*width;
		center = new Point((first - (length/2)), (second - (width/2)));
	}

	public double get_width(){ return width; }
	public double get_length(){ return length; }
	public Point position(){ return center; }
	public double area(){ return length*width; }
	public Point get_a(){ return a; }
	public Point get_b(){ return b; }

    @Override
    public boolean equals(Object obj){
        if(obj == null) return false;
        if(this == obj) return true;
        if(!super.equals(obj)) return false;
        Rectangle shape;
        if(obj instanceof Rectangle){
            shape = (Rectangle) obj;
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
    	cirStr += ("Rectangle " + "(" + c.get_x() + ", " + c.get_y() + ")-(" + d.get_x() + ", " + d.get_y() + ")");
    	return cirStr;
    }

    public boolean congruent(Rectangle r){
        if(this.get_length() == r.get_length() && this.get_width() == r.get_width()){
            return true;
        }else if(this.get_length() == r.get_width() && this.get_width() == r.get_length()){
            return true;
        }else{
            return false;
        }
    }
}