public class AreaCalculator {

	public static double calculate(Shape[] shapes){
		double area = 0;
		for (int i = 0; i<shapes.length; i++){
			area = area + shapes[i].area();
		}
		return area;
	}
}