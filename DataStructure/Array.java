

/**
  * Scan the array just once.
  * Record or maintain some data structure to achieve the goal. 
  */
class ScanSolution {


    /**
      * Given an array of vertical line, ask the maximum area.
      * area = min(leftHeight, rightHeight) * (right - left)
      * Scan from two edge toward center, move left when leftHeight < rightHeight
      */
    public int maxArea(int[] height) {
        int len = height.length;
        if (len <= 1) return 0;
        int left = 0;
        int right = len -1;
        
        int max = 0;
        while (left < right) {
            max = Math.max(max, Math.min(height[left], height[right]) * (right - left));
            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }
        return max;
    }
}

/**
  * Sometime use the input array to reduce O(n) space to constance space.
  */
class InplaceSolution {

    /**
      * Find first missive
      */
    public int firstMissingPositive(int[] A) {
        int len = A.length;
        for (int i = 0; i < len; i++) {
            int val = A[i];
            while (val<=len && val >= 1 && val != i + 1 && A[val-1] != val) {
                A[i] = A[val-1]; A[val-1] = val;
                val = A[i];
            }
        }
        for (int i = 0; i < len; i++) {
            if (A[i] != i + 1) return i + 1;
        }
        return len + 1;
    }


    /**
     * Inplace merge two sorted array.
     * Merge form the end to begin.
     */
    public void merge(int A[], int m, int B[], int n) {
        while(n >0){
            if(m>0 && A[m-1]>B[n-1]){
                A[n+m-1]=A[m-1];
                m--;
            }else{
                A[n+m-1]=B[n-1];
                n--;
            }
        }
    }

    
    /**
     * O(nlogn)
     * This can be done in O(nlogn) using divide and conquer scheme. Before starting the algorithm, please see the following observation: 

     Observation: given an array A, say [1, -2, ..., 4], with n elements, we can get the inverse of A, denoted as A’ (4, …, -2, 1), in \theta(n) time with O(1) space complexity. 

     The basic idea of the algorithm is as follows: 
     1. We recursively ‘sort’ two smaller arrays of size n/2 (here ‘sort’ is defined in the question) 
     2. Then we spend \theta(n) time merging the two sorted smaller arrays with O(1) space complexity. 
     How to merge? 
     Suppose the two sorted smaller array is A and B. A1 denotes the negative part of A, and A2 denotes positive part of A. Similarly, B1 denotes the negative part of B, and B2 denotes positive part of B. 
     2.1. Compute the inverse of A2 (i.e., A2’) in \theta(|A2|) time; compute the inverse of B1 (i.e., B1’) in \theta(|B1|) time. [See observation; the total time is \theta(n) and space is O(1)] 
     Thus the array AB (i.e., A1A2B1B2) becomes A1A2’B1’B2. 
     2.2. Compute the inverse of A2’B1’ (i.e., B1A2) in \theta(|A2|) time. [See observation; the total time is \theta(n) and space is O(1)] 
     Thus the array A1A2’B1’B2 becomes A1B1A2B2. We are done. 

     Time complexity analysis: 
     T(n) = 2T(n/2) + \theta(n) = O(nlogn)
     */
    public int inplaceStablePartition(int[] A, int beg, int end, int val) {
      if (beg == end - 1) return A[beg] > 0? beg: end;
      int mid = (beg + end) / 2;
      int pos1 = inplaceStablePartition(A, beg, mid, val);
      int pos2 = inplaceStablePartition(A, mid, end, val);
      int neg2 = pos1 + pos2 - mid;
      reverse(A, pos1, pos2);
      reverse(A, pos1, neg2);
      reverse(A, neg2, pos2);
      return neg2; 
    }
}
