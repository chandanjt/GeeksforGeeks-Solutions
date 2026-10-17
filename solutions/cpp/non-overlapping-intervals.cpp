class Solution {
  public:
    int minRemoval(int N, vector<vector<int>> &intervals) {
        // code here
         sort(intervals.begin(),intervals.end());
     int count=0;
     
      int left=0;
      int right=1;
      while(right<N)

      if(intervals[left][1]<=intervals[right][0])
      {
          left=right;
          right=right+1;
      }  
      else if(intervals[left][1]<=intervals[right][1])
      {
          count =count+1;
          right=right+1;
      }
      else if(intervals[left][1]>intervals[right][1])
      {
          count=count+1;
          left=right;
          right=right+1;
      }
      return count;
    }
};
