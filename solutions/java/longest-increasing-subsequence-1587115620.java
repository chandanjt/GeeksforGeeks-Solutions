



class Solution 
{
    //Function to find length of longest increasing subsequence.
    static int longestSubsequence(int n, int a[])
    {
        // code here
        int lis[] = new int[n];
        int len = 1; // Length of the longest increasing subsequence

        lis[0] = a[0];

        for (int i = 1; i < n; i++) {
            if (a[i] > lis[len - 1]) {
                lis[len] = a[i];
                len++;
            } else {
                // Binary search to find the position to insert a[i] in the LIS
                int idx = Arrays.binarySearch(lis, 0, len, a[i]);
                if (idx < 0) {
                    idx = -idx - 1;
                }
                lis[idx] = a[i];
            }
        }

        return len;
    }
} 