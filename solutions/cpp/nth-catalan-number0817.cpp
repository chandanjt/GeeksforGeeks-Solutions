class Solution
{
    public:
    //Function to find the nth catalan number.
    int mod=(int)(1e9+7);
    int findCatalan(int n) 
    {
           vector<long long>arr(n+1,0);
        arr[0] = 1;
        arr[1] = 1;
        
        for(int i=2; i<=n; i++)
        {
            for(int j=0; j<i; j++)
            {
                arr[i]=(arr[i]+(arr[j]*arr[i-j-1])%mod)%mod;
            }
        }
        
        return arr[n];
    }
};