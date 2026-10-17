

// User function Template for Java

class Solution {

    long countSubarray(int arr[], int n, int k) {

        long answer=((long)n * (long)(n+1))/2;
        int i=0;
        long notreq=0;
        while(i<n)
        {
            if(arr[i]>k)
            {
                i++;
                continue;
            }
            long count=0;
            while(i<n && arr[i]<=k)
            {
                i++;
                count++;
            }
            notreq += count*(count+1)/2;
        }
        return answer - notreq;
    }
}