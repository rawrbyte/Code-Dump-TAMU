import java.util.Iterator;
import java.util.NoSuchElementException;


public class ShapeList<T extends Shape> implements Iterable<T>{
    Node<T> head = null;
    Node<T> current;
    
    public ShapeList(){
        head = null;
        current = head;
    }
    
    public ShapeList(Iterable<T> iterable){
        for(T e : iterable) add(e);
    }
    
    public Iterator<T> iterator(){
        return new ShapeListIterator<T>(head);
    }
    
    
    public void insert_first(T data){
        head = new Node<T>(data, head);
    }
    
    
    public ShapeList<T> reverse(){
        ShapeList<T> list = new ShapeList<T>();
        Node<T> temp = head;
        while(temp != null){
            list.insert_first(temp.v);
            temp = temp.next;
        }
        return list;
    }

     public void add(T data){
        Node<T> temp = new Node<T>(data,null);
        if(data != null){ 
            if(head != null){
                current = head;
                while(current.get_next() != null){ 
                    current = current.get_next(); 
                }
                current.set_next(temp);
            }else{
                head = temp;
            }
        }
    }



public String toString(){
         Iterator<T> iter = iterator();
         String shapeListStr = "[";
         while (iter.hasNext()){
             shapeListStr += "{" + iter.next().toString() + "}";
            if (iter.hasNext()) // checks for if next one is null
                shapeListStr += ",";
         }
         return shapeListStr+"]";
     }
    
   /* @Override
    public String toString(){
        String temp = "[ ";
        for(T e : this){
            temp = temp + e + " ";
        }
        temp = temp + "]";
        return temp;
    }*/
    
    class ShapeListIterator<T extends Shape> implements Iterator<T>{
        Node<T> next_node;

        public ShapeListIterator(Node<T> n){
           next_node = n; 
        }

        public boolean hasNext(){
            return next_node != null;
        }

        public T next(){
            if(!hasNext()) throw new NoSuchElementException();;
            T data = next_node.v;
            next_node = next_node.next;
            return data;
        }
    }
}