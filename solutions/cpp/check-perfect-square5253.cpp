// User function Template for C++
class Solution {
  public:
    long long int isPerfectSquare(long long int n){
        // code here
          for(int i=1;i<=n;i++){
            if(i*i==n){
                return 1;
            }
            
        }
        return 0;
    }
};