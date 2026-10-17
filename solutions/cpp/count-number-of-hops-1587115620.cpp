
class Solution
{
    public:
    //Function to count the number of ways in which frog can reach the top.
    int mod=1e9+7;
    long long countWays(int n)
    {
        
        // your code here
          vector<long long>v(n+1);
        v[0]=1;
        if(n>=1){
            v[1]=1;
            if(n>=2){
                v[2]=2;
                if(n>=3){
                    v[3]=4;
                }
            }
        }
        
        for(int i=4;i<=n;i++){
            v[i]=(v[i-1]+v[i-2]+v[i-3])%mod;
        }
        return v[n];
    }
};