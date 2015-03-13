


    /*
     * Kth permuation basic on deduction.
     * K1 = K
     * a1 = K1/(n-1)!
       
       K(i) = K(i-1) % (n - (i - 1))!
       a(i) = K(i) / (n - i)!
       
       K(n-1) = K(n-2) % (2!)
       a(n-1) = K(n-1) / 1! 
     */
    public String getPermutation(int n, int k) {
        int[] num = new int[n];
        int permutationCount = 1;
        for (int i = 0; i< n; i++) {
            num[i] = i + 1;
            permutationCount *= i + 1;
        }
        k--;// change K from (1,n) to (0, n-1) to accord to index 
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < n; i++) {
            permutationCount = permutationCount/(n-i);
            int chosed = k / permutationCount;
            sb.append(num[chosed]);
            for (int j = chosed; j < n - i -1; j++) {// shift one number left;
                num[j] = num[j+1];
            }
            k = k % permutationCount;
            
        }
        return sb.toString();
    }


  /**
    * Next permutation base on lexicographcial order.

    If such arrangement is not possible, it must rearrange it as the lowest
     possible order (ie, sorted in ascending order).
    The replacement must be in-place, do not allocate extra memory.
Here are some examples. Inputs are in the left-hand column and its
 corresponding outputs are in the right-hand column.
1,2,3 → 1,3,2
3,2,1 → 1,2,3
1,1,5 → 1,5,1
    *
    * Algorithm:
    * 1) from right to left, find the first number(X) violate increase trend.
    * 2) from right to left, find the first number(Y) better then X.
    * 3) swap X and Y, reverse the order of sequence at the right hand of
    *    orignal X posistion.
    */
    public void nextPermutation(int[] num) {
        int X = -1, Y = -1;
        for (int i = num.length - 2; i >= 0; i--) {
            if (num[i] < num[i+1]) {
                X = i;
                break;
            }
        }
        if (X == -1) {// all number in decrease trend
            reverse(num, 0, num.length - 1);
            return;
        }
        for (int i = num.length - 1; i >= 0; i--) {
            if (num[i] > num[X]) {
                Y = i;
                break;
            }
        }
        assert(Y != -1);
        int tmp = num[X]; num[X] = num[Y]; num[Y] = tmp;
        reverse(num, X + 1, num.length - 1);
    }

    private void reverse(int A[], int beg, int endInclude) {
        while (beg < endInclude) {
            int tmp = A[beg];
            A[beg] = A[endInclude];
            A[endInclude] = tmp;
            
            beg++;
            endInclude--;
        }
    }


    /**
      * Generate all permuataion with backtracking swapping.
      */
    public ArrayList<ArrayList<Integer>> permute(int[] num) {
        Arrays.sort(num);
        ArrayList<ArrayList<Integer>> result = new ArrayList<>();
        backTracking(num, 0, result);
        return result;
    }

    private void swap(int[] num, int x, int y) {
        if (x == y) return;
        int tmp = num[x]; num[x] = num[y]; num[y] = tmp;
    }
    private void backTracking(int[] num, int level, ArrayList<ArrayList<Integer>> result) {
        if (level == num.length - 1) {
            ArrayList<Integer> solu = new ArrayList<Integer>();
            for (int val: num) solu.add(val);
            result.add(solu);
            return;
        }
        for (int i = level; i < num.length; i++) {
            swap(num, level, i);
            backTracking(num, level + 1, result);
            swap(num, level, i);
        }
    }


    private void _backtracking(int[] num, int level, boolean[] select, ArrayList<Integer> solu, ArrayList<ArrayList<Integer>> result) {
        if (level == num.length) {
            result.add(new ArrayList<>(solu));
            return;
        }
        for (int i = 0; i < num.length; i++) {
            if (select[i] == false) {
                if (i > 0 && num[i] == num[i - 1] && select[i-1] == false) continue;// a number can be selected if its privous was selected
                select[i] = true;
                solu.add(num[i]);
                _backtracking(num, level + 1, select, solu, result);
                solu.remove(solu.size() - 1);
                select[i] = false;
            } 
        }
        
    }
    /**
      * Generate all permutation by selecting.
      * allow duplicate element in the set.
      */
    public ArrayList<ArrayList<Integer>> permuteUnique(int[] num) {
        Arrays.sort(num);
        ArrayList<ArrayList<Integer>> result = new ArrayList<>();
        ArrayList<Integer> solu = new ArrayList<>();
        boolean[] select = new boolean[num.length];
        _backtracking(num, 0, select, solu, result);
        return result;
    }
}
