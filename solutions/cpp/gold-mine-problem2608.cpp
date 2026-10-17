// User function Template for C++

class Solution{
public:
  vector<vector<int>>dp;
    int func(int i,int j,int n,int m,vector<vector<int>>&arr){
        if(i<0||i>=n||j<0||j>=m){
            return 0;
        }
        if(j==m-1){
            return arr[i][j];
        }
        if(dp[i][j]!=-1){
            return dp[i][j];
        }
        int w1=arr[i][j]+func(i+1,j+1,n,m,arr);
        int w2=arr[i][j]+func(i,j+1,n,m,arr);
        int w3=arr[i][j]+func(i-1,j+1,n,m,arr);
        return dp[i][j]=max({w1,w2,w3});
    }
    int maxGold(int n, int m, vector<vector<int>> M)
    {
        // code here
        int ans=0;
         dp.resize(n+1,vector<int>(m+1,-1));
        for(int i=0;i<n;i++){
            int val=func(i,0,n,m,M);
            ans=max(ans,val);
        }
        return ans;
    }
};