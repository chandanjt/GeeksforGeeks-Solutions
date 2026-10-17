//User function template for C++

class Solution{
  public:
  int solve(int i, int j , string& s, string &r, vector<vector<int>>&dp){
        if(i==s.size() || j==s.size()){
            return 0;
        }
        
        if(dp[i][j] != -1){
            return dp[i][j];
        }
        
        int take=0, notTake=0;
        if(s[i] == r[j]){
            take = 1 + solve(i+1,j+1,s,r,dp);
        }
        notTake = max(solve(i+1,j,s,r,dp), solve(i,j+1,s,r,dp));
        
        return dp[i][j] =  max(take,notTake);
    }
    int minimumNumberOfDeletions(string s) { 
        // code here
        string r = s;
       reverse(s.begin(), s.end());
       int n = s.size();
       vector<vector<int>>dp(n+1,vector<int>(n+1,-1));
       
       return s.size()-solve(0,0,s,r,dp);
    } 
};