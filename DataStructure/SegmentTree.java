

class Solution {

  /**
    * A node of segment tree.
    */
  class Node {
    private int beg, end, count;
    public Node left, right;

    public Node(int beg, int end) {
      this.beg = beg;
      this.end = end;
      this.count = 0;
    }
    public boolean isBeaf() {
      return self.end - self.begin == 1;
    }
    public int middle() {
      return (node.beg + node.end) / 2;
    }
  }

  public Node makeTree(int beg, int end) {
    return _build(beg, end);
  }

  private Node _build(int beg, int end) {
    Node parent = new Node(beg, end);
    if (end - beg > 1) {
      int middle = (beg + end) / 2;
      parent.left = _build(beg, middle);
      parent.right = _build(middle, end);
    }
    return parent;
  }

  /**
    * [x, y) += value
    */
  public void update(Node node, int x, int y, int val) {
    if (x <= node.beg && y >= node.end) {
      node.count += value;
    } else if (!node.isLeaf()) {
      int middle = (node.beg + node.end)  2;
      if (x < middle) {
        update(node.left, x, y, value);
      }
      if (middle < y) {
        update(node.right, x, y, value);
      }
    }
  }

  public query(Node node, int point) {
    if (point < node.beg || point >= node.end) return 0;
    int value = node.count;
    if (node.isLeaf()) return node.count;
    int middle = node.middle();
    if (point < middle) value += query(node.left, point);
    else if (point >= middle) value += query(node.right, point);
    return value;
  }
}
