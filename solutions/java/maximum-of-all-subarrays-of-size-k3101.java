

class Solution {
    static class pair implements Comparable<pair>{
        int val;
        int indx;
        public pair(int val,int indx)
        {
            this.val=val;
            this.indx=indx;
        }
        @Override
        public int compareTo(pair p2)
        {
            return p2.val-this.val;
        }
    }
    static ArrayList<Integer> max_of_subarrays(int arr[], int n, int k) {
       ArrayList<Integer> result=new ArrayList<>();
        int res[]=new int[arr.length-k+1];
        PriorityQueue<pair>pq=new PriorityQueue<>();
        for(int i=0;i<k;i++)
        {
            pq.add(new pair(arr[i],i));
        }
        res[0]=pq.peek().val;
        
        for(int i=k;i<arr.length;i++)
        {
            while(pq.size()>0&&pq.peek().indx<=(i-k))
            {
                pq.remove();
            }
            pq.add(new pair(arr[i],i));
            res[i-k+1]=pq.peek().val;
        }
        for(int i=0;i<res.length;i++)
        {
            result.add(res[i]);
        }
        return result;
    }
}