

// User function Template for Java

class Solution {
    int missingNumber(int array[], int n) {
        // Your Code Here
         int x=0;
        for(int i=1;i<=n-1;i++){
            x=x^i^array[i-1];
        }
        return x^n;
    }
}