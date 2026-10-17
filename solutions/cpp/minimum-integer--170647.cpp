class Solution {
  public:
    int minimumInteger(int N, vector<int> &A) {
        long long sum=0;
      for(int i=0;i<N;i++)
      {
          sum=sum+A[i];
      }
     long long min=INT_MAX;

      for(int j=0;j<N;j++)
      {
          if((log(sum)<=log(N)+log(A[j])) && min>A[j])
          {
              min=A[j];
          }
      }
      
      return (int)min;
    }
};