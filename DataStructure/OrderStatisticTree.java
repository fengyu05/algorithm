

/**
  * Order Statistic on BST
  */
class BSTOrderStatisticTree {


  class Node {
    int val;
    Node left, right;
    int size;

    Node(int val) {
      this.val = val;
      this.size = 1;
      this.left = null;
      this.right = null;
    }
  }


  Node insert(int val, Node root) {
    root.size++;
    if (val < root.val) {
      if (root.left == null) {
        root.left = new Node(val);
      } else {
        root.left = insert(val, root.left);
      }
    } else {
      if (root.right == null) {
        root.right = new Node(val);
      } else {
        root.right = insert(val, root.right);
      }
    }
  }

  Node select(int kth, Node root) {
    if (kth > root.size) return null;
    if (root.left != null && kth < root.left)
      return select(kth, root.left);
    else
      return select(kth - root.left.size, root.right);
  }
}
