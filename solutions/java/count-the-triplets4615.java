

//User function Template for Java

class Solution {
    int countTriplet(int arr[], int n) {
        // code here
         int ans = 0 ;
        HashSet<Integer> set = new HashSet<>();
        for(int i = 0; i < n; i ++) 
            set.add(arr[i]);
        for(int i = 0 ; i < n - 1 ; i ++) 
            for(int j = i + 1; j < n; j ++)
                if(set.contains(arr[i] + arr[j])) ans ++;        
        return ans;
    }
}