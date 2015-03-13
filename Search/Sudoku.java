
/**
  * Solve Sudoku using backtracking.
  */
class Solution {
    private boolean isValid(char[][] board, int row, int column) {
        boolean[] rows = new boolean[128];
        boolean[] columns = new boolean[128];
        boolean[] block = new boolean[128];
        for (int i = 0; i< 9; i++) {
            // rows
            char val = board[row][i];
            if (val != '.') {
                if (rows[val]) return false;
                rows[val] = true;
            }
            // columns
            val = board[i][column];
            if (val != '.') {
                if (columns[val]) return false;
                columns[val] = true;
            }
        }
        int rowOffset = row / 3 * 3;
        int columnOffset = column / 3 * 3;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                char val = board[rowOffset+i][columnOffset+j];
                if (val != '.') {
                    if (block[val]) return false;
                    block[val] = true;
                }
            }
        }
        return true;
    }
    public boolean _solveSudoku(char[][] board, int level, ArrayList<Point> pointList) {
        Point point = pointList.get(level);
        for (char x = 0; x < 9; x++) {
            board[point.x][point.y] = (char)('1' + x);
            if (isValid(board, point.x, point.y)) {
                if (level == pointList.size() - 1) return true;
                boolean result = _solveSudoku(board, level + 1, pointList);
                if (result) return true;
            }
            board[point.x][point.y] = '.';
        }

        return false;
    }
    
    class Point {
        public int x, y;
        public Point(int x, int y) {
            this.x = x;
            this.y = y;
        } 
    }
    public void solveSudoku(char[][] board) {
        ArrayList<Point> pointList = new ArrayList<>();
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') {
                    pointList.add(new Point(i,j));
                }
            }
        }
        _solveSudoku(board, 0, pointList);
    }
}
