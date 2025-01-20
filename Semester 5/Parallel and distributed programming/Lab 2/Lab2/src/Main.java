import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        ArrayList<Integer> vector1 = new ArrayList<>();
        ArrayList<Integer> vector2 = new ArrayList<>();
        for(int i=1;i<=100;i++)
        {
            vector1.add(1);
            vector2.add(i);
        }
        List<Thread> threads = new ArrayList<>();
        ProducerConsumerQueue<Integer> queue = new ProducerConsumerQueue<>();

        threads.add(new Thread(new Consumer(queue)));
        threads.add(new Thread(new Producer(queue, vector1, vector2)));
        long startTime = System.currentTimeMillis();
        for (Thread thread : threads)
            thread.start();
        for (Thread thread : threads)
            try {
                thread.join();
            } catch (Exception e) {
                e.printStackTrace();
            }
        long endTime = System.currentTimeMillis();
        System.out.println("Time: " + (endTime - startTime) + " milliseconds");
    }
}