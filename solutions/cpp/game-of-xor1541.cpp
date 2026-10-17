class Solution {
  public:
    int gameOfXor(int N , int A[]) {
        // code here
         int xor1=0;
      int preval=0;
      for(int i=0;i<N;i++)
      {
          int val=preval+(N-i);
          if(val%2!=0)
          {
              xor1=xor1^A[i];
          }
          preval+=(N-i-1)-i;
          
      }
      return xor1;
    }
};