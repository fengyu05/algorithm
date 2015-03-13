

class UndirectedGraphNode {
  int label;
  ArrayList<UndirectedGraphNode> neighbors;
  UndirectedGraphNode(int x) { label = x; neighbors = new ArrayList<UndirectedGraphNode>(); }
};
public class Solution {

    /**
      * Copy a undirected graph with a bfs.
      * Use deque as a open, use map as close.
      */
    public UndirectedGraphNode cloneGraph(UndirectedGraphNode node) {
        if (node == null) return null;
        Deque<UndirectedGraphNode> queue = new ArrayDeque<>();
        Map<UndirectedGraphNode, UndirectedGraphNode> map = new HashMap<>();
        queue.add(node);
        UndirectedGraphNode newNode = new UndirectedGraphNode(node.label);
        map.put(node, newNode);
        while (queue.size() > 0) {
            UndirectedGraphNode curr = queue.remove();
            UndirectedGraphNode newCurr = map.get(curr);
            for (UndirectedGraphNode next : curr.neighbors) {
                if (!map.containsKey(next)) {
                    UndirectedGraphNode newNext = new UndirectedGraphNode(next.label);
                    newCurr.neighbors.add(newNext);
                    map.put(next, newNext);
                    queue.add(next);
                } else {
                    newCurr.neighbors.add(map.get(next));
                }
            }
        }
        return newNode;
    }
}
