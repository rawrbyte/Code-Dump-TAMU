// CSCE 314 Homework Assignment  #6 // 304-501 // Raymond Zhu // 923008555 // Help from Welsey Ng
import java.util.*;
import java.util.LinkedList;
import java.lang.System;
import java.util.concurrent.locks.*;

class PostBox implements Runnable{
    private static final int MAX_SIZE = 10;
    private Lock msglock = new ReentrantLock();
    private static final int DELAY = 1000;
    
    class Message{
        String sender;
        String recipient;
        String msg;
        Message(String sender, String recipient, String msg) {
            this.sender = sender;
            this.recipient = recipient;
            this.msg = msg;
        }
        
        public String toString(){
            return "From " + sender + " to " + recipient + ": " + msg;
        }
    }
    
    private final LinkedList<Message> messages;
    private LinkedList<Message> myMessages;
    private String myId;
    private boolean stop = false;
    private int counter = 0;
    
    public PostBox(String myId){
        messages = new LinkedList<Message>();
        this.myId = myId;
        this.myMessages = new LinkedList<Message>();
        new Thread(this).start();
    }
    
    public PostBox(String myId, PostBox p){
        this.myId = myId;
        this.messages = p.messages;
        this.myMessages = new LinkedList<Message>();
        new Thread(this).start();
    }
    
    public String getId(){ return myId; }
    
    public void stop(){ 
        stop = true;
    }
    
    public synchronized void send(String recipient, String msg){ 
        synchronized(messages){
            messages.add(new Message(this.myId,recipient, msg));
        } //locked so that no other thread can edit values while this function is still editing values
        notifyAll();
    }
    
    public synchronized List<String> retrieve(){
        LinkedList<String> temp = new LinkedList<String>();
        synchronized(myMessages){
            if(myMessages.size() == 0) return temp;
            for(int i = 0; i < myMessages.size(); i++){
                temp.add(myMessages.get(i).toString());
            }
            myMessages.clear();
        } //locked so that no other thread can edit values while this function is still editing values
        notifyAll();
        
        return temp;
    }
    
    public synchronized void move(){
        synchronized(messages){
            LinkedList<Integer> temp = new LinkedList<Integer>();
            if(counter != 0) counter = 0;
            for(Message msg : messages){
                if(msg.recipient.equals(myId)){ 
                    myMessages.add(msg);
                    temp.add(counter);
                    counter++;
                }
            }

            for(int derp : temp) if (derp < messages.size()) messages.remove(derp);
        } //locked so that no other thread can edit values while this function is still editing values
        notifyAll();
    }
    
    public synchronized void overflow(){
        synchronized(messages){
            while(messages.size() > MAX_SIZE) messages.remove();
        } //locked so that no other thread can edit values while this function is still editing values
        notifyAll();
    }
    
    @Override
    public void run(){
        while(!stop){
            synchronized(messages){
            move();
            } //locked so that no other thread can move messages while the current thread is. separate from overflow() to prevent deadlock
            overflow();
            try{
                Thread.sleep(DELAY);
            }catch(InterruptedException e){}
        }
    }
}