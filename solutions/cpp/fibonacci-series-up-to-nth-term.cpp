class Solution {
  public:
    vector<int> Series(int n) {
        // Code here
        long long mod=1000000000+7;
        if(n==0)
        return {};
        vector<int>res(n+1,0);
        res[0]=0;
        res[1]=1;
        for(int i=2;i<=n;i++)
        {
            res[i]=(res[i-1]+res[i-2])%mod;
        }
        return res;
    }
};