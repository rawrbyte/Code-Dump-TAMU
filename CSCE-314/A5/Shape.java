import java.util.*;
import java.io.*;

abstract public class Shape implements Comparable{
    abstract public double area();
    abstract public Point position();

    @Override
    public boolean equals(Object obj){
        if(obj instanceof Shape) return true;
        return false;
    }
         
    @Override
	abstract public int hashCode();

    @Override
    abstract public String toString();
    
    @Override
    public int compareTo(Object obj){
        if(obj instanceof Shape){
            Shape shape = (Shape) obj;
            if(this.area() > shape.area()) return 1;
            else if(this.area() == shape.area()) return 0;
            else return -1;
        }else{
            return 9999999;
        }
    }
   
}