// User function Template for C++
class Solution {
  public:
  int mod=1000000007;
    int nthFibonacci(int n){
        // code here
        int a=0;
       int b=1,c=0;
       for(int i=1;i<n;i++)
       {
           c=(a+b)%mod;
           a=b%mod;
           b=c%mod;
       }
       return c%mod;
    }
};