import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.concurrent.*;

public class GraphColoringFuture {
    public static int[] colorGraphWorker(int workerId, GraphStructure graph, int currentNode, int[] initialSolution) throws InterruptedException, ExecutionException {
        int colorCount = ColorManager.getColorCount();
        return colorGraphRecursive(workerId, graph, currentNode, initialSolution, colorCount);
    }

    private static int[] colorGraphRecursive(int workerId, GraphStructure graph, int currentNode, int[] solution, int colorCount) throws InterruptedException, ExecutionException {
        int nodeCount = graph.getNodeCount();

        // Check if the current solution is invalid
        if (!isSolutionValid(currentNode, solution, graph)) {
            return createInvalidSolution(nodeCount);
        }

        // If the solution is valid and complete, return it
        if (currentNode + 1 == nodeCount) {
            return solution;
        }

        // Identify the next node to color
        int nextNode = currentNode + 1;

        List<Callable<int[]>> tasks = new ArrayList<>();

        // Create tasks for all colors except the current worker's color
        for (int color = 1; color <= colorCount; color++) {
            if (color != workerId) {
                int[] tempSolution = Arrays.copyOf(solution, solution.length);
                tempSolution[nextNode] = color;

                int finalColor = color;
                tasks.add(() -> colorGraphRecursive(finalColor, graph, nextNode, tempSolution, colorCount));
            } else {
                // Process the current worker's color
                int[] tempSolution = Arrays.copyOf(solution, solution.length);
                tempSolution[nextNode] = workerId;

                int[] result = colorGraphRecursive(workerId, graph, nextNode, tempSolution, colorCount);
                if (result[0] != -1) {
                    return result;
                }
            }
        }

        // Execute tasks using a thread pool
        ExecutorService executor = Executors.newFixedThreadPool(colorCount - 1);
        List<Future<int[]>> results = executor.invokeAll(tasks);

        for (Future<int[]> result : results) {
            int[] finalResult = result.get();
            if (finalResult[0] != -1) {
                return finalResult;
            }
        }

        executor.shutdown();
        return createInvalidSolution(nodeCount);
    }

    private static boolean isSolutionValid(int node, int[] solution, GraphStructure graph) {
        for (int i = 0; i < node; i++) {
            if (graph.edgeExists(node, i) && solution[node] == solution[i]) {
                return false;
            }
        }
        return true;
    }

    private static int[] createInvalidSolution(int size) {
        int[] invalidSolution = new int[size];
        Arrays.fill(invalidSolution, -1);
        return invalidSolution;
    }
}
