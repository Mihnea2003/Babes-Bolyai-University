import mpi.MPI;
import java.util.*;

public class GraphColoringHandler {
    public static void initiateColoring(GraphStructure graph) throws InterruptedException {
        int colorCount = ColorManager.getColorCount();
        int[] solution = findColoring(-1, graph, colorCount, new int[graph.getNodeCount()], 0);

        if (solution[0] == -1) {
            throw new RuntimeException("No valid coloring solution found!");
        }
    }

    private static int[] findColoring(int currentNode, GraphStructure graph, int colorCount, int[] currentSolution, int processId) throws InterruptedException {
        int nodeCount = graph.getNodeCount();

        if (!isSolutionValid(currentNode, currentSolution, graph)) {
            return createInvalidSolution(nodeCount);
        }

        if (currentNode + 1 == nodeCount) {
            return currentSolution;
        }

        int nextNode = currentNode + 1;
        int sender, receiver;

        for (int color = 1; color <= colorCount; color++) {
            receiver = color;

            if (color != processId) {
                int[] partialSolution = new int[]{nextNode};
                int[] updatedSolution = copyArray(currentSolution);
                updatedSolution[nextNode] = color;

                int[] buffer = new int[partialSolution.length + updatedSolution.length];
                System.arraycopy(partialSolution, 0, buffer, 0, partialSolution.length);
                System.arraycopy(updatedSolution, 0, buffer, partialSolution.length, updatedSolution.length);

                MPI.COMM_WORLD.Isend(buffer, 0, buffer.length, MPI.INT, receiver, 0);
            }
        }

        int[] result;

        if (processId != 0) {
            int[] solutionForCurrentProcess = copyArray(currentSolution);
            solutionForCurrentProcess[nextNode] = processId;
            result = findColoring(nextNode, graph, colorCount, solutionForCurrentProcess, processId);

            if (result[0] != -1) {
                return result;
            }
        }

        for (int color = 1; color <= colorCount; color++) {
            sender = color;

            if (color != processId) {
                int[] buffer = new int[nodeCount + 1];
                MPI.COMM_WORLD.Recv(buffer, 0, nodeCount + 1, MPI.INT, sender, 0);

                int previousNode = buffer[0];
                int[] receivedSolution = new int[nodeCount];
                System.arraycopy(buffer, 1, receivedSolution, 0, receivedSolution.length);

                if (processId != 0) {
                    result = findColoring(previousNode, graph, colorCount, receivedSolution, processId);
                    if (result[0] != -1) {
                        return result;
                    }
                } else {
                    if (receivedSolution[0] != -1) {
                        System.out.println("Process " + sender + " provided solution: " + ColorManager.mapNodesToColors(receivedSolution));
                    }
                }
            }
        }

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

    private static int[] createInvalidSolution(int length) {
        int[] invalidSolution = new int[length];
        Arrays.fill(invalidSolution, -1);
        return invalidSolution;
    }

    private static int[] copyArray(int[] original) {
        return Arrays.copyOf(original, original.length);
    }
}