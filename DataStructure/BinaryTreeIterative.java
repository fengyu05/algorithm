
class TreeNode {
  int val;
  TreeNode left;
  TreeNode right;
  TreeNode(int x) { val = x; }
}


/**
  * Common problems on Binary tree.
  * Using iterative instead of recursion.
  */
class Solution {

    /* ------------------------------------------------------------------- */
    /**
     * Depth of a tree.
     * Access null in recursion make coding easy.
     */
    public int maxDepth(TreeNode root) {
        if (root == null) return 0;
        Stack<TreeNode> stack = new Stack<>();
        Map<TreeNode, Integer> map = new HashMap<>();
        stack.push(root);
        map.put(root, 1);
        int maxDepth = 1;
        while (stack.size() > 0) {
          TreeNode curr = stack.pop();
          int currDepth = map.get(curr);
          if (curr.left) {
            map[curr.left] = currDepth + 1;
            stack.push(curr.left);
            maxDepth = Math.max(maxDepth, currDepth + 1);
          }
          if (curr.right) {
            map[curr.left] = currDepth + 1;
            stack.push(curr.right);
            maxDepth = Math.max(maxDepth, currDepth + 1);
          }
        }
        return maxDepth;
    }
    /* ------------------------------------------------------------------- */

    /**
      * preorder travel.
      */
    public ArrayList<Integer> preorderTraversal(TreeNode root) {
        ArrayList<Integer> result = new ArrayList<>();
        if (root == null) return result;

        Stack<TreeNode> stack = new Stack<TreeNode>();
        stack.push(root);

        while (stack.size() > 0) {
          TreeNode curr = stack.pop();
          result.add(curr.val);

          if (curr.right != null) {
            stack.push(curr.right);
          }
          if (curr.left != null) {
            stack.push(curr.left);
          }
        }
        return result;
    }

    /**
     * postorder travel.
     */
    public ArrayList<Integer> postorderTraversal(TreeNode root) {
        ArrayList<Integer> result = new ArrayList<>();
        if (root == null) return result;

        Stack<TreeNode> stack = new Stack<TreeNode>();
        stack.push(root);

        while (stack.size() > 0) {
          TreeNode curr = stack.pop();
          result.add(curr.val);

          if (curr.left != null) {
            stack.push(curr.left);
          }
          if (curr.right != null) {
            stack.push(curr.right);
          }
        }
        return Collections.reverse(result);
    }
    /* ------------------------------------------------------------------- */

    /**
      * Inorder travel.
      */
    public ArrayList<Integer> inorderTraversal(TreeNode root) {
        ArrayList<Integer> result = new ArrayList<>();
        if (root == null) return result;

        Stack<TreeNode> stack = new Stack<TreeNode>();
        TreeNode curr = root;
        while (!stack.isEmpty() || curr != null) {
          
          if (curr != null) {
              stack.push(curr);
              curr = curr.left;
          } else {
              curr = stack.pop();
              result.add(curr.val);
              curr = curr.right;
          }
        }
        return result;
    }
} 
