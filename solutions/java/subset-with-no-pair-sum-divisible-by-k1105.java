

class Solution {
    static int maxGroupSize(int[] arr, int N, int K) {
     
     int a[]=new int[K];  
     for(int i=0;i<N;i++)
     {
         a[arr[i]%K]++;
     }
     int ans=0;
     for(int i=0;i<=K/2;i++)
     {
         if(i==0||i==K-i)
         {
             if(a[i]!=0)
             ans++;
         }
         else
         ans +=Math.max(a[i],a[K-i]);
     }
     return ans;
    }
};