//User function Template for C++
class Solution
{
public:
    long long sumOfDivisors(int N)
    {
        // Write Your Code here
          long ans=0;
    for(long i=1;i<=N;i++){
            long times=N/i;
            ans+=(i*times);
     }
   return ans;
    }
};