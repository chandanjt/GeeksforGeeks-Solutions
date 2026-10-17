
class Solution{
    public:
    //You need to complete this fucntion
    int mod = (int)(1000000007);
    long long power(int N,int R)
    {
       //Your code here
       if(R==0)
       return 1;
       if(N==0)
       return 0;
        if (R%2==0)
          { long ans = power(N, R/2);
          return (ans%mod * ans%mod ) % mod;}
         else {
            long ans = power(N, (R-1)/2);
              return (N%mod*ans%mod * ans%mod )%mod;
        }
        
        
    }

};