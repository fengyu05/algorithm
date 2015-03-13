

class Solution {
/*
 * Greedy algorithm for wildcard match '?' '*'
'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).
The matching should cover the entire input string (not partial).
`*/
    public boolean isMatch(String s, String p) {
        int sPos = 0;
        int pPos = 0;
        int starPos = -1;
        int wildPos = -1;
        while (sPos < s.length()) {
            if (pPos < p.length() && 
                (p.charAt(pPos) == '?' || s.charAt(sPos) == p.charAt(pPos))) {
                pPos++;
                sPos++;
            } else if (pPos < p.length() && p.charAt(pPos) == '*') {
                starPos = pPos;
                wildPos = sPos;
                pPos++;
            } else {
                // not match, use *
                if (starPos < 0) return false;
                pPos = starPos + 1;
                sPos = wildPos + 1;
                wildPos++;
            }
        }
        while (pPos < p.length() && p.charAt(pPos) == '*') pPos++;
        return pPos == p.length();
    }


    /**
      * Recursion algorithm on regex matching.
'.' Matches any single character.
'*' Matches zero or more of the preceding element.

The matching should cover the entire input string (not partial).
      */
    public boolean isMatch(String s, String p) {
        if (s.equals(p)) return true;
        if (p.isEmpty()) return false;
        
        boolean hasStar = false;
        if (p.length() >= 2 && p.charAt(1) == '*') hasStar = true;
        
        if (hasStar) {
            for (int i = 0; i <= s.length(); i++) {
                String prefix = s.substring(0, i);
                String postfix = s.substring(i);
                if (p.charAt(0) == '.') {
                    if (isMatch(postfix, p.substring(2))) return true;
                } else {
                    boolean allValid = true;
                    for (char c: prefix.toCharArray()) {
                        if (c != p.charAt(0)) {
                            allValid = false;
                            break;
                        }
                    }
                    if (allValid && isMatch(postfix, p.substring(2))) return true;
                }
            }
            return false;
        } else {
            if (s.length() > 0 && (p.charAt(0) == '.' || s.charAt(0) == p.charAt(0))) {
                return isMatch(s.substring(1), p.substring(1));
            } return false;
        }
    }
}
