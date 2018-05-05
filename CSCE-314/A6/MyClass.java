// CSCE 314 Homework Assignment  #6 // 304-501 // Raymond Zhu // 923008555 // Help from Welsey Ng
public class MyClass{
    public MyClass(){ System.out.println("MyClass created"); }
    public static boolean test1(){ System.out.println("method invoked: test1"); return true; }
    public static boolean test2(){ System.out.println("method invoked: test2"); return false; }
    public static boolean a1(){ System.out.println("method invoked: a1"); return true; }
    public static boolean a2(){ System.out.println("method invoked: a2"); return false; }
    static boolean test3(){ System.out.println("method invoked: test3"); return false; }
    public boolean test4(){ System.out.println("method invoked: test4"); return false; }
    public static boolean test5(int a){ System.out.println("method invoked: test5"); return true; }
    public static int test6(int a){ System.out.println("method invoked: test6"); return 0; }
    public static int test7(){ System.out.println("method invoked: test7"); return 0; }
    static void test8(){ System.out.println("method invoked: test8"); }
    public void test9(){ System.out.println("method invoked: test9"); }
}