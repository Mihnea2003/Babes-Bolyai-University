import java.util.*;

public class GraphStructure {
    private final Set<GraphNode> nodes;
    private final int threadLimit = 16;

    public GraphStructure(int nodeCount) {
        nodes = new HashSet<>(nodeCount);
        for (int id = 0; id < nodeCount; id++) {
            nodes.add(new GraphNode(id));
        }
    }

    public void createEdge(Integer node1Id, Integer node2Id) {
        GraphNode node1 = findNodeById(node1Id);
        GraphNode node2 = findNodeById(node2Id);

        node1.addAdjacentNode(node2);
        node2.addAdjacentNode(node1);
    }

    public boolean edgeExists(Integer node1Id, Integer node2Id) {
        GraphNode node1 = findNodeById(node1Id);
        GraphNode node2 = findNodeById(node2Id);

        return node1.isConnectedTo(node2);
    }

    public List<GraphNode> getAllNodes() {
        return nodes.stream().sorted().toList();
    }

    public GraphNode findNodeById(int id) {
        return nodes.stream().filter(node -> Objects.equals(node.getId(), id)).findFirst().orElseThrow();
    }

    public int getNodeCount() {
        return nodes.size();
    }

    public void generateRandomEdges(int edgeCount) {
        Random random = new Random();
        int nodeCount = getNodeCount();

        int addedEdges = 0;
        while (addedEdges < edgeCount) {
            int node1Id = random.nextInt(nodeCount);
            int node2Id = random.nextInt(nodeCount);


            if (node1Id != node2Id && !edgeExists(node1Id, node2Id)) {
                createEdge(node1Id, node2Id);
                addedEdges++;
            }
        }
    }
}