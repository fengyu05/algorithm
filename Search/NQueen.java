

/**
  * Find all N queen solution with backtracking.
  * Place queue each row, consider whether diagonal occupied.
  */
class Solution {
    int[] rows;
    boolean[] columns;
    ArrayList<String[]> result;
    int size;
    private void backTracking(int level) {
        if (level == size) {
            String[] board = new String[size];
            for (int i = 0; i < size; i++) {
                char[] boardRows = new char[size];
                Arrays.fill(boardRows, '.');
                boardRows[rows[i]] = 'Q';
                board[i] = new String(boardRows);
            }
            result.add(board);
            return;
        }
        for (int i = 0; i < size; i++) {
            if (!columns[i]) {// columns i not occupied
                boolean occupied = false;
                for (int prevLevel = 0; prevLevel < level; prevLevel++) {
                    if (Math.abs(level - prevLevel) == Math.abs(i - rows[prevLevel])) {
                        occupied = true;
                        break;// diagonal occupied
                    }
                }
                if (occupied) continue;
                
                rows[level] = i;
                columns[i] = true;
                backTracking(level + 1);
                rows[level] = -1;
                columns[i] = false;
            }
        }
    }
    public ArrayList<String[]> solveNQueens(int n) {
        rows = new int[n];
        columns = new boolean[n];
        result = new ArrayList<>();
        size = n;
        backTracking(0);
        return result;
    }



    /**
      * Count N queen solution using back tracking.
      * Use bit encoding.
      * Maintain the restrict with three masker, row/leftDiagonal/rightDiagnoal.
      */
    int count, rowIsFull;
    public int totalNQueens(int n){
        count = 0;
        rowIsFull = (1<<n) - 1;
        nQueenBacktracking(0,0,0);
        return count;
    }
    
    private void nQueenBacktracking(int row, int leftDiagonal, int rightDiagonal){
         if (row != rowIsFull) {
             //find the available bits position, bits that not in row/leftDiaonal/rightDiagonal
             int availablePos = rowIsFull & ( ~ (row | leftDiagonal | rightDiagonal));
             while( availablePos != 0 ) //still some '1' in availablePos
             {
                 int newBit = availablePos & (-availablePos);//from right to left, the first "1" in availablePos

                 availablePos = availablePos - newBit; //now take this newBit slot as 'Q'
                 
                 // call next level recursion with new row/leftDiagonal/rightDiagonal masker
                 // leftDiagonal shift left, rightDiaonal shift right.
                 nQueenBacktracking(row + newBit, (leftDiagonal + newBit)<<1, (rightDiagonal + newBit) >>1);
             }
         }
         else ++count;
    }
}
