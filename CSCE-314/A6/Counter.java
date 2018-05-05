// CSCE 314 Homework Assignment  #6 // 304-501 // Raymond Zhu // 923008555 // Help from Welsey Ng
class Counter implements Runnable{
    private int num;
    private String msg;
    private Timer time;

    public Counter(int num, String msg, Timer timer){
        if(num <= 0) throw new IllegalArgumentException("num must be 1 or greater");
        this.num = num;
        this.msg = msg;
        time = timer;
    }

    @Override
    public void run(){
        while(true){
            time.lock.lock();
            try{
                do time.qq.await();
                while((time.elapsed + 1) % num != 0);
                System.out.println(msg);
            }catch(InterruptedException e){
                e.printStackTrace();
            }finally{
                time.lock.unlock();
            }
        }
    }
}