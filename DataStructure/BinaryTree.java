

class TreeNode {
  int val;
  TreeNode left;
  TreeNode right;
  TreeNode(int x) { val = x; }
}


/**
  * Common problems on Binary tree.
  */
class Solution {

    /* ------------------------------------------------------------------- */
    /**
     * Depth of a tree.
     * Access null in recursion make coding easy.
     */
    public int maxDepth(TreeNode root) {
        if (root == null) return 0;
        return Math.max(maxDepth(root.left), maxDepth(root.right)) + 1;
    }
    /* ------------------------------------------------------------------- */


    /* ------------------------------------------------------------------- */
    private void _preorderTraversal(TreeNode root, ArrayList<Integer> result) {
        if (root == null) return;
        result.add(root.val);
        if (root.left != null) _preorderTraversal(root.left,result);
        if (root.right != null) _preorderTraversal(root.right,result);
    }
    
    /**
     * preorder travel with recursion.
     */
    public ArrayList<Integer> preorderTraversal(TreeNode root) {
        ArrayList<Integer> result = new ArrayList<>();
        preorderTraversal(root, result);
        return result;
    }
    /* ------------------------------------------------------------------- */


    
    /* ------------------------------------------------------------------- */
    private TreeNode _flatten(TreeNode root, TreeNode nextLink) {
        if (root == null) return nextLink;
        if (root.left == null && root.right == null) {
            root.right = nextLink;
            return root;
        }
        TreeNode rightTree = _flatten(root.right, nextLink);
        if (root.left != null) {
            root.right = _flatten(root.left, rightTree);
        } else {
            root.right = rightTree;
        }
        root.left = null;
        return root;
    }

    /**
     * Flatten a binary tree to a link list. root=>left=>right;
     */
    public void flatten(TreeNode root) {
        if(root == null) return;
        _flatten(root, null);
    }
    /* ------------------------------------------------------------------- */


    /* ------------------------------------------------------------------- */
    /**
      * A recursion to find maximum path.
      * return [] {maxPath, maxPath from the root}
      */
    private int[] _maxPathSum(TreeNode root) {
        if (root.left == null && root.right == null) return new int[] {root.val, root.val};
        if (root.left != null && root.right == null || root.right != null && root.left == null) {
            int[] resultMax = _maxPathSum(root.left != null ? root.left : root.right);
            resultMax[1] = Math.max(resultMax[1] + root.val, root.val);
            resultMax[0] = Math.max(resultMax[0], resultMax[1]);
            return resultMax;
        }
        int[] leftMax = _maxPathSum(root.left);
        int[] rightMax = _maxPathSum(root.right);
        
        int[] resultMax = new int[2];
        resultMax[1] = Math.max(leftMax[1], rightMax[1]);
        resultMax[1] = Math.max(resultMax[1] + root.val, root.val);
        
        resultMax[0] = Math.max(leftMax[0], rightMax[0]);
        resultMax[0] = Math.max(resultMax[0], resultMax[1]);
        resultMax[0] = Math.max(resultMax[0], leftMax[1] + rightMax[1] + root.val);
        return resultMax;
    }
    
    /**
      * Find the maximum path.
      */
    public int maxPathSum(TreeNode root) {
        if (root == null) return 0;
        return _maxPathSum(root)[0];
        
    }
    /* ------------------------------------------------------------------- */

    
    /* ------------------------------------------------------------------- */
    private TreeNode _buildTree(int[] num, int begin, int end) {
        assert(end > begin);
        if (end - begin == 1) { return new TreeNode(num[begin]); }
        if (end - begin == 2) {
            TreeNode root = new TreeNode(num[begin]);
            root.right = new TreeNode(num[begin + 1]);
            return root;
        }
        int mid = (begin + end) / 2;
        TreeNode root = new TreeNode(num[mid]);
        root.left = _buildTree(num, begin, mid);
        root.right = _buildTree(num, mid + 1, end);
        return root;
    }
    /**
      * Build a bst from sorted array.
      */
    public TreeNode sortedArrayToBST(int[] num) {
        if (num.length == 0) return null;
        return _buildTree(num, 0, num.length);
    }
    /* ------------------------------------------------------------------- */

    
    /* ------------------------------------------------------------------- */
    class Pair {
        public Pair(TreeNode node, ListNode head) {
            this.node = node;
            this.head = head;
        }
        public TreeNode node;
        public ListNode head;
    }

    /**
      * Recursion to build BST from linklist.
      * Need to return two value, rootNode of BST /nextNode of linklist
      */
    private Pair _buildTree(ListNode head, int size) {
        if (size == 1) {
            int val = head.val;
            return new Pair(new TreeNode(val), head.next);
        }
        int mid = size / 2;

        TreeNode left = null;
        TreeNode right = null;
        if (size / 2 > 0) {
            Pair pair = _buildTree(head, size / 2);
            head = pair.head;
            left = pair.node;
        }
        TreeNode middle = new TreeNode(head.val);
        head = head.next;
        if (size - size/2 - 1 > 0 && head != null) {
            Pair pair = _buildTree(head, size - size/2 - 1);
            head = pair.head;
            right = pair.node;
        }
        middle.left = left;
        middle.right = right;
        return new Pair(middle, head);
    }

    /**
      * Build a BST from sorted link list.
      */
    public TreeNode sortedListToBST(ListNode head) {
        if (head == null) return null;
        
        int size = 1;
        ListNode current = head;
        while(current.next != null) { size++; current = current.next; } 
        
        return _buildTree(head, size).node;
    }
    /* ------------------------------------------------------------------- */


    /* ------------------------------------------------------------------- */
    private TreeNode _buildTree(int[] preorder, int[] inorder, int preBegin, int inBegin, int length, Map<Integer, Integer> map) {
        if (length <= 0) return null;
        TreeNode root = new TreeNode(preorder[preBegin]);
        if (length == 1) return root;
        int offset = map.get(root.val) - inBegin;
        root.left = _buildTree(preorder, inorder, preBegin + 1, inBegin, offset, map);
        root.right = _buildTree(preorder, inorder, preBegin + offset + 1, inBegin + offset + 1, length - offset - 1, map);
        return root;
    }
    /*
     * Build bst tree from a preorder sequence and a inorder sequence
     * Using a hashmap to achieve O(n)
     */
    public TreeNode buildTree(int[] preorder, int[] inorder) {
        if (preorder.length == 0) return null;
        Map<Integer, Integer> inPositionByValue = new HashMap<>();
        for (int i = 0; i < inorder.length; i ++) {
            inPositionByValue.put(inorder[i], i);
        }
        return _buildTree(preorder, inorder, 0, 0, preorder.length, inPositionByValue);
    }
    /* ------------------------------------------------------------------- */


    /* ------------------------------------------------------------------- */
    private TreeNode _buildTree(int[] inorder, int[] postorder, int inBegin, int postBegin, int length, Map<Integer, Integer> map) {
        if (length <= 0) return null;
        TreeNode root = new TreeNode(postorder[postBegin + length - 1]);
        if (length == 1) return root;
        int offset = map.get(root.val) - inBegin;
        root.left = _buildTree(inorder, postorder, inBegin, postBegin, offset, map);
        root.right = _buildTree(inorder, postorder, inBegin + offset + 1, postBegin + offset, length - offset - 1, map);
        return root;
    }
    /**
      * Build a bst tree from a inorder sequence and a postorder sequence.
      */
    public TreeNode buildTree(int[] inorder, int[] postorder) {
        if (inorder.length == 0) return null;
        Map<Integer, Integer> inPositionByValue = new HashMap<>();
        for (int i = 0; i < inorder.length; i ++) {
            inPositionByValue.put(inorder[i], i);
        }
        return _buildTree(inorder, postorder, 0, 0, inorder.length, inPositionByValue);
    }
    /* ------------------------------------------------------------------- */

    /* ------------------------------------------------------------------- */
    public boolean isSymmetric(TreeNode root) {
        if (root == null) return true;
        if (root.left == null && root.right == null) return true;
        if (root.left != null && root.right != null && root.left.val == root.right.val) {
            TreeNode fake = new TreeNode(-1);
            fake.left = root.left.left;
            fake.right = root.right.right;
            if (!isSymmetric(fake)) return false;
            
            fake.left = root.left.right;
            fake.right = root.right.left;
            if (!isSymmetric(fake)) return false;
            return true;
        } return false;
    }
    /* ------------------------------------------------------------------- */

    /* ------------------------------------------------------------------- */
    private void _generateTrees(int beg, int end, ArrayList<TreeNode> result) {
        if (end < beg) { result.add(null); return;}

        if (end == beg) {
            result.add(new TreeNode(beg));
            return;
        }
        
        for (int i = beg - 1; i + 1 <= end ; i++) {
            ArrayList<TreeNode> leftResult = new ArrayList<>(); _generateTrees(beg, i, leftResult);
            ArrayList<TreeNode> rightResult = new ArrayList<>(); _generateTrees(i + 2, end, rightResult);
            
            for(TreeNode left : leftResult) {
                for (TreeNode right : rightResult) {
                    TreeNode newRoot = new TreeNode(i + 1);
                    newRoot.left = left;
                    newRoot.right = right;
                    result.add(newRoot);
                }
            }
        }
    }
    /**
      * Generate unique BSTs. 
      */
    public ArrayList<TreeNode> generateTrees(int n) {
        ArrayList<TreeNode> result = new ArrayList<>();
        _generateTrees(1, n, result);
        return result;
    }
    /* ------------------------------------------------------------------- */

    /* ------------------------------------------------------------------- */
    private TreeNode first, second, prev;
    
    private void inOrder(TreeNode root) {
        if (root == null) {
            return;
        }
        if (root.left != null) inOrder(root.left);
        if (prev == null) {
            prev = root;
        } else {
            if (prev.val > root.val) {
                if (first == null) {
                    first = prev;
                    second = root;
                } else {
                    second = root;
                }
            }
            prev = root;
        }
        
        if (root.right != null) inOrder(root.right);
    }
    /**
      * recover a BST that have two nodes inversed.
      */
    public void recoverTree(TreeNode root) {
        prev = null;
        first = null;
        second = null;
        inOrder(root);
        
        assert(first != null);
        assert(second != null);
        
        
        int tmp = first.val; first.val = second.val; second.val = tmp;
    }
    /* ------------------------------------------------------------------- */
} 
