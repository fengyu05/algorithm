/**
  * Common problem on matrix;
  */
public class Solution {



    /**
      * Maximum area of a 0/1 matrix
      * O(n*m)
      * preprocess, for each row acculuated each gird a row height represent
      * contigous 1 above the row.
      * Reduce to problem of maximal rectange on each row.

      * A O(n) solve to the reduced problem is maintaint a non descrease stack
      * update maximum area when need to pop element out.
      */
    public int maximalRectangle(char[][] matrix) {
        int rows = matrix.length;
        if (rows == 0) return 0;
        int columns = matrix[0].length;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                if (i == 0) {
                    matrix[i][j] = (char)(matrix[i][j] == '0' ? 0 : 1);
                    continue;
                }
                if (matrix[i][j] != '0') {
                    matrix[i][j] = (char)(matrix[i][j] - '0' + matrix[i-1][j]);
                } else {
                    matrix[i][j] = 0;
                }
            }
        }
        
        int max = 0;
        for (int i = 0; i < rows; i ++) {
            Stack<Integer> stack = new Stack<>();
            for (int j = 0; j <= columns; j++) {
                int height = j == columns ? 0 : matrix[i][j];
                if (stack.empty() || matrix[i][stack.peek()] <= height) {
                    stack.push(j);
                } else {
                    int popHeight = matrix[i][stack.pop()];
                    int prevIndex = stack.empty() ? 0 : stack.peek() + 1; // key-point
                    max = Math.max(max, popHeight * (j - prevIndex));
                    j--;
                }
            }
        }
        return max;
    }
}
