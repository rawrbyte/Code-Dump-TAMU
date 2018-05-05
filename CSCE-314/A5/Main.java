// CSCE 314 Homework Assignment  #5 // 304-501 // Raymond Zhu // 923008555 // Help from Welsey Ng
import java.io.File;
import java.util.Arrays;
import java.util.ArrayList;
import java.util.HashMap;

public class Main {
	public static Shape maxArea(Node<Shape> list){
		for (Shape e : list) {
			if (list.get_next() == null) { break; }
			if (e.area() > list.get_next().v.area()) {
				if ((list.get_next()).get_next() == null){ break; } 
				list.set_next((list.get_next()).get_next());
				continue; 
			}
			else { 
				if ((list.get_next()).get_next() == null){
					list = list.get_next();
					break;
				} 
				list = list.get_next();
				continue; 
			}
		}
		return list.v;
	}
	public static Rectangle boundingRect(Node<Rectangle> list){
		double gx = list.v.get_b().get_x(), lx = list.v.get_a().get_x(), gy = list.v.get_a().get_y(), ly = list.v.get_b().get_y();
		for (Rectangle e : list){
			if(list.get_next() == null) { break; }
			if(lx >= list.get_next().v.get_a().get_x()){ lx = list.get_next().v.get_a().get_x(); }
			if(gy <= list.get_next().v.get_a().get_y()){ gy = list.get_next().v.get_a().get_y(); }
			if(gx <= list.get_next().v.get_b().get_x()){ gx = list.get_next().v.get_b().get_x(); }
			if(ly >= list.get_next().v.get_b().get_y()){ ly = list.get_next().v.get_b().get_y(); }
			if ((list.get_next()).get_next() == null ) { break; }
			else{ list = list.get_next(); continue; } 
		}
		Point pos1 = new Point(lx, gy);
		Point pos2 = new Point(gx, ly);
		Rectangle bounding = new Rectangle(pos1, pos2);
		return bounding;
	}

	public static void main(String[] args){
		Shape shape[] = new Shape[args.length];
		Point origin = new Point(0.0, 0.0);
		Rectangle temprec = new Rectangle(origin, origin);
		Rectangle original = new Rectangle(origin, origin);
		Shape tempshape = new Triangle(origin, origin, origin);
		int counter = 0;
		for( int i = 0 ; i < args.length; i++){
			String[] manipArgs = args[i].split(" ");
			if (manipArgs[0].equals("c")){
				Point trial = new Point(Double.parseDouble(manipArgs[1]), Double.parseDouble(manipArgs[2]));
				double radiusnum = Double.parseDouble(manipArgs[3]);
				Shape newshape = new Circle(trial,radiusnum);
				Node<Shape> areing = new Node<Shape>(newshape, null);
				Node<Shape> ared = new Node<Shape>(tempshape, areing);
				tempshape = maxArea(ared);
				shape[i] = newshape;
			}
			else if (manipArgs[0].equals("r")){ 
				Point trialone = new Point(Double.parseDouble(manipArgs[1]), Double.parseDouble(manipArgs[2]));
				Point trialtwo = new Point(Double.parseDouble(manipArgs[3]), Double.parseDouble(manipArgs[4]));
				Shape newshape = new Rectangle(trialone, trialtwo);
				Rectangle rect = new Rectangle(trialone, trialtwo);
				Rectangle rect1 = new Rectangle(temprec.get_a(), temprec.get_b());
				if (counter == 0){ rect1 = rect;}
				Node<Rectangle> bound = new Node<Rectangle>(rect, null);
				Node<Rectangle> bounded = new Node<Rectangle>(rect1, bound);	
				Node<Shape> areing = new Node<Shape>(newshape, null);
				Node<Shape> ared = new Node<Shape>(tempshape, areing);			
				original = rect;
				temprec = boundingRect(bounded);
				tempshape = maxArea(ared);
				shape[i] = newshape;
				counter++;
			}
			else if (manipArgs[0].equals("t")){
				Point firstpt = new Point(Double.parseDouble(manipArgs[1]), Double.parseDouble(manipArgs[2]));
				Point secondpt = new Point(Double.parseDouble(manipArgs[3]), Double.parseDouble(manipArgs[4]));
				Point thirdpt = new Point(Double.parseDouble(manipArgs[5]), Double.parseDouble(manipArgs[6]));
				Shape newshape = new Triangle(firstpt,secondpt,thirdpt);
				Node<Shape> areing = new Node<Shape>(newshape, null);
				Node<Shape> ared = new Node<Shape>(tempshape, areing);
				tempshape = maxArea(ared);
				shape[i] = newshape;			
			}
		}

		Arrays.sort(shape);
        int count = 0;
        for (Shape s: shape){
            System.out.println(++count + ") "+s+"\t\t area="+s.area());
        }
       
        System.out.printf("The total area for the %d objects is %1.2f units squared.\n", shape.length, AreaCalculator.calculate(shape));
        System.out.printf("Largest area in linkedlist: " + tempshape + ", area: %.2f\n",  tempshape.area());
        if (counter > 1) { System.out.println(temprec + " encompasses all rectangles in linkedlist."); }
        if (counter <= 1 && counter > 0)  { System.out.println(original + " encompasses all rectangles in linkedlist."); }
		

		Circle c1 = new Circle(1,1,1);
        Circle d1 = new Circle(2,2,2);
        Circle e1 = new Circle(3,3,3);

        System.out.println(c1);

        ShapeList<Shape> emptyShapes = new ShapeList<Shape>();
        ShapeList<Circle> someCircles = new ShapeList<Circle>(Arrays.asList(c1, d1, e1));

        System.out.println("emptyShapes = " + emptyShapes);
        System.out.println("reversed emptyShapes = " + emptyShapes.reverse());
        System.out.println("someCircles = " + someCircles);
        System.out.println("reversed someCircles = " + someCircles.reverse());

        double sumOfXs = 0.0;
        double sumOfYs = 0.0;
        for (Circle c: someCircles) {
            sumOfXs += c.position().get_x();
            sumOfYs += c.position().get_y();
        }
        System.out.println("Some of Xs = " + sumOfXs);
        System.out.println("Some of Ys = " + sumOfYs);

	}
}
