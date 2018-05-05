import java.util.*;
import java.util.Iterator;

public final class Node<T extends Shape> implements Iterable<T>{
	public final T v;
	public Node<T> next;
	public Node(T d){ v = d; this.next = null; }
	public Node (T val, Node<T> link) { v = val; next = link; }
	public void set_next(Node<T> link) { next = link ;}
	public Node<T> get_next(){ return next; }
    public Iterator<T> iterator(){ return new NodeIterator<T>(this); }
}