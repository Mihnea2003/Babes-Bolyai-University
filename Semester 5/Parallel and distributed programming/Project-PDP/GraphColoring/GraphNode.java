import java.util.HashSet;
import java.util.Objects;
import java.util.Set;

public class GraphNode {
    private final Integer id;
    private final Set<GraphNode> adjacentNodes;

    public GraphNode(Integer id) {
        this.id = id;
        this.adjacentNodes = new HashSet<>();
    }

    public Integer getId() {
        return id;
    }

    public Set<GraphNode> getConnections() {
        return adjacentNodes;
    }

    public boolean isConnectedTo(GraphNode otherNode) {
        return adjacentNodes.contains(otherNode);
    }

    public void addAdjacentNode(GraphNode otherNode) {
        adjacentNodes.add(otherNode);
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (!(obj instanceof GraphNode otherNode)) return false;
        return id.equals(otherNode.id);
    }

    @Override
    public int hashCode() {
        return Objects.hash(id);
    }
}