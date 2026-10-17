

class Solution {
    int[] kLargest(int[] arr, int n, int k) {
       int[] res=new int[k];
       
       Arrays.sort(arr);
       for(int i=0;i<k;i++)
       {
            res[i] = arr[n-1];
                n--;
       }
       return res;
    }
}