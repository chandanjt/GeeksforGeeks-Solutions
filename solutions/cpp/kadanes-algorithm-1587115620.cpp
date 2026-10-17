class Solution{
    public:
    // arr: input array
    // n: size of array
    //Function to find the sum of contiguous subarray with maximum sum.
    long long maxSubarraySum(int arr[], int n){
        
        // Your code here
               long long sum=0;
      long long maxi=LONG_MIN;
       for(int i=0;i<n;i++)
       {
           sum=sum+arr[i];
           if(sum>maxi)
           maxi=sum;
           if(sum<0)
           sum=0;
       }
        return maxi;
        
    }
};