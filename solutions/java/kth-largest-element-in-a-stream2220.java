

class Solution {
    static int[] kthLargest(int k, int[] arr, int n) {
        // code here
       int res[] = new int[n],i=0;
        PriorityQueue<Integer> pq = new PriorityQueue<>(k);
        
        for(i=0;i<k;i++){
            pq.offer(arr[i]);  
            res[i]=-1;
        }
      
        for(i=k;i<n;i++){
            res[i-1]=pq.peek(); 
            pq.offer(arr[i]); 
            if(pq.size()>k)
                pq.poll(); 
        }
        res[n-1]=pq.peek(); 
        return res;
    }
};