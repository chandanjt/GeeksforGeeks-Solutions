

//User function Template for Java

class Solution {
    int print2largest(int arr[], int n) {
       Arrays.sort(arr);
       int large=arr[n-1];
       int small=arr[0];
       if(large==small)
       return-1;
       for(int i=0;i<n;i++)
       {
           if(arr[i]==large)
           arr[i]=0;
           
       }
       
      Arrays.sort(arr);
       return arr[n-1];
    }
}