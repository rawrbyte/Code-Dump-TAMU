public class Triangle extends Shape{
	public Point a, b, c, middle;
	public double ab, ac, bc, p;
	Double area;
	
	public Triangle(Point one, Point two, Point three){
		a = one;
		b = two;
		c = three;
		ab = a.distance(b);
		ac = a.distance(c);
		bc = b.distance(c);
		p = (ab+ac+bc)/2;
		area = Math.sqrt((p*(p-ab)*(p-ac)*(p-bc)));
		Point center = new Point((a.get_x() + b.get_x() + c.get_x())/3, (a.get_y() + b.get_y() + c.get_y())/3);
		middle = center;
	}

	public Triangle (double first, double second, double third, double fourth, double fifth, double sixth){
		a = new Point(first, second);
		b = new Point(third, fourth);
		c = new Point(fifth, sixth);
		double ax = first*(fourth - sixth);
		double bx = third*(sixth - second);
		double cx = fifth*(second-fourth);
		area = Math.abs(ax+bx+cx)/2;
		middle = new Point(((first + third + fifth)/3),((second+fourth+fifth)/3));
	}

	public double get_ab(){ return ab; }
	public double get_ac(){ return ac; }
	public double get_bc(){ return bc; }
	public Point position(){ return middle; }
	public double area(){ return area; }

    @Override
    public boolean equals(Object obj){
        if(obj == null) return false;
        if(this == obj) return true;
        if(!super.equals(obj)) return false;
        Triangle shape;
        if(obj instanceof Triangle){
            shape = (Triangle) obj;
            if(this.position().equals(shape.position()) && this.congruent(shape)) return true;
        }
        return false;
    }

    public int hashCode(){
		int hash = 13;
		hash = 7 * hash + this.middle.hashCode();
		hash = 7 * hash + this.area.hashCode();
		return hash;
	}

    public String toString(){
    	String cirStr = "";
    	cirStr += ("Triangle " +  "(" + a.get_x() + ", " + a.get_y() + ")-(" + b.get_x() + ", " + b.get_y() + ")-(" + c.get_x() + ", " + c.get_y() + ")");
    	return cirStr;
    }

    public boolean congruent(Triangle t){
        if(this.get_ab() == t.get_ab() && this.get_bc() == t.get_bc() && this.get_ac() == t.get_ac()){
            return true;
        }else if(this.get_ab() == t.get_bc() && this.get_bc() == t.get_ac() && this.get_ac() == t.get_ab()){
            return true;
        }else if(this.get_ab() == t.get_ac() && this.get_bc() == t.get_ab() && this.get_ac() == t.get_bc()){
            return true;
        }else{
            return false;
        }
    }

}

/*
public class Triangle extends Shape{
	public Point a,b,c, positionone, positiontwo, positionthree;
	public double ax, bx, cx;
	Double area;

	public Triangle (Point first, Point second, Point third){
		a = first;
		b = second;
		c = third;
		positionone = a;
		positiontwo = b;
		positionthree = c;
		ax = a.get_x()*(b.get_y() - c.get_y());
        bx = b.get_x()*(c.get_y() - a.get_y());
        cx = c.get_x()*(a.get_y() - b.get_y());
        area = Math.abs(ax+bx+cx)/2;
	}

	public double area(){
        return area;
	}

	public double get_ab() {
		return ax;
	}

	public double get_ac() {
		return cx;
	}

	public double get_bc() {
		return bx;
	}

	public Point position(){
		return positionone;
	}

    @Override
    public boolean equals(Object obj){
        if(obj == null) return false;
        if(this == obj) return true;
        if(!super.equals(obj)) return false;
        Triangle shape;
        if(obj instanceof Triangle){
            shape = (Triangle) obj;
            if(this.position().equals(shape.position()) && this.congruent(shape)) return true;
        }
        return false;
    }	

     public int hashCode(){
		int hash = 13;
		hash = 7 * hash + this.positionone.hashCode();
		hash = 7 * hash + this.area.hashCode();
		return hash;
	}

	public String toString(){
        return String.format("Triangle %s %.2f", position().toString(), this.area());
    }

    public boolean congruent(Triangle t){
        if(this.get_ab() == t.get_ab() && this.get_bc() == t.get_bc() && this.get_ac() == t.get_ac()){
            return true;
        }else if(this.get_ab() == t.get_bc() && this.get_bc() == t.get_ac() && this.get_ac() == t.get_ab()){
            return true;
        }else if(this.get_ab() == t.get_ac() && this.get_bc() == t.get_ab() && this.get_ac() == t.get_bc()){
            return true;
        }else{
            return false;
        }
    }

}
*/