

public class Solution {
    
    private double iter(double x, double s) {
        return (x + s/x)/2;
    }
    
    private boolean sameFloat(double x, double y ) {
        return Math.abs(x-y) < 0.01;
    }

    public int sqrt(int s) {
        double x = 1;
        while (!sameFloat(x*x, s)) {
            x = iter(x, s);
        }
        return (int)x;
    }
}
