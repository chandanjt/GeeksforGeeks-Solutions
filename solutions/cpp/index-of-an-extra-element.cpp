class Solution {
  public:
    int findExtra(int n, int arr1[], int arr2[]) {
        // add code here.
       int low=0;
       int high=n-1;
       while(low<high)
       {
           if(arr1[low]==arr2[low] && arr1[high]==arr2[high-1])
           {
              low++;
              high--;
           }
           else if(arr1[low]!=arr2[low])
           return low;
           else if(arr1[high]!=arr2[high-1])
           return high;
           
       }
    }
};