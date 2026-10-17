

//User function Template for Java

class Solution {
    static int countSquares(int N) {
        // code here
                   int a = (int) (Math.sqrt(N));
        if (a * a == N) {
            return a - 1;
        }

        return a;
    }
}