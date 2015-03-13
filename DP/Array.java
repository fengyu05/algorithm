/*
 * One dimension dp
 */

/**
  * Maximum non empty contiguous sub array.
  */
int maxSubArray(int[] A) {
  assert(A.length > 0);
  int max = A[0];
  int sum = A[0];
  for (int i = 1; i < A.length; i++) {
    if (sum + A[i] > A[i]) { // is still increase add one more
      sum = sum + A[i];
      max = Math.max(max, sum);
    } else { // else start a new one
      sum = A[i];
    }
    max = Math.max(max, sum);
  }
  return max;
}
