


class Solution {

  char[] T, P;
  long mask = 1<<31-1; //A Mersenne Prime

  public Solution(String text, String pattern) {
    T = text.toCharArray();
    P = pattern.toCharArray();
  }


  /**
    * a^b mod n
    */
  long modExp(long a, long b, long n) {
    long r = 1, x = a;
    while (b != 0) {
      if (b%2 == 1) r = r * x % n; // b if odd
      x = x * x % n; //be aware of overflow 
      b = b >> 1; 
    }
    return r;
  }
  
  int encode(char c) {
    return c - 'a';
  }

  /**
    * Raibin Karp on T/P from startIndex
    * digitCount is how many different digit we have for each bit.
    * use prime number digitCount for better hash.
    * mask is a prime number to serve the hash function.
    */
  public int RabinKarp(int digitCount) {
    long heighestBit = modExp(digitCount, P.length-1, mask);
    long patternHash = 0, textHash = 0;
    for (int i = 0; i < P.length; i++) {
      patternHash = (digitCount * patternHash + encode(P[i])) % mask;
      textHash = (digitCount * textHash + encode(T[i])) % mask;
    }
    if (patternHash == textHash) return 0;
    int offset = 1;
    while (offset + P.length < T.length) {
      long oldPart = digitCount * (textHash - encode(T[offset-1]) * heighestBit);
      textHash = (oldPart + encode(T[offset + P.length - 1])) % mask;
      if (textHash < 0) textHash += mask;

      if (patternHash == textHash) {
        // check whether is a false positive
        return offset;
      }
      offset++;
    }
    return -1;
  }
}
