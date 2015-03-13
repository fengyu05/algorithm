

class Node {
  public Node left, right, parent;
  public Node(Node left, Node right, Node parent) {
    this.left = left;
    this.right = right;
    this.parent = parent;
  }
}


class LCASolution {

  public Node lca(Node a, Node b) {
    int aLen = 0, bLen = 0;
    Node pa = a, pb = b;
    while (pa != null) {
      pa = pa.parent;
      aLen++;
    }
    while (pb != null) {
      pb = pb.parent;
      bLen++;
    }
    if (aLen < bLen) {
      int tmp = bLen; bLen = aLen; aLen = tmp;
      Node tmpNode = b; b = a; a = tmp;
    }
    for (int i = 0; i < aLen - bLen; i++) a = a.parent;
    while (a != b) {
      a = a.parent;
      b = b.parent;
    }
    return a;
  }
}


class RMQSoluction {
  int[] A;
  int N;

  int[] M; //1D array
  int[][] M2; // 2D array

  public RMQSoluction(int[] A) {
    this.A = A;
    this.N = A.length;
  }

  /**
   * straight DP <O(n^2), O(1)>
   */
  public void process1() {
    M2 = new int[N][N];
    for (int i =0; i < N; i++)
      M[i][i] = i;
    for (int i = 0; i < N; i++)
      for (int j = i + 1; j < N; j++)
        if (A[M[i][j - 1]] < A[j])
          M[i][j] = M[i][j - 1];
        else
          M[i][j] = j;
  }

  public int query1(int a, int b) {
    return A[M[a][b]];
  }
  /* -------- end -------------*/


  /**
    * Divide by sqrt(n), DP <O(n), O(sqrt(n))>
    */

  public void process2() {
    int sqrtn = (int)Math.ceil(Math.sqrt(N));
    M = new int[sqrtn];
    for (int i = 0; i < N; i++) {
      if (i % sqrtn == 0 ) {
        M[i / sqrtn] = i;
      } else {
        int val = A[M[i/sqrtn]];
        if (A[i] < val) M[i/sqrtn] = i;
      }
    }
  }

  public int query2(int a, int b) {
    int sqrtn = (int)Math.ceil(Math.sqrt(N));
    int min = Integer.MAX_VALUE;
    for (int i = a; i <= b; i++) {
      if (i % sqrtn == 0 && i + sqrtn <= b) {
        min = Math.min(min, A[M[i/sqrtn]);
      } else {
        min = Math.min(min, A[i]);
      }
    }
    return min;
  }

  /**
    * Sparse table algorithm <O(NlogN), O(1)>
    */
  public void process3() {
    int logn = Math.ceil(Math.log(n));
    M = new int[N][logn];
    for (int i = 0; i < N; i++) M[i][0] = i;
    for (int j = 1;  (1<<j) < N; j++) {
      for (int i = 0; i + (1<<j) - 1 < N; i++) {
        if (A[M[i][j-1]] < A[M[i + 1<<(j-1)][j-1]]) {
          M[i][j] = M[i][j-1];
        } else {
          M[i][j] = M[i + 1<<(j-1)][j-1];
        }
      }
    }
  }

  public int query3(int a, int b) {
    int k = Math.log(b - a + 1);
    int min = Math.min(A[M[[a][k]], A[M[b-(1<<k)+1][k]]);
    return min;
  }

  /**
    * Using internal tree.
    * M[1..2*2[logn] + 1] index mean the node of a perfect binary tree.
    * if node is parent node * 2 and node * 2 + 1 are the children.
    */
  public void init() {
    M = new int[N];
    _init(1, 0, N - 1);
  }

  private void _init(int node, int beg, int end) {
    if (beg == end) M[node] = beg;
    else {
      _init(node*2, beg, (beg+end)/2);
      _init(node*2+1, (beg+end)/2 + 1, end);
      if (A[M[2 * node]] <= A[M[2 * node + 1]])
        M[node] = M[2 * node];
      else
        M[node] = M[2 * node + 1]; 
    }
  }

  public int query(int a, int b) {
    return _query(1, 0, N-1, a, b);
  }

  private int _query(int node, int beg, int end, int a, int b) {
    if ( a > end || b < beg) return -1;
    //if the current interval is included in 
    //the query interval return M[node]
    if (beg >= a && end <= b) return M[node];

    //compute the minimum position in the 
    //left and right part of the interval
    int p1 = _query(2 * node, beg, (beg + end) / 2, a, b);
    int p2 = _query(2 * node + 1, (beg + end) / 2 + 1, end, a, b);

    //return the position where the overall 
    //minimum is
    if (p1 == -1)
      return M[node] = p2;
    if (p2 == -1)
      return M[node] = p1;
    if (A[p1] <= A[p2])
      return M[node] = p1;
    return M[node] = p2;
  }

  
}
