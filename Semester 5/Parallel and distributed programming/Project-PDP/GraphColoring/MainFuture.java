import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.*;

public class MainFuture {
    private static final int NODE_COUNT = 5;
    private static final int COLOR_COUNT = 3;

    public static void main(String[] args) throws InterruptedException, ExecutionException {
        final String[] colors = {"Red", "Green", "Blue"};

        GraphStructure graph = new GraphStructure(NODE_COUNT);
        graph.createEdge(0, 1);
        graph.createEdge(1, 2);
        graph.createEdge(1, 4);
        graph.createEdge(2, 0);
        graph.createEdge(2, 3);
        graph.createEdge(3, 1);
        graph.createEdge(3, 4);
        graph.createEdge(4, 0);

        ColorManager.initializeColorCount(COLOR_COUNT);
        for (int i = 1; i <= COLOR_COUNT; i++) {
            ColorManager.assignColorName(i, colors[i - 1]);
        }

        ExecutorService executor = Executors.newFixedThreadPool(COLOR_COUNT);
        List<Callable<int[]>> tasks = new ArrayList<>();

        for (int i = 1; i <= COLOR_COUNT; i++) {
            int[] initialSolution = new int[NODE_COUNT];
            initialSolution[0] = i;

            int finalColor = i;
            tasks.add(() -> GraphColoringFuture.colorGraphWorker(finalColor, graph, 0, initialSolution));
        }

        List<Future<int[]>> results = executor.invokeAll(tasks);

        for (Future<int[]> result : results) {
            int[] solution = result.get();
            System.out.println("Solution: " + ColorManager.mapNodesToColors(solution));
        }

        executor.shutdown();
    }
}
