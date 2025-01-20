import mpi.*;

import java.util.Arrays;
import java.util.concurrent.ExecutionException;

public class Main {
    private static final int NODE_COUNT = 5;
    private static final int COLOR_COUNT = 3;
    private static final int EDGE_COUNT = 6;
    public static void main(String[] args) throws InterruptedException, ExecutionException {
        MPI.Init(args);

        final String[] colors = {"Red", "Green", "Blue"};

        int processId = MPI.COMM_WORLD.Rank();
        int processCount = MPI.COMM_WORLD.Size();


        System.out.println("Process " + processId + " of " + processCount + " started.");

        // Master process setup
        if (processId == 0) {
            if (processCount - 1 != COLOR_COUNT) {
                System.err.println("Error: Expected " + (COLOR_COUNT + 1) + " processes but got " + processCount);
                MPI.Finalize();
                return;
            }
        }

        GraphStructure graph = new GraphStructure(NODE_COUNT);
        graph.generateRandomEdges(EDGE_COUNT);


        ColorManager.initializeColorCount(COLOR_COUNT);
        for (int i = 1; i <= COLOR_COUNT; i++) {
            ColorManager.assignColorName(i, colors[i - 1]);
        }

        if (processId == 0) {
            // Master Process
            System.out.println("Master process is starting the graph coloring.");

            int[] initialSolution = new int[NODE_COUNT];
            Arrays.fill(initialSolution, 0); // Initialize the solution array with zeroes
            initialSolution[0] = 1; // Start with the first node colored with the first color

            try {
                int[] result = GraphColoringFuture.colorGraphWorker(0, graph, -1, initialSolution);
                System.out.println("Solution found by master process: " + ColorManager.mapNodesToColors(result));
            } catch (Exception e) {
                System.err.println("Master process encountered an error: " + e.getMessage());
                e.printStackTrace();
            }
        } else {
            // Worker Processes
            System.out.println("Worker process " + processId + " is waiting for tasks.");

            int[] solutionBuffer = new int[NODE_COUNT + 1];
            MPI.COMM_WORLD.Recv(solutionBuffer, 0, NODE_COUNT + 1, MPI.INT, 0, 0);

            System.out.println("Worker process " + processId + " received task: " + Arrays.toString(solutionBuffer));

            int startingNode = solutionBuffer[0];
            int[] partialSolution = Arrays.copyOfRange(solutionBuffer, 1, solutionBuffer.length);

            int[] result = GraphColoringFuture.colorGraphWorker(processId, graph, startingNode, partialSolution);

            System.out.println("Worker process " + processId + " sending result: " + Arrays.toString(result));
            MPI.COMM_WORLD.Send(result, 0, result.length, MPI.INT, 0, 0);
        }

        MPI.Finalize();
        System.out.println("Process " + processId + " finalized.");
    }
}
