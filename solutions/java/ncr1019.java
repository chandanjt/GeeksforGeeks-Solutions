

//User function Template for Java

class Solution{
    static long ncr(int n, int r)
    {
        //complete the function here
         long mod=1000000007;
       long[] dp=new long[n+1];
       dp[0]=1;
       
       for(int i = 1; i <= n; i++){
           dp[i] = (i * dp[i - 1]) % mod;
       }
       
       if(r > n) {
           return 0;
       }
       long num = dp[n];
       long dino = (dp[r] * dp[n - r]) % mod;
       long ans = (num * power(dino, mod - 2, mod)) % mod;
       long res = ans;
       return res;
    }
      static long power(long x,long y,long mod){
       if (y == 0)
           return 1;
       long p = power(x, y/2, mod) % mod;
       p = (p * p) % mod;
    
       return (y%2 == 0)? p : (x * p) % mod;
   }


}