/**
  DP on two string problems.
  */

/**
Edit distance.


Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2. (each operation is counted as 1 step.)

You have the following 3 operations permitted on a word:

a) Insert a character
b) Delete a character
c) Replace a character

define: dp[i][j] mean edit distance of word1.substring(0, i) to 
                                       word2.substring(0, j). 

dp[i][j] =  dp[i-1][j-1]   if (A[i] == B[j])
      or = min(dp[i][j-1], dp[i-1][j], dp[i-1][j-1]) +1;
      
initial: dp[0][j] = j and dp[i][0] = i   
  */


/**
  LCS
  */
class Solution {
    // dp[1..n][1..m]
    // dp[x][y] = dp[x-1][y-1] + 1 if A[x-1] == B[y-1]
    // else:
    // dp[x][y] = max(dp[x-1][y], dp[x][y-1]) 
    private char[] LCS(char[] A, char[] B) {
        int n = A.length;
        int m = B.length;
        
        int[][] dp = new int[n + 1][m + 1]; // init with 0
        char[][] solu = new char[n + 1][m + 1];
        for (int x = 1; x <= n; x++) {
            for (int y = 1; y <= m; y++) {
                if (A[x-1] == B[y-1]) {
                  dp[x][y] = dp[x-1][y-1] + 1;
                    solu[x][y] = '\\';
                } else {
                    if (dp[x-1][y] > dp[x][y-1]) {
                        dp[x][y] = dp[x-1][y];
                        solu[x][y] = '|';
                    } else {
                        dp[x][y] = dp[x][y-1];
                        solu[x][y] = '-';
                    }
                }
            }
        }
        for (int x = 0; x <= n; x++) {
            for (int y = 0; y <= m; y++) {
                System.out.printf("%d ", dp[x][y]);
            }
            System.out.printf("\n");
        }
        for (int x = 0; x <= n; x++) {
            for (int y = 0; y <= m; y++) {
                System.out.printf("%c ", solu[x][y]);
            }
            System.out.printf("\n");
        }     
        int resultLength = dp[n][m];
        char[] result = new char[resultLength];
        while (n > 0 && m > 0) {

            switch (solu[n][m]){
                case '\\':
                    result[--resultLength] = A[n - 1];
                    n--;
                    m--;
                    break;
                case '|':
                    n--;
                    break;
                case '-':
                    m--;
                    break;
            }
        }
        assert(resultLength == 0);
        return result;
    }

    /**
Distinct Subsequences Total Accepted: 8478 Total Submissions: 35221 My Submissions
Given a string S and a string T, count the number of distinct subsequences of T in S.

A subsequence of a string is a new string which is formed from the original string
 by deleting some (can be none) of the characters without disturbing the relative
 positions of the remaining characters. (ie, "ACE" is a subsequence of "ABCDE"
 while "AEC" is not).

Here is an example:
S = "rabbbit", T = "rabbit"

Return 3.
      */
    public int numDistinct(String S, String T) {
        int lenS = S.length();
        int lenT = T.length();
        if (lenS < lenT) return 0;
        int[][] dp = new int[2][lenS + 1];
        for (int i = 0; i <= lenS; i++) {
            dp[0][i] = 1;
        }
        for (int i = 1; i <= lenT; i ++) {
            for (int j = i; j <= lenS; j++) {
                dp[i%2][j] = (i == j) ? 0 : dp[i%2][j-1];// don't use S[j-1]
                if (S.charAt(j-1) == T.charAt(i-1)) { // use S[j-1]
                    dp[i%2][j] += dp[(i+1)%2][j-1];
                }
            }
        }
        return dp[lenT%2][lenS];
    }



    /**
      * Interleaving string.
Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.

For example,
Given:
s1 = "aabcc",
s2 = "dbbca",

When s3 = "aadbbcbcac", return true.
When s3 = "aadbbbaccc", return false.
      * dp[i][j] = dp[i-1][j] && ? || dp[i][j-1] && ??
      */
    public boolean isInterleave(String s1, String s2, String s3) {
        int s1Len = s1.length();
        int s2Len = s2.length();
        if (s1Len + s2Len != s3.length()) return false;
        boolean [][] dp = new boolean [s1Len+1][s2Len+1];
        dp[0][0] = true;
        for (int i = 1; i <= s2Len; i++) {
            if (s2.charAt(i-1) == s3.charAt(i-1)) {
                dp[0][i] = true;
            } else {
                break;
            }
        }
        for (int i = 1; i <= s1Len; i++) {
            if (s1.charAt(i-1) == s3.charAt(i-1)) {
                dp[i][0] = true;
            } else {
                break;
            }
        }
        for (int i = 1; i <= s1Len; i++) {
            for (int j = 1; j <= s2Len; j++) {
                dp[i][j] = (dp[i-1][j] && s1.charAt(i-1) == s3.charAt(i+j-1))
                    || (dp[i][j-1] && s2.charAt(j-1) == s3.charAt(i+j-1));
            }
        }
        return dp[s1Len][s2Len];
    }


    /**
Given a string s, partition s such that every substring of the partition is a palindrome.

Return the minimum cuts needed for a palindrome partitioning of s.

For example, given s = "aab",
Return 1 since the palindrome partitioning ["aa","b"] could be produced using 1 cut.

      * dp[i] = min(dp[j] + 1 ?) j=[0,i]
      */
    public int minCut(String s) {
        int len = s.length();
        boolean[][] isPalindrome = new boolean[len][len];
        for (int deta = 0; deta < len; deta++) {
            for (int i = 0; i + deta < len; i++) {
                if (deta == 0) {
                    isPalindrome[i][i] = true;
                    continue;
                } else if (deta == 1) {
                    isPalindrome[i][i+1] = s.charAt(i) == s.charAt(i+1); 
                } else {
                    isPalindrome[i][i+deta] = isPalindrome[i+1][i+deta-1] && s.charAt(i) == s.charAt(i+deta);
                }
            }
        }
        
        int[] dp = new int[len];
        dp[0] = 0;
        for (int i = 1; i < len; i++) {
            int min = Integer.MAX_VALUE;
            for (int j = 0; j <= i; j++) {
                if (isPalindrome[j][i]) {
                    if (j == 0) min = 0;
                    else 
                    min = Math.min(min, dp[j-1] + 1);
                }
            }
            dp[i] = min;
        }
        return dp[len-1];
    }
}
