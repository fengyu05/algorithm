/**
Given two words (start and end), and a dictionary, find all shortest transformation sequence(s) from start to end, such that:

Only one letter can be changed at a time
Each intermediate word must exist in the dictionary
For example,

Given:
start = "hit"
end = "cog"
dict = ["hot","dot","dog","lot","log"]
Return
  [
    ["hit","hot","dot","dog","cog"],
    ["hit","hot","lot","log","cog"]
  ]
Note:
All words have the same length.
All words contain only lowercase alphabetic characters.
  *
  */

public class Solution {
    private ArrayList<ArrayList<String>> result;
    private Map<String, ArrayList<String>> backTrackingMap;
    private String start, end;
    private void populateNextWords(String word, HashSet<String> dict, Set<String> nextLevel) {
        char[] chars = word.toCharArray();
        for (int i = 0; i < chars.length; i++) {
            char tmp = chars[i];
            for (char j = 'a'; j <= 'z'; j++) {
                chars[i] = j;
                String newWord = new String(chars);
                if (dict.contains(newWord)) {
                    if (!backTrackingMap.containsKey(newWord)) {
                        backTrackingMap.put(newWord, new ArrayList<String>());
                    }
                    backTrackingMap.get(newWord).add(word);
                    nextLevel.add(newWord);
                }
            }
            chars[i] = tmp;
        }
    }
    
    private void reconstructSolu(String curr, ArrayList<String> solu) {
        for (String prevWord : backTrackingMap.get(curr)) {
            solu.add(prevWord);
            if (prevWord.equals(start)) {
                result.add(new ArrayList<String>(solu));
            } else {
                reconstructSolu(prevWord, solu);
            }
            solu.remove(solu.size() - 1);
        }
    }

    /**
      * BFS that use two set represent two levels' nodes.
      * Termate when the result level completed.
      */
    public ArrayList<ArrayList<String>> findLadders(String end, String start, HashSet<String> dict) {
        this.start = start;
        this.end = end;
        result = new ArrayList<ArrayList<String>>();
        backTrackingMap = new HashMap<>();
        
        dict.add(start);
        dict.add(end);
        
        Set<String> currLevel = new HashSet<>();
        Set<String> nextLevel = new HashSet<>();
        currLevel.add(start);
        
        while(true) {
            for (String word: currLevel) dict.remove(word);
            
            for (String word: currLevel) {
                populateNextWords(word, dict, nextLevel);
            }
            if (nextLevel.isEmpty()) break;
            if (nextLevel.contains(end)) {
                ArrayList<String> solu = new ArrayList<>();
                solu.add(end);
                reconstructSolu(end, solu);
            }
            currLevel.clear();
            currLevel = nextLevel;
            nextLevel = new HashSet<>();
        }

        return result;
    }
}
