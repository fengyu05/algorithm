

class Trie {

  static int CHILDREN_SIZE = 26;
  
  class Node {
    char value;
    Node[] children;
    boolean isLeaf;

    public Node(char value) {
      this.value = value;
      this.children = new Node[CHILDREN_SIZE];
      Arrays.fill(children, -1);
      this.isLeaf = false;
    }
  }

  Node init() {
    Node root = new Node(' ');
  }

  Node insert(String word, Node node) {
    for (char c : word.toCharArray()) {
      if (node.children[c-'a'] == null) {
        node.children[c-'a'] = new Node(c);
      }
      node = node.children[c-'a'];
    }
    node.isLeaf = true;
    return node;
  }

  Node query(String word, Node node) {
    for (char c : word.toCharArray()) {
      if (node.children[c-'a'] != null) {
        node = node.children[c-'a'];
      } else {
        return null;
      }
    }
    return node;
  }
}
