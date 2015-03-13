


/**
Suffix array : Represents the lexicographic rank of each suffix of an array.
LCP array : Contains the maximum length prefix match between two consecutive
suffixes, after they are sorted lexicographically.
  */
class Solution [

  int[] sa; // suffix array.
  int[] pos; // ranking of each position.
  int[] lcp; // longest common prefix
  int N; // len of array.

  /**
    * naive version of construct suffix array by sort.
    * N^2 logn
    */
  public void construct(String s) {
    N = s.length();
    sa = new int[N];
    for (int i = 0; i < N; i++) chars[i] = i;
    Collections.sort(sa, new Comparator<Integer>() {
      public int compare(Integer a, Integer b) {
        return s.substring(a).compareTo(s.substring(b));
      }
    });
  }


  /**
    * A sort base algorithm by comparing 2^k-grams.
    * (2-grams, 4-grams, 8-grams, respectively.
    */
  public void buildSuffixArray(String s) {
    
    N = s.length(); 
    sa = new int[N]

    /* This is a loop that initializes sa[] and pos[].
    For sa[] we assume the order the suffixes have
    in the given string. For pos[] we set the lexicographic
    rank of each 1-gram using the characters themselves.
    That makes sense, right? */
     */
    pos = new int[N]; 
    for (int i = 0; i < N; i++) {
      sa[i] = i;
      pos[i] = (int)s.charAt(i); // sort by first char of a suffix
    }

    int tmp = new int[N];
    /* Gap is the length of the m-gram in each step, divided by 2.
       We start with 2-grams, so gap is 1 initially. It then increases
       to 2, 4, 8 and so on. */
    for (int gap = 2;; gap *= 2) {
      Collections.sort(sa, new Compartor<Integer>() {
        public int compare(int a, int b) {
          return sufCmp(a, b) ? -1: 1;
        }
      });

      /* We compute the lexicographic rank of each m-gram
         that we have sorted above. Notice how the rank is computed
         by comparing each n-gram at position i with its
         neighbor at i+1. If they are identical, the comparison
         yields 0, so the rank does not increase. Otherwise the
         comparison yields 1, so the rank increases by 1. */
      for(int i = 0; i < N - 1; i++) {
        tmp[i + 1] = tmp[i] + sufCmp(sa[i], sa[i + 1]) ? 1 : 0;
      }

      /* tmp contains the rank by position. Now we map this
         into pos, so that in the next step we can look it
         up per m-gram, rather than by position. */
      */
      for (int i = 0; i < N; i++) pos[sa[i]] = tmp[i];

      /* If the largest lexicographic name generated is
         n-1, we are finished, because this means all
         m-grams must have been different. */
      if (tmp[N - 1] == N - 1) break;
    }
  }

  boolean sufCmp(int i, int j) {
    if (pos[i] != pos[j])
      return pos[i] < pos[j];
    i += gap;
    j += gap;
    return (i < N && j < N) ? pos[i] < pos[j] : i > j;
  }


  void buildLCP() {
    for (int i = 0, k = 0; i < N; ++i) if (pos[i] != N - 1) {
      for (int j = sa[pos[i] + 1]; s.charAt(i + k) == s.charAt(j + k);)
        ++k;
      lcp[pos[i]] = k;
      if (k > 0) --k;
    }
  }
}
