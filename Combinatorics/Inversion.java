
/**
  * Inversion vector
  * V[i] = |{k|k < i and A(k) > A(i)}|.
  *In other words each element is the number of elements preceding the element in the original sequence that are greater than it.
  * Inversion number = Sum(V)
  * Ex:
  The permutation (4,1,5,2,6,3) has the inversion vector (0,1,0,2,0,3) and the inversion set {(1,2),(1,4),(3,4),(1,6),(3,6),(5,6)}.
*/
class Inversion {


  /**
    * Populate inversion for an array. Return the total inversion.
    * O(n^2)
    */
  int populateInversion(int[] A, int[] inversion) {
    Arrays.fill(inversion, 0);
    int totalInversion = 0;
    inversion[0] = 0;
    for (int i = 1; i < n; i++) {
      for (int k = 0; k < i; k++) {
        if (A[k] > A[i]) {
          inversion[i]++;
          totalInversion++;
      }
    }
    return totalInversion;
  }

  /**
    * Reconstruct array using inversion vector.
    * O(n^2)
    */
  void populatePermutationFormInversion(int[] A, int[] inversion) {
    int n = A.length;
    boolean[] flag = new boolean[n];
    for (int i = n - 1; i >= 0; i--) {
      int inversionCount = inversion[i];
      int offset = n - 1;
      while(inversionCount > 0 || flag[offset]) {
        offset--;
        if (!flag[offset]) inversionCount--;
      }
      flag[offset] = true;
      A[i] = offset;
    }
  }

  /**
    * Reconstruct array using inversion by a point tree. 
    * PointTree is a array/BST with update node and index rank k element in tree.
    * O(n)
    */
  void populatePermutationFromInversionUsingPointTree(int[] A, int[] inversion) {
    // MAX_N = min 2^x st MAX_N > A.length
    PointTree pointTree = new PointTree(MAX_N);
    for (int i = 0; i < n; i++) pointTree.add(i);
    for (int i = n - 1; i >= 0; i--) {
      int tmp = pointTree.lastKth(inversion[i]);
      A[i] = tmp;
      pointTree.remove(tmp);
    }
  }
}
