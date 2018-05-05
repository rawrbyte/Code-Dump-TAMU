// CSCE 314 Homework Assignment  #6 // 304-501 // Raymond Zhu // 923008555 // Help from Welsey Ng
import java.util.*;
import java.util.ArrayList;
import java.lang.*;
import java.lang.Class;
import java.lang.reflect.*;

public class Main3{
	public static class A{
  		void foo(long T1, String T2){ }
  		int bar(double T1, int T2, float T3){ return 0; }
		static double doo(){ return 0; }
	}
	
	static void displayMethodInfo(Object obj){
		Class cl = obj.getClass();	
		Method methods[] = cl.getDeclaredMethods();
        boolean isStatic;
        boolean first = true;
        
        for(Method method : methods){
			System.out.print(method.getName() + "(");
            Type[] types = method.getGenericParameterTypes();
            isStatic = Modifier.isStatic(method.getModifiers());
			if(!isStatic){
                System.out.print(method.getDeclaringClass().getSimpleName());
            }
			int counter = 1;
            for(Type type : types){
                if(isStatic && first){
                    System.out.print(type.toString());
                    first = false;
                }else{
				    System.out.print(", " + "T" + counter /* type.toString() */ );
					counter++;
                }
			}

			System.out.print(") -> " + method.getGenericReturnType().toString());
			System.out.println();
		}
	}

    public static void main(String args[]){
		A nope = new A();
		displayMethodInfo(nope);
	}
}