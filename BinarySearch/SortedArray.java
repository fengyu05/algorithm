
class Solution {
    private int[] _search(int[] A, int target, int beg, int end) {
        if (end - beg == 0) return new int[] {-1, -1};
        if (end - beg == 1) {
            if (A[beg] == target) return new int[]{beg, beg};
            else return new int[]{-1, -1};
        }
        int mid = (beg + end) / 2;
        if (target < A[mid]) {
            return _search(A, target, beg, mid);
        } else if (target > A[mid]) {
            return _search(A, target, mid, end);
        } else {
            int[] left = _search(A, target, beg, mid);
            int[] right = _search(A, target, mid + 1, end);
            return new int[] {left[0] != -1 ? left[0]: mid, right[1] != -1 ? right[1]: mid};
        }
    }

    /**
      * Range search in a sorted array.
For example,
Given [5, 7, 7, 8, 8, 10] and target value 8,
return [3, 4].
      */
    public int[] searchRange(int[] A, int target) {
        int[] result = _search(A, target, 0, A.length);
        return result;
    }
}
