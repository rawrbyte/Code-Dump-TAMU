import java.util.*;
import java.util.Iterator;

public final class NodeIterator<T extends Shape> implements Iterator<T>{
	public Node<T> next_node; 

	public NodeIterator(Node<T> n){
		next_node = n;
	}

	public boolean hasNext(){
		return next_node != null;
	}

	public T next(){
		if(!hasNext()) throw new NoSuchElementException();
		T data = next_node.v;
		next_node = next_node.get_next();
		return data;
	}
}