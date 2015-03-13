

class Solution {
    private void _backtracking(int[] candidates, int target, int level, ArrayList<Integer> solu,
        ArrayList<ArrayList<Integer>> result) {       
        if (level >= candidates.length) return;
        for (int i = 0; i <= target / candidates[level]; i++) {
            int remain = target - i * candidates[level];
            for (int j = 0; j < i; j++) solu.add(candidates[level]);// add i candidates[level]
            if (remain == 0) { // found a solution
                result.add(new ArrayList<>(solu));
            } else { //  constraint condition
                if (level + 1 < candidates.length && remain >= candidates[level]) { // 
                    _backtracking(candidates, target - i * candidates[level], level + 1, solu, result);
                }
            }
            for (int j = 0; j < i; j++) solu.remove(solu.size() - 1);// remove i candidates[level]
        }
    }

    /**
      * Backtracking to find a combination sum, using candidates zero or more time.
      */
    public ArrayList<ArrayList<Integer>> combinationSum(int[] candidates, int target) {
        Arrays.sort(candidates);
        ArrayList<ArrayList<Integer>> result = new ArrayList<>();
        ArrayList<Integer> solu = new ArrayList<>();
        _backtracking(candidates, target, 0, solu, result);
        return result;
    }
}
