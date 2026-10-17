/* The function should return the index of any
   peak element present in the array */

// arr: input array
// n: size of array
class Solution
{
    public:
    int peakElement(int arr[], int n)
    {
       // Your code here
          int m=INT_MIN;
        int ans=-1;
        for(int i=0;i<n;i++)
    {
        if(arr[i]>m)
        {
            ans=i;
            m=arr[i];
        }
    }
    return ans;
       
    }
};