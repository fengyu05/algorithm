
class Solution {
    public int largestRectangleArea(int[] height) {
        Stack<Integer> stack = new Stack<>();
        int max = 0;
        for (int i = 0; i <= height.length; i++) {
            int currHeight = i == height.length ? 0: height[i]; // add a 0 to the end of Array height
            if (stack.empty() || height[stack.peek()] < currHeight) {
                stack.push(i);
            } else {
                int maxHeight = height[stack.pop()];
                max = Math.max(max, maxHeight * (stack.empty() ? i : i - stack.peek() - 1));
                i--;
            }
        }
        return max;
    }
}    
