// CSCE 314 Homework Assignment  #6 // 304-501 // Raymond Zhu // 923008555 // Help from Welsey Ng
public class Main2{
    public static void main(String[] args){
        Timer time = new Timer();  
        Counter fifteen = new Counter(15,"\n15 second message",time); 
        Counter seven = new Counter(7,"\n7 second message",time); 

        new Thread(time).start();
        new Thread(seven).start();
        new Thread(fifteen).start(); 
    }
}