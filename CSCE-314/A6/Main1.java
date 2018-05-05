// CSCE 314 Homework Assignment  #6 // 304-501 // Raymond Zhu // 923008555 // Help from Welsey Ng
public class Main1 {

    static void pause(long n) {
        try { Thread.sleep(n); } catch (InterruptedException e) {}
    }

    public static void main (String[] args) {
        final String bond    = "Bond";
        final String blofeld = "Blofeld";
        final String osato   = "Mr. Osato";

        final PostBox pBond    = new PostBox(bond);
        final PostBox pBlofeld = new PostBox(blofeld, pBond);
        final PostBox pOsato   = new PostBox(osato, pBond);

        // send out some messages on another thread
        new Thread( new Runnable() {
                public void run() {
                pBond.send(blofeld, "Yes, this is my second life"); pause(1000);
                pBlofeld.send(bond, "You only live twice, Mr. Bond."); pause(500);
                String msg = "I gave Number 11 the strictest orders to eliminate him.";
                pOsato.send(blofeld, msg); pause(2000);
                pOsato.send(bond, msg);
                for (int i=0; i<20; ++i) pOsato.send(bond, "flooding the message queue...");
                }
                }).start();

        PostBox[] boxes = { pBond, pBlofeld, pOsato };
        long startTime = System.currentTimeMillis();
        // poll for messages in a loop for 5 secs
        while (true) {
            for (PostBox box : boxes) {
                for (String m : box.retrieve()) System.out.println(m);
            }
            if (System.currentTimeMillis() - startTime > 5000) break;
        }
        // stop each mailbox
        for (PostBox box : boxes) {
            box.stop();
        }
    } // end of main()

} // end of Main1