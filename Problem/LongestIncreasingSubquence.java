

class LIS_Solution {

    /**
     * LIS problem
     * Longest Monotonically Increasing Subsequence Size (N log N)
     * Patience sorting algorithm.
     * http://en.wikipedia.org/wiki/Patience_sorting
     * considering only strictly increasing monotone sequences.
     */
    public int LIS(int[] A) {
        int len = A.length;
        assert(len > 0);
        int maxLen = 0;
        int[] tailNum = new int[len];
        tailNum[maxLen++] = A[0];
        
        for (int i = 1; i < len; i++) {
            if (A[i] < tailNum[0]) {
                tailNum[0] = A[i];
            } else if (A[i] > tailNum[maxLen - 1]) {
                tailNum[maxLen++] = A[i];
            } else {
                tailNum[searchIndex(tailNum, -1, maxLen - 1, A[i])] = A[i];
            }
        }
        return maxLen;
    }
    
    /**
     * Binary search the smallest index of a sorted array nums,
     * such that nums[index] < val.
     */
    private int searchIndex(int[] nums, int left, int right, int val) {
        int middle;
        while( right - left > 1 ) {
            middle = left + (right - left)/2;
            if (nums[middle] >= val) right = middle;
            else left = middle;
        }
        return right;
    }
}
