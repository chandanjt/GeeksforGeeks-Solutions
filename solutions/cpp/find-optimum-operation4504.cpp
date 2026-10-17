class Solution
{
  public:
  int solve(int n){
       int operation = 0;
      while(n>=1){
          if(n%2==0){
              n/=2;
              operation++;
          }else{
              n-=1;
              operation++;
          }
      }
      return operation;
      
   }
    int minOperation(int n)
    {
        //code here.
             if(n==0)return 0;
        else if(n==1) return 1;
        else return solve(n);
    }
};